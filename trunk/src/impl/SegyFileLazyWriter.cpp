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

#include<impl/SegyFileLazyWriter.h>

#include<iterator>

#include "impl/SegyFileIndexer.h"

namespace seismic {

    
    SegyFileLazyWriter::SegyFileLazyWriter(SegyFileIndexer& indexer, boost::filesystem::fstream& fileStream)
    : indexer_(indexer), fileStream_(fileStream){
    }
    
    void SegyFileLazyWriter::addToOverwriteQueue(const SegyFile::trace_type& trace, size_t n) {
        overwite_map_[n] = trace;
    }

    void SegyFileLazyWriter::commit() {
        using namespace std;
        // Commit overwrite modifications
        /// @TODO implementation here
        // Commit append modifications
        fileStream_.seekp( 0, ios::end );
        fileStream_.write(append_vector_.data(),append_vector_.size());
        append_vector_.clear();
        // Update index
        indexer_.updateIndex();
    }
    
    void SegyFileLazyWriter::addToAppendQueue(const SegyFile::trace_type& trace, size_t sizeOfDataSample) {        
        using namespace std;
        // Declare a stream of byte
        stringstream byte_stream;
        // Write trace header
        write(byte_stream, trace.first);
        // Write trace data
        trace_data_type traceDataCopy(trace.second);
        write(byte_stream,traceDataCopy,trace.first[rev0::th::nsamplesTrace],sizeOfDataSample);
        // Append to internal buffer
        auto buffer = byte_stream.str();
        copy(buffer.begin(),buffer.end(),back_inserter(append_vector_));
    }
    
}
