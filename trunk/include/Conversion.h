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
 * @file  Conversion.h
 * @brief Conversion functions between objects of different format
 */
#ifndef CONVERSION_H
#define	CONVERSION_H

#include<SegyFile.h>
#include<SeismicTrace-inl.h>

namespace seismic {
    
    /**
     * @brief Manages conversion between SegyFile::trace_type and SeismicTrace objects
     * 
     * The following is a small example of the basic use of the class:
     * @include example05.cpp     
     */
    class SegyConverter {
    public:
        /**
         * @brief Unique and only constructor
         * 
         * @param[in] bfh binary file header
         */
        explicit SegyConverter(const BinaryFileHeader& bfh) : bfh_(bfh) {}
        
        /**
         * @brief Convert a SegyFile::trace_type object to a SeismicTrace object
         * 
         * @param[in]  segyTrace input trace in SEGY format
         * @param[out] seismicTrace converted output
         */
        void operator()(const SegyFile::trace_type& segyTrace, SeismicTrace& seismicTrace);

        /**
         * @brief Convert a SeismicTrace object to a SegyFile::trace_type object
         * 
         * @param[in] seismicTrace
         * @param[in,out] segyTrace
         */
        void operator()(const SeismicTrace& seismicTrace, SegyFile::trace_type& segyTrace);
        
    private:
        const BinaryFileHeader& bfh_;
    } ;
    
}

#endif	/* CONVERSION_H */

