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
#ifndef SEGYFILE_TRACEHEADER_REV1_H
#define	SEGYFILE_TRACEHEADER_REV1_H

#include<impl/rev0/SegyFile-TraceHeader-Rev0.h>
#include<impl/rev1/SegyFile-Fields-Rev1.h>

namespace seismic {
    
    template<>
    class ConcreteTraceHeader<Rev1> : public ConcreteTraceHeader<Rev0> {
    public:
        /* virtual */
        void print(std::ostream& cout) const;
        /* virtual */
        void invertByteOrder();
        /* virtual */
        void checkConsistencyOrThrow() const;
        /* virtual */
        ConcreteTraceHeader<Rev1> * create() const {
            return new ConcreteTraceHeader<Rev1>;
        }
        
    private:
        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int32Fields
         */
        static const std::vector< Int32Field > Int32List;

        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int16Fields
         */
        static const std::vector< Int16Field > Int16List;

        /**
         * @brief Field needed to register the class into its factory
         */
        static const bool isRegistered;
    };
    
}

#endif	/* SEGYFILE_TRACEHEADER_REV1_H */

