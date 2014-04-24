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
#include<impl/rev1/SegyFile-Fields-Rev1.h>

namespace seismic {
    namespace rev1 {
        // Binary file header
        namespace bfh {
            // Fields that are mapped to int16_t
            const Int16Field segyFormatRevisionNumber = 300;
            const Int16Field fixedLengthTraceFlag = 302;
            const Int16Field nextendedTextualFileHeader = 304;
        }
        // Trace header
        namespace th {
            // Fields that are mapped to int32_t
            const Int32Field ensembleCoordinateX = 180;
            const Int32Field ensembleCoordinateY = 184;
            const Int32Field inlineNumber = 188;
            const Int32Field crosslineNumber = 192;
            const Int32Field shotpointNumber = 196;
            const Int32Field transductionConstantMantissa = 204;
            const Int32Field sourceMeasurementMantissa = 224;
            // Fields that are mapped to int16_t
            const Int16Field scalarShotpointNumber = 200;
            const Int16Field traceValueMeasurementUnit = 202;
            const Int16Field transductionConstantExponent = 208;
            const Int16Field transductionUnits = 210;
            const Int16Field traceIdentifier = 212;
            const Int16Field scalarTime = 214;
            const Int16Field sourceOrientation = 216;
            const Int16Field sourceMeasurementExponent = 228;
            const Int16Field sourceMeasurementUnit = 230;
        }
    }
}
