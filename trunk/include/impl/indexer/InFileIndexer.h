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

#include<SegyFile.h>
#include<impl/indexer/IndexItem-inl.h>

#include<boost/filesystem/fstream.hpp>

#include "FullScanIndexer-inl.h"

namespace seismic {

    class InFileStorage {
    public:

        explicit InFileStorage(SegyFile& file)
        : file_(file), size_(0),
        stream_( file_.path().filename().replace_extension("index"), std::ios::binary ) {            
        }

        template<class T, class U>        
        void push_back(T&& position,U&& nsamples) {
            IndexItem item(position,nsamples);
            stream_.write(reinterpret_cast<char*>(&item),sizeof(IndexItem));
            size_++;
        }
        
        size_t size() const {
            return size_;
        }        
        
        IndexItem load(size_t n) const {
            IndexItem item;
            stream_.seekg( n * sizeof(IndexItem) );
            stream_.read(reinterpret_cast<char*>(&item),sizeof(IndexItem));
            return item;
        }
        
    private:
        SegyFile& file_;
        size_t size_;
        mutable boost::filesystem::fstream stream_;
    };

    using InFileIndexer = FullScanIndexer<InFileStorage>;
    //    class InFileIndexer : public SegyFileIndexer {
    //    public:
    //
    //        InFileIndexer(SegyFile& segyFile, boost::filesystem::fstream& fileStream);
    //
    //        void createIndex() override;
    //
    //        size_t nsamples(const size_t n) const override;
    //
    //        boost::filesystem::fstream::pos_type position(const size_t n) const override;
    //
    //        size_t size() const override;
    //
    //        void updateIndex() override;
    //
    //    private:        
    //        SegyFile& segyFile_;
    //        boost::filesystem::fstream& fileStream_;        
    //    };    
}

#endif	/* INFILEINDEXER_H_20140826 */

