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

#include<impl/indexer/InMemoryIndexer.h>

#include<SegyFile.h>
#include<impl/SegyFile-TraceHeader.h>
#include<impl/rev1/SegyFile-BinaryFileHeader-Rev1.h>

#include<boost/filesystem.hpp>

#include<stdexcept>
#include<sstream>

using namespace std;
using namespace boost::filesystem;

namespace seismic {

    InMemoryIndexer::InMemoryIndexer(SegyFile& segyFile, boost::filesystem::fstream& fileStream)
    : SegyFileIndexer(segyFile, fileStream), segyFile_(segyFile), fileStream_(fileStream)
    , previousEndOfFile_(0) {
    }

    void InMemoryIndexer::createIndex() {
        //boost::filesystem::fstream::pos_type position(3600); /// @todo CHANGE HERE
        fileStream_.seekg(3600);
        scanFileAndUpdateIndexFromCurrentPosition();
    }

    size_t InMemoryIndexer::nsamples(const size_t n) const {
        return traceNsamples_[n];
    }

    size_t InMemoryIndexer::size() const {
        return traceStrides_.size();
    }

    boost::filesystem::fstream::pos_type InMemoryIndexer::position(const size_t n) const {
        return traceStrides_.at(n);
    }

    void InMemoryIndexer::updateIndex() {
        fileStream_.seekg( previousEndOfFile_ );
        scanFileAndUpdateIndexFromCurrentPosition();
    }

    /////////////////////
    // PRIVATE METHODS //
    /////////////////////

    void InMemoryIndexer::scanFileAndUpdateIndexFromCurrentPosition() {
        boost::filesystem::fstream::pos_type position = fileStream_.tellg();
        TraceHeader::smart_reference_type th(TraceHeader::create(segyFile_.tag()));
        auto segyFileSize = file_size(segyFile_.path());
        while (true) {
            // Check for end of file
            if (segyFileSize == static_cast<size_t> (position)) {
                // If the end of the file has been reached, then stop reading
                break;
            } else if (segyFileSize < static_cast<size_t> (position)) {
                // If the end of the file has been exceeded, the file is truncated
                stringstream estream;
                estream << "FATAL ERROR: " << segyFile_.path() << " is truncated after trace number " << traceStrides_.size() << endl << endl;
                estream << "The total size of the file is " << segyFileSize << " while it should be " << position;
                estream << " to contain " << (traceStrides_.size() + 1) << "traces" << endl;
                throw runtime_error(estream.str());
            }
            size_t sizeOfDataSample_ = constants::sizeOfDataSample(segyFile_.getBinaryFileHeader()[rev1::bfh::formatCode]);
            // Push back value into the vector used as buffer
            traceStrides_.push_back(position);
            // Move to the start of the next trace header and read it
            fileStream_.seekg(position);
            // Read trace header
            fileStream_.read(th.get(), TraceHeader::buffer_size);
#ifdef LITTLE_ENDIAN
            // If the system is little endian, bytes must be swapped
            th.invertByteOrder();
#endif        
            // Compute the number of samples in the next trace to update the stride
            size_t nsamples = th[rev0::th::nsamplesTrace];
            traceNsamples_.push_back(nsamples);
            // Update the current stride in the file
            position += TraceHeader::buffer_size + sizeOfDataSample_ * nsamples;
        }
        // Register last position in the file
        fileStream_.seekg(0,ios::end);        
        previousEndOfFile_ = fileStream_.tellg();
    }

}
