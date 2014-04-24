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
 * @file metafunctions-inl.h
 * @brief Generic meta-functions needed in the implementation of the library
 */
#ifndef METAFUNCTIONS_INL_H
#define	METAFUNCTIONS_INL_H

#include<cstdint>

namespace seismic {
    
    /**
     * @brief Bundles the stride in a byte-stream and the type to which a chink of 
     * bytes has to be casted
     * 
     * @tparam R underlying type of the chunk of bytes at stride value_
     */
    template< class R>
    struct Field {
        /// Using declaration of the return type
        using type = R;
        
        /**
         * @brief Constructor from anything that can be converted to long long int
         * 
         * @param value stride in a byte stream
         */
        template< class T >
        Field(T value) : value_(value){}
        
        /// Stride in a byte-stream
        const long long int value_;
    };
        
    using Int32Field = Field<int32_t>;
    using Int16Field = Field<int16_t>;    
}

#endif	/* METAFUNCTIONS_INL_H */

