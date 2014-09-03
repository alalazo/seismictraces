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
 * @file IndexItem-inl.h
 * @brief Defines the structure of an index item
 */
#ifndef INDEXITEM_INL_H_20140826
#define	INDEXITEM_INL_H_20140826

#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>

#include<utility>

namespace seismic {
    
    /**
     * @brief DEfines the information needed to index a trace in a SEG-Y file
     * for a later random access
     */
    class IndexItem {
    public:
        /// Type that represents the number of samples in a trace
        using nsamples_type = size_t;
        /// Type that represents a position in a file
        using position_type = boost::filesystem::fstream::pos_type;
        
        IndexItem(){}
        
        template<class T, class U>
        IndexItem(T&& position, U&& nsamples) {
            value_ = std::make_pair(position,nsamples);
        }
        
        /**
         * @brief Returns the position of the item
         * 
         * @return position
         */
        position_type position() const {
            return value_.first;
        }
        
        /**
         * @brief Returns the number of samples of the item
         * 
         * @return number of samples
         */
        nsamples_type nsamples() const {
            return value_.second;
        }
        
    private:
        std::pair<position_type,nsamples_type> value_;
    };
    
}


#endif	/* INDEXITEM_INL_H_20140826 */

