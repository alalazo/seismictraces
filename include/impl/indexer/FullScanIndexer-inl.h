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
#include<impl/ObjectFactory-inl.h>
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
        FACTORY_ADD_CREATE(FullScanIndexer)
                
        FullScanIndexer();

        void create_index() override;

        void clear_index() override;

        size_t nsamples(const size_t n) const override;
        
        boost::filesystem::fstream::pos_type position(const size_t n) const override;

        size_t size() const override;
        
        void update_index() override;

        void reset_segy_file(SegyFile& segyFile) override;

    private:
        inline void scanFileAndUpdateIndexFromCurrentPosition();

        SegyFile * m_segy_file;
        boost::filesystem::fstream::pos_type m_previous_end_of_file;
        StorageType m_store;
        
        static bool m_is_registered;
    };
    
    template< class StorageType >
    FullScanIndexer<StorageType>::FullScanIndexer() : m_segy_file(nullptr), m_previous_end_of_file(0)  {
    }
    
    template< class StorageType >
    void FullScanIndexer<StorageType>::reset_segy_file(SegyFile& segyFile) {
        m_segy_file = &segyFile;
        m_store.reset(m_segy_file);
        clear_index();
    }
    
    template< class StorageType >
    void FullScanIndexer<StorageType>::create_index() {
        /// @bug Check if a SEG-Y file is currently set
        m_segy_file->fstream().seekg(3600,std::ios::beg);
        scanFileAndUpdateIndexFromCurrentPosition();
    }

    template< class StorageType >
    void FullScanIndexer<StorageType>::clear_index() {
        m_store.clear();
    }

    template< class StorageType >
    size_t FullScanIndexer<StorageType>::nsamples(const size_t n) const {      
        return m_store.load(n).nsamples();
    }
    
    template< class StorageType >
    boost::filesystem::fstream::pos_type FullScanIndexer<StorageType>::position(const size_t n) const {
        return m_store.load(n).position();
    }
    
    template< class StorageType >
    size_t FullScanIndexer<StorageType>::size() const {
        return m_store.size();
    }
    
    template< class StorageType >
    void FullScanIndexer<StorageType>::update_index() {
        m_segy_file->fstream().seekg( m_previous_end_of_file );
        scanFileAndUpdateIndexFromCurrentPosition();
    }
    
    template< class StorageType >
    void FullScanIndexer<StorageType>::scanFileAndUpdateIndexFromCurrentPosition() {
        boost::filesystem::fstream::pos_type position = m_segy_file->fstream().tellg();
        TraceHeader::smart_reference_type th(TraceHeader::create(m_segy_file->tag()));
        auto segyFileSize = file_size(m_segy_file->path());
        while (true) {
            // Check for end of file
            if (segyFileSize == static_cast<size_t> (position)) {
                // If the end of the file has been reached, then stop reading
                break;
            } else if (segyFileSize < static_cast<size_t> (position)) {
                // If the end of the file has been exceeded, the file is truncated
                std::stringstream estream;
                estream << "FATAL ERROR: " << m_segy_file->path() << " is truncated after trace number " << m_store.size() << std::endl << std::endl;
                estream << "The total size of the file is " << segyFileSize << " while it should be " << position;
                estream << " to contain " << (m_store.size() + 1) << "traces" << std::endl;
                throw std::runtime_error(estream.str());
            }
            size_t sizeOfDataSample_ = constants::sizeOfDataSample(m_segy_file->getBinaryFileHeader()[rev0::bfh::formatCode]);
            // Move to the start of the next trace header and read it
            m_segy_file->fstream().seekg(position);
            // Read trace header
            m_segy_file->fstream().read(th.get(), TraceHeader::buffer_size);
#ifdef LITTLE_ENDIAN
            // If the system is little endian, bytes must be swapped
            th.invertByteOrder();
#endif        
            // Compute the number of samples in the next trace to update the stride
            size_t nsamples = th[rev0::th::nsamplesTrace];
            m_store.push_back(position,nsamples);
            // Update the current stride in the file
            position += TraceHeader::buffer_size + sizeOfDataSample_ * nsamples;
        }
        // Register last position in the file
        m_segy_file->fstream().seekg(0, std::ios::end);
        m_previous_end_of_file = m_segy_file->fstream().tellg();
    }
        
}
#endif	/* FULLSCANINDEXER_INL_H_20140826 */

