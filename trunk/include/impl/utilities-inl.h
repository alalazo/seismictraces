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
 * @file utilities-inl.h
 * @brief Utility functions
 */
#ifndef UTILITIES_INL_H
#define	UTILITIES_INL_H

#include<algorithm>
#include<cstdint>

namespace seismic {

    ////////////////////
    //// Byte order 
    ////////////////////            
    
    /**
     * @brief Invert in place the byte order of a generic object in memory
     * 
     * This function has been designed to be used with built-in types
     * 
     * @tparam T type of the object 
     * 
     * @param obj object whose byte order is to be inverted
     */
    template< class T >
    inline void invertByteOrder(T& obj) {
        char * pnt = reinterpret_cast<char*> (&obj);
        std::reverse( pnt,pnt+sizeof(T) );
    }

    /**
     * @brief Invert in place the byte order of a stream of bytes
     * 
     * @param stream pointer to the beginning of the stream
     * @param size size of the stream
     */
    inline void invertByteOrder( char * stream, const size_t size) {        
        std::reverse(stream,stream+size);
    }    
    
    ////////////////////
    //// Format conversion
    ////////////////////            

    /**
     * @brief Convert a 4 bytes value from IEEE-754 format to IBM floating point format
     * 
     * @param[in,out] value value to be converted
     */
    inline void ieee2ibm(int32_t& value) {
        int32_t fconv = value;
        if (fconv) {
            int32_t fmant = (0x007fffff & fconv) | 0x00800000;
            int32_t t = (int32_t) ((0x7f800000 & fconv) >> 23) - 126;
            while (t & 0x3) {
                ++t;
                fmant >>= 1;
            }
            fconv = (0x80000000 & fconv) | (((t >> 2) + 64) << 24) | fmant;
        }
        value = fconv;
    }


    /**
     * @brief Convert a 4 bytes value from IBM floating point format to IEEE-754 format
     * 
     * @param[in,out] value value to be converted
     */
    inline void ibm2ieee(int32_t& value) {
        int32_t fconv = value;
        int32_t fmant = 0x00ffffff & fconv;
        if (!fmant)
            fconv = 0;
        else {
            int32_t t = (int32_t) ((0x7f000000 & fconv) >> 22) - 130;
            while (!(fmant & 0x00800000)) {
                --t;
                fmant <<= 1;
            }
            if (t > 254) fconv = (0x80000000 & fconv) | 0x7f7fffff;
            else if (t <= 0) fconv = 0;
            else fconv = (0x80000000 & fconv) | (t << 23) | (0x007fffff & fmant);
        }
        value = fconv;
    }
    
    /// Mapping from EBCDIC format to ASCII format
    extern const unsigned char e2a[256];
    /// Mapping from ASCII format to EBCDIC format
    extern const unsigned char a2e[256];
    
    /**
     * @brief Converts an EBCDIC character to the corresponding ASCII character
     * 
     * @param[in,out] value character to be converted
     */
    inline void ebcdic2ascii(unsigned char& value) {
        value = e2a[value];
    }
    
    /**
     * @brief Converts an ASCII character to the corresponding EBCDIC character
     * 
     * @param[in,out] value character to be converted
     */
    inline void ascii2ebcdic(unsigned char& value) {
        value = a2e[value];
    }
    
}

#endif	/* UTILITIES_INL_H */

