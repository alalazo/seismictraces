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

/**
 * @file FullScanIndexer-inl.h
 * @brief Implementation of a SegyFileIndexer that performs a 
 * full scan of the file
 */

#ifndef FULLSCANINDEXER_INL_H_20140826
#define	FULLSCANINDEXER_INL_H_20140826

#include<impl/SegyFileIndexer.h>
#include<SegyFile.h>
#include<impl/SegyFile-TraceHeader.h>
#include<impl/rev0/SegyFile-BinaryFileHeader-Rev0.h>

#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>

#include<iostream>
#include<sstream>
#include<stdexcept>

namespace seismic {

    template< class StorageType >
    class FullScanIndexer : public SegyFileIndexer {
    public:

        FullScanIndexer(SegyFile& segyFile, boost::filesystem::fstream& fileStream)
        : SegyFileIndexer(segyFile, fileStream), segyFile_(segyFile), fileStream_(fileStream),
        previousEndOfFile_(0), store_(segyFile) {
        }

        void createIndex() override;

        size_t nsamples(const size_t n) const override;
        
        boost::filesystem::fstream::pos_type position(const size_t n) const override;

        size_t size() const override;
        
        void updateIndex() override;

    private:
        inline void scanFileAndUpdateIndexFromCurrentPosition();

        SegyFile& segyFile_;
        boost::filesystem::fstream& fileStream_;
        boost::filesystem::fstream::pos_type previousEndOfFile_;
        StorageType store_;
    };

    template< class StorageType >
    void FullScanIndexer<StorageType>::createIndex() {
        fileStream_.seekg(3600);
        scanFileAndUpdateIndexFromCurrentPosition();
    }

    template< class StorageType >
    size_t FullScanIndexer<StorageType>::nsamples(const size_t n) const {      
        return store_.load(n).nsamples();
    }
    
    template< class StorageType >
    boost::filesystem::fstream::pos_type FullScanIndexer<StorageType>::position(const size_t n) const {
        return store_.load(n).position();
    }
    
    template< class StorageType >
    size_t FullScanIndexer<StorageType>::size() const {
        return store_.size();
    }
    
    template< class StorageType >
    void FullScanIndexer<StorageType>::updateIndex() {
        fileStream_.seekg( previousEndOfFile_ );
        scanFileAndUpdateIndexFromCurrentPosition();
    }
    
    template< class StorageType >
    void FullScanIndexer<StorageType>::scanFileAndUpdateIndexFromCurrentPosition() {
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
                std::stringstream estream;
                estream << "FATAL ERROR: " << segyFile_.path() << " is truncated after trace number " << store_.size() << std::endl << std::endl;
                estream << "The total size of the file is " << segyFileSize << " while it should be " << position;
                estream << " to contain " << (store_.size() + 1) << "traces" << std::endl;
                throw std::runtime_error(estream.str());
            }
            size_t sizeOfDataSample_ = constants::sizeOfDataSample(segyFile_.getBinaryFileHeader()[rev0::bfh::formatCode]);
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
            store_.push_back(position,nsamples);
            // Update the current stride in the file
            position += TraceHeader::buffer_size + sizeOfDataSample_ * nsamples;
        }
        // Register last position in the file
        fileStream_.seekg(0, std::ios::end);
        previousEndOfFile_ = fileStream_.tellg();

    }
}
#endif	/* FULLSCANINDEXER_INL_H_20140826 */

