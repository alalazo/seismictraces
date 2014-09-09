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
 * @file InMemoryIndexer.h
 * @brief Indexer that keeps every information in memory
 */
#ifndef INMEMORYINDEXER_H
#define	INMEMORYINDEXER_H

#include<impl/indexer/FullScanIndexer-inl.h>
#include<impl/indexer/IndexItem-inl.h>
#include<impl/SegyFileIndexer.h>

#include<boost/filesystem/fstream.hpp>

#include<vector>

namespace seismic {
        
    class InMemoryStorage {
    public:
        
        template<class T, class U>        
        void push_back(T&& position,U&& nsamples) {
            m_index.emplace_back(position,nsamples);
        }
        
        size_t size() const {
            return m_index.size();
        }
        
        IndexItem load(size_t n) const {
            /// @todo Check performance issues related to range-checked access
            return m_index.at(n);
        }
        
        void reset(SegyFile* file) {
            clear();
        }
        
        void clear() {
          m_index.clear();
        }
        
    private:
        std::vector<IndexItem> m_index;
    };
    
    
    /**
     * @brief Implementation of the SegyFileIndexer interface that maintains
     * information in memory
     * 
     * @todo Write a broader documentation
     */
    using InMemoryIndexer = FullScanIndexer<InMemoryStorage>;

}

#endif	/* INMEMORYINDEXER_H */

