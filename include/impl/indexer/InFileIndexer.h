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
 * @file InFileIndexer.h
 * @brief Indexer that stores information in a file
 * Created on August 26, 2014, 8:50 PM
 */
#ifndef INFILEINDEXER_H_20140826
#define	INFILEINDEXER_H_20140826

#include<impl/indexer/FullScanIndexer-inl.h>

#include<impl/indexer/IndexItem-inl.h>

#include<boost/filesystem/fstream.hpp>

namespace seismic {

    class InFileStorage {
    public:

        template<class T, class U>        
        void push_back(T&& position,U&& nsamples) {
            IndexItem item(position,nsamples);
            m_stream.seekp(0,std::ios::end);
            m_stream.write(reinterpret_cast<char*>(&item),sizeof(IndexItem));
            m_size++;
        }
        
        size_t size() const {
            return m_size;
        }        
        
        IndexItem load(size_t n) const {
            IndexItem item;
            m_stream.seekg( n * sizeof(IndexItem), std::ios::beg );
            m_stream.read(reinterpret_cast<char*>(&item),sizeof(IndexItem));
            return item;
        }
        
        void reset(SegyFile * file) {            
            /// @todo check if this is the right open mode
            m_index_filename = file->path();
            m_index_filename.replace_extension("index");
            clear();
        }
        
        void clear() {
            m_stream.close();
            { // For some reason these two lines create an empty index file
              // while just closing, removing and reopening does not
              remove(m_index_filename);
              boost::filesystem::fstream tmp(m_index_filename, std::ios::binary | std::ios::out);
            }
            m_stream.open(m_index_filename,std::ios::binary|std::ios::in|std::ios::out);
            m_size = 0;
        }
        
    private:
        boost::filesystem::path m_index_filename;
        size_t m_size{0};
        mutable boost::filesystem::fstream m_stream;
    };

    using InFileIndexer = FullScanIndexer<InFileStorage>;    
}

#endif	/* INFILEINDEXER_H_20140826 */

