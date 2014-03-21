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

namespace seismic {

    namespace meta {

        /**
         * @brief Computes the return type for an overload of the
         * subscript operator taking an instance of type T as input
         * 
         * @tparam T input type 
         */
        template<class T>
        struct subscript_return_type {
        };

        /**
         * @brief Aggregates the information on subscript return type
         * to a generic class. Useful for named enumerations.
         * 
         * @tparam input type
         */
        template<class T>
        struct SubscriptReturnTypeAggregator {
            typedef typename subscript_return_type<T>::type type;

            SubscriptReturnTypeAggregator(T value) : value_(value) {
            }

            const T value_;
        };
    }

    /**
     * @brief Convenience function to deduce type T and instantiate a 
     * SubscriptReturnTypeAggregator<T> object
     * 
     * @tparam input type
     * 
     * @param id value
     * @return SubscriptReturnTypeAggregator<T> 
     */
    template<class T>
    meta::SubscriptReturnTypeAggregator<T> field(T id) {
        return meta::SubscriptReturnTypeAggregator<T>(id);
    }

    /**
     * @brief Convenience macro to set the subscript return type 
     * by a specialization of the subcript_return_type meta-function          
     */
#define SET_SUBSCRIPT_RETURN_TYPE( T, RETURN_TYPE) \
    namespace meta { \
        template<> \
        struct subscript_return_type< T > { \
            typedef RETURN_TYPE type; \
        }; \
    }
}

#endif	/* METAFUNCTIONS_INL_H */

