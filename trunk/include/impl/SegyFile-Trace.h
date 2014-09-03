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
 * @file SegyFile-Trace.h
 * @brief Trace contained in a SEG-Y file
 */

#ifndef SEGYFILE_TRACE_H
#define	SEGYFILE_TRACE_H

#include<impl/SegyFile-TraceHeader.h>
#include<impl/rev0/SegyFile-Fields-Rev0.h>
#include<vector>

namespace seismic {

    /**
     * @brief Represents a SEG-Y file trace
     * 
     * A SEG-Y file trace is nothing but an aggregation of a trace header
     * (meta-data) and a vector<T> (data)
     */
    template<class T>
    class Trace : public std::vector<T>, public TraceHeader::smart_reference_type {
    public:

        /**
         * @brief Construct an empty trace from a trace header pointer
         * 
         * @param[in] th pointer to a trace header
         */
        Trace(TraceHeader::smart_reference_type th) : TraceHeader::smart_reference_type(th) {
            updateNumberOfSamples();
        }

        //////////
        // Disambiguates subscript operator
        //////////        
        using TraceHeader::smart_reference_type::operator[];
        using std::vector<T>::operator[];
        
        //////////
        // Modifying operations on vector
        //////////
        
        /**
         * @brief Remove all elements from the trace
         */
        void clear() {
            std::vector<T>::clear();
            updateNumberOfSamples();
        }

        template<class V>
        void push_back(V&& value) {
            std::vector<T>::push_back(std::forward<V>(value));
            updateNumberOfSamples();
        }
        
        /// @todo HIDE ALL THE OTHER FUNCTIONS THAT ADD REMOVE ELEMENTS
        
        /**
         * @brief Disallows explicit conversion to the underlying trace data
         */
        explicit operator std::vector<T>&() = delete;

        /**
         * @brief Disallows explicit conversion to the underlying trace data
         */
        explicit operator const std::vector<T>&() const = delete;
        
    private:

        /**
         * @brief Updates the number of samples stored in the trace header
         */
        void updateNumberOfSamples() {
            (*this)[rev0::th::nsamplesTrace] = this->size();
        }
    };

    template<class T>
    void read(std::istream& inputStream, Trace<T>& trace) {
        auto nSamples = trace.size();
        auto sizeOfDataSample = sizeof(typename Trace<T>::value_type);
        inputStream.read(reinterpret_cast<char*>(trace.data()), nSamples * sizeOfDataSample);
#ifdef LITTLE_ENDIAN
        // If the system is little endian, bytes must be swapped
        for( auto& x : trace ) {
            invertByteOrder(x);
        }        
#endif  
    }

}

#endif	/* SEGYFILE_TRACE_H */

