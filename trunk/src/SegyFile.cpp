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
