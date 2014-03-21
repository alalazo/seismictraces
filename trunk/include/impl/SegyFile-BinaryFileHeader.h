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
 * @file SegyFile-BinaryFileHeader.h
 * @brief Generic interface to a binary file header
 */
#ifndef SEGYFILE_BINARYFILEHEADER_H
#define	SEGYFILE_BINARYFILEHEADER_H

#include<impl/GenericByteStream-inl.h>

#include<vector>
#include<iostream>
#include<string>
#include<memory>

namespace seismic {
    
    typedef GenericByteStream<400> BinaryFileHeader;
    
    /**
     * @brief Master template to be specialized for different standards
     */
    template< class StdTag>
    class ConcreteBinaryFileHeader;
         
}

#endif	/* SEGYFILE_BINARYFILEHEADER_H */

