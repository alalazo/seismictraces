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
 * @file SegyFileIndexer.h
 * 
 * @brief Interface to create index for random access to SEG Y files
 */
#ifndef SEGYFILEINDEXER_H
#define	SEGYFILEINDEXER_H

#include<impl/ObjectFactory-inl.h>

#include<boost/filesystem/fstream.hpp>

#include<string>

namespace seismic {
    
    class SegyFile;
    
    /**
     * @brief Interface to a generic indexer
     * 
     * The concept behind the interface
     * -----
     * 
     * The format of a SEG-Y file is __inherently serial__.
     * 
     * To avoid losing performance at each access the concept of an indexer is 
     * introduced in the implementation of the SegyFile class. The basic idea is
     * to _scan the SEG-Y file only once_ and store index information for later access. 
     * 
     * It is left to implementation to decide:
     *   - how to scan a SEG-Y file
     *   - where to store the index information
     * 
     * The SegyFile class is implemented in terms of this interface, and can be
     * customized with different indexing strategies.
     * 
     */
    class SegyFileIndexer {
    public:
        /**
         * @brief Resets the SEG-Y file to be indexed
         * 
         * @param[in] segyFile SEG Y file to be indexed
         */
        virtual void reset_segy_file(SegyFile& segyFile) = 0;
        
        /**
         * @brief Creates the index of the SEG Y file
         */
        virtual void create_index() = 0;
        
        /**
         * @brief Clears the current index
         */
        virtual void clear_index() = 0;
        
        /**
         * @brief Returns the absolute position of a trace in a file
         * 
         * @param[in] n trace id
         * 
         * @return absolute position of the trace
         */
        virtual boost::filesystem::fstream::pos_type position(const size_t n) const = 0;
        
        /**
         * @brief Returns the total number of indexed traces
         * 
         * @return total number of indexed traces
         */
        virtual size_t size() const = 0;
        
        /**
         * @brief Returns the number of samples for a trace in a file
         * 
         * @param[in] n trace id
         * 
         * @return number of samples
         */
        virtual size_t nsamples(const size_t n) const = 0;
        
        /**
         * @brief Updates the index of the SEG Y file
         */
        virtual void updateIndex() = 0;
        
        /**
         * @brief The infamous virtual destructor
         */
        virtual ~SegyFileIndexer() {
        }
        
        INTERFACE_USE_FACTORY(SegyFileIndexer,std::string)
    };
        
}

#endif	/* SEGYFILEINDEXER_H */

