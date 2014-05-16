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

#include<impl/SegyFileIndexer.h>

#include<boost/filesystem/fstream.hpp>

#include<vector>

namespace seismic {

    class InMemoryIndexer : public SegyFileIndexer {
    public:

        InMemoryIndexer(SegyFile& segyFile, boost::filesystem::fstream& fileStream);

        void createIndex() override;

        boost::filesystem::fstream::pos_type position(const size_t n) const override;

        void updateIndex() override;

        size_t nsamples(const size_t n) const override;

        size_t size() const override;

    private:
        void scanFileAndUpdateIndexFromCurrentPosition();
        
        SegyFile& segyFile_;
        boost::filesystem::fstream& fileStream_;
        std::vector<boost::filesystem::fstream::pos_type> traceStrides_;
        std::vector<size_t> traceNsamples_;
        boost::filesystem::fstream::pos_type previousEndOfFile_;
    };

}

#endif	/* INMEMORYINDEXER_H */

