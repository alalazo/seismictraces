/*
 *  SeismicTraces : another C++ library that reads files in SEG-Y format
 * 
 *  Copyright (C) 2014  Massimiliano Culpo
 * 
 *  This file is part of SeismicTraces.
 *
 *  SeismicTraces is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SeismicTraces is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 * 
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SeismicTraces.  If not, see <http://www.gnu.org/licenses/>.
 */
#include<SegyFile.h>

#include<impl/SegyFileIndexer.h>
#include<impl/rev0/SegyFile-BinaryFileHeader-Rev0.h>
#include<impl/utilities-inl.h>

/// @todo REMOVE THESE INCLUDES
#include<impl/indexer/InMemoryIndexer.h>
#include<impl/SegyFileLazyWriter.h>

#include<type_traits>
#include<typeinfo>

using namespace std;
using namespace boost::filesystem;

namespace seismic {

    SegyFile::SegyFile(const char * filename, const std::string & revision_tag)
    : filePath_(filename), tfh_(new TextualFileHeader)
    , bfh_(BinaryFileHeader::create(revision_tag))
    , tag_(revision_tag) {
        //////////
        // If the file does not exist create it
        // and add enough space for TFH and BFH
        if (!exists(filePath_)) {
            create_directories(filePath_.parent_path());
            boost::filesystem::fstream tmp(filePath_, ios::binary | ios::out);
            vector<char> buffer(BinaryFileHeader::buffer_size + TextualFileHeader::line_length * TextualFileHeader::nlines, 0);
            tmp.write(buffer.data(), buffer.size());
        }
        //////////

        //////////
        // Open SEG Y file and read TFH and BFH
        fstream_.open(filePath_, ios::binary | ios::out | ios::in);
        fstream_.exceptions(ios::eofbit | ios::badbit | ios::failbit);
        // Read Textual file header (3200 bytes)
        fstream_.read(tfh_->get(), TextualFileHeader::line_length * TextualFileHeader::nlines);
        // Read Binary file header  (400 bytes)
        read(fstream_, bfh_);
        //////////

        //////////
        // Create index to have random access later
        /// @todo TO BE CHANGED
        indexer_.reset(new InMemoryIndexer(*this, fstream_));
        indexer_->createIndex();
        writer_.reset(new SegyFileLazyWriter(*indexer_, fstream_));
        //////////
    }

    void SegyFile::commitFileHeaderModifications() {
        fstream_.seekp(ios::beg);
        fstream_.write(tfh_->get(), TextualFileHeader::line_length * TextualFileHeader::nlines);
        write(fstream_, bfh_);
    }

    TextualFileHeader& SegyFile::getTextualFileHeader() {
        return const_cast<TextualFileHeader&> (static_cast<const SegyFile&> (*this).getTextualFileHeader());
    }

    const TextualFileHeader& SegyFile::getTextualFileHeader() const {
        return *tfh_;
    }

    const BinaryFileHeader& SegyFile::getBinaryFileHeader() const {
        return *bfh_;
    }

    BinaryFileHeader& SegyFile::getBinaryFileHeader() {
        return const_cast<BinaryFileHeader&> (static_cast<const SegyFile&> (*this).getBinaryFileHeader());
    }

    const std::string& SegyFile::tag() const {
        return tag_;
    }

    const boost::filesystem::path& SegyFile::path() const {
        return filePath_;
    }

    size_t SegyFile::ntraces() const {
        return indexer_->size();
    }

    SegyFile::raw_trace_type SegyFile::readRawTrace(const size_t n) {
        TraceHeader::smart_reference_type th(TraceHeader::create(tag_));
        // Read trace header
        auto fposition = indexer_->position(n);
        fstream_.seekg(fposition);
        read(fstream_, th);
        // Read trace data
        size_t sizeOfDataSample = constants::sizeOfDataSample((*bfh_)[rev0::bfh::formatCode]);
        auto nSamples = indexer_->nsamples(n);
        trace_data_type td;
        read(fstream_, td, nSamples, sizeOfDataSample);
        return make_pair(th, td);
    }

    void SegyFile::overwriteRawTrace(const raw_trace_type& trace, const size_t n) {
        writer_->addToOverwriteQueue(trace, n);
    }

    void SegyFile::appendRawTrace(const raw_trace_type& trace) {
        writer_->addToAppendQueue(trace, constants::sizeOfDataSample((*bfh_)[rev0::bfh::formatCode]));
    }

    void SegyFile::commitTraceModifications() {
        writer_->commit(constants::sizeOfDataSample((*bfh_)[rev0::bfh::formatCode]));
    }

    SegyFile::~SegyFile() {
        commitTraceModifications();
    }

    //////////
    // Template member functions
    //////////

    template<class T>
    Trace<T> SegyFile::readTraceAs(const size_t n) {
        auto encoding_format = (*bfh_)[rev0::bfh::formatCode];
        // Check consistency
        checkConsistencyWithType<T>();
        // Read trace header
        TraceHeader::smart_reference_type th(TraceHeader::create(tag_));
        auto fposition = indexer_->position(n);
        fstream_.seekg(fposition);
        read(fstream_, th);
        // Read trace data
        Trace<T> trace(th);
        trace.resize(indexer_->nsamples(n));
        read(fstream_, trace);
        // Convert IBMfloat32 to IEEE754
        if (encoding_format == constants::SegyFileFormatCode::IBMfloat32) {
            for (auto & x : trace) {
                int32_t * pnt = reinterpret_cast<int32_t *> (&x);
                ibm2ieee(*pnt);
            }
        }
        return trace;
        //////////
    }

