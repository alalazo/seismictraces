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
 * @file SegyFileLazyWriter.h
 * @brief Lazy writer for SEG Y files
 */
#ifndef SEGYFILELAZYWRITER_H
#define	SEGYFILELAZYWRITER_H

#include<SegyFile.h>

#include<boost/filesystem/fstream.hpp>

#include<map>
#include<sstream>
#include<vector>

#include "rev0/SegyFile-Fields-Rev0.h"

namespace seismic {
    
    class SegyFileIndexer;
    
    /**
     * @brief Manages lazy writing of traces to a SEG Y file
     */
    class SegyFileLazyWriter {
    public:
        
        /**
         * @brief Constructor from an indexer
         * 
         * @param[in] indexer indexer of a SEG Y file
         */
        explicit SegyFileLazyWriter(SegyFileIndexer& indexer, boost::filesystem::fstream& fileStream);
        
        /**
         * @brief Add a trace to the overwrite queue
         * 
         * @param[in] trace trace to be written
         * @param[in] n id of the trace
         */
        void addToOverwriteQueue(const SegyFile::trace_type& trace, size_t n);
        
        /**
         * @brief Add a trace to the append queue
         * 
         * @param[in] trace trace to be appended
         */
        void addToAppendQueue(const SegyFile::trace_type& trace, size_t sizeOfDataSample);
        
        /**
         * @brief Commit changes to file and update index
         */
        void commit(size_t sizeOfDataSample);
    
    private:
        SegyFileIndexer& indexer_;
        boost::filesystem::fstream& fileStream_;
        
        std::map<size_t, SegyFile::trace_type> overwriteMap_;
        std::vector<char> appendVector_;
    };
    
}

#endif	/* SEGYFILELAZYWRITER_H */

