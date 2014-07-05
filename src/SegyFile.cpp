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
            vector<char> buffer(BinaryFileHeader::buffer_size + TextualFileHeader::line_length * TextualFileHeader::nlines,0);
            tmp.write( buffer.data(), buffer.size() );
        }
        //////////

        //////////
        // Open SEG Y file and read TFH and BFH
        fstream_.open(filePath_, ios::binary | ios::out | ios::in);
        fstream_.exceptions( ios::eofbit|ios::badbit|ios::failbit );
        // Read Textual file header (3200 bytes)
        fstream_.read(tfh_->get(), TextualFileHeader::line_length * TextualFileHeader::nlines);
        // Read Binary file header  (400 bytes)
        read(fstream_,bfh_);        
        //////////
        
        //////////
        // Create index to have random access later
        /// @todo TO BE CHANGED
        indexer_.reset(new InMemoryIndexer(*this, fstream_));
        indexer_->createIndex();
        writer_.reset(new SegyFileLazyWriter(*indexer_,fstream_));
        //////////
    }

    void SegyFile::commitFileHeaderModifications() {
        fstream_.seekp( ios::beg );
        fstream_.write( tfh_->get(), TextualFileHeader::line_length * TextualFileHeader::nlines );
        write( fstream_, bfh_ );
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

    SegyFile::trace_type SegyFile::readTrace(const size_t n) {
        TraceHeader::smart_reference_type th(TraceHeader::create(tag_));
        // Read trace header
        auto fposition = indexer_->position(n);
        fstream_.seekg( fposition );
        read(fstream_,th);
        // Read trace data
        size_t sizeOfDataSample = constants::sizeOfDataSample((*bfh_)[rev0::bfh::formatCode]);
        auto nSamples = indexer_->nsamples(n);
        trace_data_type td;
        read(fstream_,td,nSamples,sizeOfDataSample);
        return make_pair(th, td);
    }

    // Define template function
    template<class T>
    Trace<T> SegyFile::readTraceAs(const size_t n) {
        //////////
        // Check consistency between type and format     
        auto encoding_format = (*bfh_)[rev0::bfh::formatCode];
        stringstream estream;            
        if( encoding_format == constants::SegyFileFormatCode::Fixed32 ) { // Fixed 32 not supported
            estream << "Data format error : format Fixed32 is deprecated and won't be supported by the library" << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;
        } else if ( // If the format is floating point, but the type is not throw
                (encoding_format == constants::SegyFileFormatCode::IEEEfloat32 ||
                 encoding_format == constants::SegyFileFormatCode::IBMfloat32) &&
                !std::is_same<T,float>::value
                ) {
            estream << "Data format error : can't read a floating-point trace as " << typeid(T).name() << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;         
            throw runtime_error(estream.str());
        } else if (
                encoding_format == constants::SegyFileFormatCode::Int32 &&
                !std::is_same<T,int32_t>::value
                ) {
            estream << "Data format error : can't read an int32_t trace as " << typeid(T).name() << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;         
            throw runtime_error(estream.str());
        } else if (
                encoding_format == constants::SegyFileFormatCode::Int16 &&
                !std::is_same<T,int16_t>::value
                ) {
            estream << "Data format error : can't read an int16_t trace as " << typeid(T).name() << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;         
            throw runtime_error(estream.str());
        } else if (
                encoding_format == constants::SegyFileFormatCode::Int8 &&
                !std::is_same<T,int8_t>::value
                ) {
            estream << "Data format error : can't read an int8_t trace as " << typeid(T).name() << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;         
            throw runtime_error(estream.str());
        }        
        size_t sizeOfDataSample = constants::sizeOfDataSample((*bfh_)[rev0::bfh::formatCode]);
        if( sizeOfDataSample != sizeof(T) ) { // Check size consistency
            estream << "Data format error : unexpected size mismatch " << endl;
            estream << "\tSEG-Y file : " << filePath_ << endl;                     
            estream << "\tdata value size : " << sizeOfDataSample << endl;
            estream << "\t" << typeid(T).name() << " value size : " << sizeof(T) << endl;
            throw runtime_error(estream.str());
        }
        //////////
        
        //////////
        // Read trace (header)
        TraceHeader::smart_reference_type th(TraceHeader::create(tag_));
        auto fposition = indexer_->position(n);
        fstream_.seekg( fposition );
        read(fstream_,th);        
        // Read trace (data)
        Trace<T> trace(th);         
        trace.resize(indexer_->nsamples(n));        
        read(fstream_,trace);
        // Convert IBMfloat32 to IEEE754
        if( encoding_format == constants::SegyFileFormatCode::IBMfloat32 ) {
            for( auto & x : trace) {
                int32_t * pnt = reinterpret_cast<int32_t *>(&x);
                ibm2ieee(*pnt);
            }
        }
        return trace;
        //////////
    }
    
    template Trace<float>   SegyFile::readTraceAs<float>  (const size_t n);
    template Trace<int32_t> SegyFile::readTraceAs<int32_t>(const size_t n);
    template Trace<int16_t> SegyFile::readTraceAs<int16_t>(const size_t n);
    template Trace<int8_t>  SegyFile::readTraceAs<int8_t> (const size_t n);
    
    void SegyFile::overwriteTrace(const trace_type& trace, const size_t n) {        
        writer_->addToOverwriteQueue(trace,n);
    }

    void SegyFile::appendTrace(const trace_type& trace) {
        writer_->addToAppendQueue(trace,constants::sizeOfDataSample((*bfh_)[rev0::bfh::formatCode]));
    }
    
    void SegyFile::commitTraceModifications() {
        writer_->commit( constants::sizeOfDataSample((*bfh_)[rev0::bfh::formatCode]) );
    }

    SegyFile::~SegyFile() {  
        commitTraceModifications();
    }
    
    ////////////////////
    // Private functions
    ////////////////////
}