    template Trace<float> SegyFile::readTraceAs<float> (const size_t n);
    template Trace<int32_t> SegyFile::readTraceAs<int32_t>(const size_t n);
    template Trace<int16_t> SegyFile::readTraceAs<int16_t>(const size_t n);
    template Trace<int8_t> SegyFile::readTraceAs<int8_t> (const size_t n);

    template<class T>
    void SegyFile::appendTrace(const Trace<T>& trace) {        
        appendRawTrace(convertToRawType(trace));        
    }

    template void SegyFile::appendTrace<float >(const Trace<float >& trace);
    template void SegyFile::appendTrace<int32_t>(const Trace<int32_t>& trace);
    template void SegyFile::appendTrace<int16_t>(const Trace<int16_t>& trace);
    template void SegyFile::appendTrace<int8_t >(const Trace<int8_t >& trace);

    template<class T>
    void SegyFile::overwriteTrace(const Trace<T>& trace, const size_t n) {
        overwriteRawTrace(convertToRawType(trace), n);
    }

    template void SegyFile::overwriteTrace<float > (const Trace<float > & trace, const size_t n);
    template void SegyFile::overwriteTrace<int32_t>(const Trace<int32_t>& trace, const size_t n);
    template void SegyFile::overwriteTrace<int16_t>(const Trace<int16_t>& trace, const size_t n);
    template void SegyFile::overwriteTrace<int8_t >(const Trace<int8_t >& trace, const size_t n);

    ////////////////////
    // Private functions
    ////////////////////

    template<class T>
    void SegyFile::checkConsistencyWithType() {
        //////////
        // Check consistency between type and format     
        auto encoding_format = (*bfh_)[rev0::bfh::formatCode];
        stringstream estream;
        if (encoding_format == constants::SegyFileFormatCode::Fixed32) { // Fixed 32 not supported
            estream << "Data format error : format Fixed32 is deprecated and won't be supported by the library" << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;
        } else if (// If the format is floating point, but the type is not throw
                (encoding_format == constants::SegyFileFormatCode::IEEEfloat32 ||
                encoding_format == constants::SegyFileFormatCode::IBMfloat32) &&
                !std::is_same<T, float>::value
                ) {
            estream << "Data format error : can't read a floating-point trace as " << typeid (T).name() << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;
            throw runtime_error(estream.str());
        } else if (
                encoding_format == constants::SegyFileFormatCode::Int32 &&
                !std::is_same<T, int32_t>::value
                ) {
            estream << "Data format error : can't read an int32_t trace as " << typeid (T).name() << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;
            throw runtime_error(estream.str());
        } else if (
                encoding_format == constants::SegyFileFormatCode::Int16 &&
                !std::is_same<T, int16_t>::value
                ) {
            estream << "Data format error : can't read an int16_t trace as " << typeid (T).name() << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;
            throw runtime_error(estream.str());
        } else if (
                encoding_format == constants::SegyFileFormatCode::Int8 &&
                !std::is_same<T, int8_t>::value
                ) {
            estream << "Data format error : can't read an int8_t trace as " << typeid (T).name() << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;
            throw runtime_error(estream.str());
        }
        size_t sizeOfDataSample = constants::sizeOfDataSample((*bfh_)[rev0::bfh::formatCode]);
        if (sizeOfDataSample != sizeof (T)) { // Check size consistency
            estream << "Data format error : unexpected size mismatch " << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;
            estream << "\tdata value size : " << sizeOfDataSample << endl;
            estream << "\t" << typeid (T).name() << " value size : " << sizeof (T) << endl;
            throw runtime_error(estream.str());
        }
        //////////        
    }

    template<class T>
    SegyFile::raw_trace_type SegyFile::convertToRawType(const Trace<T>& trace) {
        auto encoding_format = (*bfh_)[rev0::bfh::formatCode];
        // Check consistency
        checkConsistencyWithType<T>();
        // Convert to a char stream
        std::vector<char> raw_stream;
        raw_stream.resize(trace.size() * sizeof (typename Trace<T>::value_type));
        std::copy(reinterpret_cast<const char *> (trace.data()),
                reinterpret_cast<const char *> (trace.data() + trace.size()),
                raw_stream.begin()
                );
        // Convert IBMfloat32 to IEEE754
        if (encoding_format == constants::SegyFileFormatCode::IBMfloat32) {
            for_each(reinterpret_cast<int32_t*> (raw_stream.data()),
                    reinterpret_cast<int32_t*> (raw_stream.data() + raw_stream.size()),
                    [](int32_t & x) {
                        ieee2ibm(x);
                    }
            );
        }
        return make_pair(static_cast<const TraceHeader::smart_reference_type&> (trace), std::move(raw_stream));
    }

}
