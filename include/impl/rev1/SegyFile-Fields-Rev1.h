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
#ifndef SEGYFILE_FIELDS_REV1_H
#define	SEGYFILE_FIELDS_REV1_H

#include<impl/metafunctions-inl.h>
#include<impl/rev0/SegyFile-Fields-Rev0.h>

namespace seismic {

    /**
     * @brief Template tag to intantiate a Rev1 conforming class
     */
    class Rev1 {
    };

    /**
     * @brief Constants used in SEG-Y format revision 1
     */
    namespace rev1 {

        /**
         * @addtogroup BfhConstants
         * @{
         */

        /**
         * @brief Binary file header constants
         */
        namespace bfh {
            using namespace rev0::bfh;

            /// > SEG Y Format Revision Number
            /// >
            /// > This is a 16-bit unsigned value with a Q-point between the first
            /// > and second bytes. Thus for SEG Y Revision 1.0, as defined in 
            /// > this document, this will be recorded as 010016.  
            /// >
            /// > This field is mandatory for all versions of SEG Y, although a 
            /// > value of zero indicates “traditional” SEG Y conforming to the 
            /// > 1975 standard
            extern const Int16Field segyFormatRevisionNumber;
            /// > Fixed length trace flag
            /// >
            /// > A value of one indicates that all traces in this SEG Y file are 
            /// > guaranteed to have the same sample interval and number of 
            /// > samples, as specified in Textual File Header bytes 3217-3218 
            /// > and 3221-3222.
            /// >
            /// > A value of zero indicates that the length of the traces in the 
            /// > file may vary and the number of samples in bytes 115-116 of the 
            /// > Trace Header must be examined to determine the actual length of 
            /// > each trace. This field is mandatory for all versions of SEG Y, 
            /// > although a value of zero indicates “traditional” SEG Y 
            /// > conforming to the 1975 standard.
            extern const Int16Field fixedLengthTraceFlag;
            /// > Number of 3200-byte, Extended Textual File Header records following the Binary Header
            /// >
            /// > A value of zero indicates there are no Extended Textual File 
            /// > Header records (i.e. this file has no Extended Textual File 
            /// > Header(s)).
            /// >
            /// > A value of -1 indicates that there are a variable number of 
            /// > Extended Textual File Header records and the end of the Extended
            /// > Textual File Header is denoted by an ((SEG: EndText)) stanza in 
            /// > the final record. 
            /// > 
            /// > A positive value indicates that there are exactly that many 
            /// > Extended Textual File Header records. Note that, although the 
            /// > exact number of Extended Textual File Header records may be a 
            /// > useful piece of information, it will not always be known at the
            /// > time the Binary Header is written and it is not mandatory that a
            /// > positive value be recorded here.  This field is mandatory for
            /// > all versions of SEG Y, although a value of zero indicates 
            /// > “traditional” SEG Y conforming to the 1975 standard
            extern const Int16Field nextendedTextualFileHeader;
        }

        /**
         * @}
         */

        /**
         * @addtogroup ThConstants
         * @{
         */
        /**
         * @brief Trace header constants
         */
        namespace th {
            using namespace rev0::th;

            /// > X coordinate of ensemble (CDP) position of this trace (scalar in Trace Header bytes 71-72 applies)
            /// >
            /// > The coordinate reference system should be identified through an 
            /// > extended header Location Data stanza (see section D-1)
            extern const Int32Field ensembleCoordinateX;
            /// > Y coordinate of ensemble (CDP) position of this trace (scalar in bytes Trace Header 71-72 applies)
            /// >
            /// > The coordinate reference system should be identified through an
            /// > extended header Location Data stanza (see section D-1)
            extern const Int32Field ensembleCoordinateY;
            /// > For 3-D poststack data, this field should be used for the in-line number
            /// >
            /// > If one in-line per SEG Y file is being recorded, this value 
            /// > should be the same for all traces in the file and the same value
            /// > will be recorded in bytes 3205-3208 of the Binary File Header
            extern const Int32Field inlineNumber;
            /// > For 3-D poststack data, this field should be used for the cross-line number
            /// >
            /// > This will typically be the same value as the ensemble (CDP) 
            /// > number in Trace Header bytes 21-24, but this does not have to 
            /// > be the case
            extern const Int32Field crosslineNumber;
            /// > Shotpoint number 
            /// >
            /// > This is probably only applicable to 2-D poststack data. 
            /// > Note that it is assumed that the shotpoint number refers to the 
            /// > source location nearest to the ensemble (CDP) location for a 
            /// > particular trace. If this is not the case, there should be a 
            /// > comment in the Textual File Header explaining what the 
            /// > shotpoint number actually refers to
            extern const Int32Field shotpointNumber;
            /// > Transduction Constant 
            /// >
            /// > The multiplicative constant used to convert the Data Trace 
            /// > samples to the Transduction Units (specified in Trace Header 
            /// > bytes 211-212). The constant is encoded as a four-byte, two's 
            /// > complement integer (bytes 205-208) which is the mantissa and a 
            /// > two-byte, two's complement integer (bytes 209-210) which is the 
            /// > power of ten exponent (i.e. Bytes 205-208 * 10**Bytes 209-210)
            extern const Int32Field transductionConstantMantissa;
            /// > Source Measurement 
            /// > 
            /// > Describes the source effort used to generate the trace. The 
            /// > measurement can be simple, qualitative measurements such as the
            /// > total weight of explosive used or the peak air gun pressure or 
            /// > the number of vibrators times the sweep duration. Although these
            /// > simple measurements are acceptable, it is preferable to use true
            /// > measurement units of energy or work.
            /// >
            /// > The constant is encoded as a four-byte, two's complement integer
            /// > (bytes 225-228) which is the mantissa and a two-byte, two's 
            /// > complement integer (bytes 209-230) which is the power of ten 
            /// > exponent (i.e. Bytes 225-228 * 10**Bytes 229-230)
            extern const Int32Field sourceMeasurementMantissa;

            /// > Scalar to be applied to the shotpoint number in Trace Header bytes 197-200 to give the real value
            /// > 
            /// > If positive, scalar is used as a multiplier; if negative as a 
            /// > divisor; if zero the shotpoint number is not scaled (i.e. it is 
            /// > an integer. A typical value will be -10, allowing shotpoint 
            /// > numbers with one decimal digit to the right of the decimal
            /// > point)
            extern const Int16Field scalarShotpointNumber;
            /// > Trace value measurement unit
            /// >
            /// > @see constants::MeasurementUnit
            extern const Int16Field traceValueMeasurementUnit;
            /// > Transduction Constant 
            /// >
            /// > The multiplicative constant used to convert the Data Trace 
            /// > samples to the Transduction Units (specified in Trace Header 
            /// > bytes 211-212). The constant is encoded as a four-byte, two's 
            /// > complement integer (bytes 205-208) which is the mantissa and a 
            /// > two-byte, two's complement integer (bytes 209-210) which is the 
            /// > power of ten exponent (i.e. Bytes 205-208 * 10**Bytes 209-210)
            extern const Int16Field transductionConstantExponent;
            /// > Transduction Units 
            /// >
            /// > The unit of measurement of the Data Trace samples after they 
            /// > have been multiplied by the Transduction Constant specified in 
            /// > Trace Header bytes 205-210
            /// >
            /// > @see constants::MeasurementUnit
            extern const Int16Field transductionUnits;
            /// > Device/Trace Identifier 
            /// >
            /// > The unit number or id number of the device associated with the 
            /// > Data Trace (i.e. 4368 for vibrator serial number 4368 or 20316 
            /// > for gun 16 on string 3 on vessel 2). This field allows traces 
            /// > to be associated across trace ensembles independently of the 
            /// > trace number (Trace Header bytes 25-28)
            extern const Int16Field traceIdentifier;
            /// > Scalar to be applied to times specified in Trace Header bytes 95-114 to give the true time value in milliseconds
            /// >
            /// > Scalar = 1, +10, +100, +1000, or +10,000.  If positive, scalar 
            /// > is used as a multiplier; if negative, scalar is used as divisor.
            /// > A value of zero is assumed to be a scalar value of 1
            extern const Int16Field scalarTime;
            /// > Source Type/Orientation
            /// >
            /// > Defines the type and the orientation of the energy source. The
            /// > terms vertical, cross-line and in-line refer to the three axes 
            /// > of an orthogonal coordinate system. The absolute azimuthal 
            /// > orientation of the coordinate system axes can be defined in the 
            /// > Bin Grid Definition Stanza (page 28).
            /// >
            /// > -1 to -n = Other
            /// >        0 = Unknown
            /// >        1 = Vibratory - Vertical orientation
            /// >        2 = Vibratory - Cross-line orientation
            /// >        3 = Vibratory - In-line orientation
            /// >        4 = Impulsive - Vertical orientation
            /// >        5 = Impulsive - Cross-line orientation
            /// >        6 = Impulsive - In-line orientation
            /// >        7 = Distributed Impulsive - Vertical orientation
            /// >        8 = Distributed Impulsive - Cross-line orientation
            /// >        9 = Distributed Impulsive - In-line orientation
            extern const Int16Field sourceOrientation;
            /// > Source Measurement 
            /// > 
            /// > Describes the source effort used to generate the trace. The 
            /// > measurement can be simple, qualitative measurements such as the
            /// > total weight of explosive used or the peak air gun pressure or 
            /// > the number of vibrators times the sweep duration. Although these
            /// > simple measurements are acceptable, it is preferable to use true
            /// > measurement units of energy or work.
            /// >
            /// > The constant is encoded as a four-byte, two's complement integer
            /// > (bytes 225-228) which is the mantissa and a two-byte, two's 
            /// > complement integer (bytes 209-230) which is the power of ten 
            /// > exponent (i.e. Bytes 225-228 * 10**Bytes 229-230)
            extern const Int16Field sourceMeasurementExponent;
            /// > Source Measurement Unit 
            /// >
            /// > The unit used for the Source Measurement, Trace header bytes 225-230.
            /// > -1 = Other (should be described in Source Measurement Unit stanza, page 40)
            /// >  0 = Unknown
            /// >  1 = Joule (J)
            /// >  2 = Kilowatt (kW)
            /// >  3 = Pascal (Pa)
            /// >  4 = Bar (Bar)
            /// >  4 = Bar-meter (Bar-m)
            /// >  5 = Newton (N)
            /// >  6 = Kilograms (kg)
            extern const Int16Field sourceMeasurementUnit;
        }
        
        /**
         * @}
         */
    }

}

#endif	/* SEGYFILE_FIELDS_REV1_H */

