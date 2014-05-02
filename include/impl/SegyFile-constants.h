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
 * @file SegyFile-constants.h
 * @brief Contains all the enumerations and constants needed to describe a SEGY file
 */
#ifndef SEGYFILE_CONSTANTS_H
#define	SEGYFILE_CONSTANTS_H

#include<stdexcept>

#include<cstdint>

namespace seismic {
    namespace constants {

        /**
         * @brief Exposes an enumeration of the possible "Data sample format code"
         */
        struct SegyFileFormatCode {

            enum {
                /// 4-byte IBM floating-point
                IBMfloat32 = 1,
                /// 4-byte, two's complement integer
                Int32 = 2,
                /// 2-byte, two's complement integer
                Int16 = 3,
                /// 4-byte fixed-point with gain (obsolete)
                Fixed32 = 4,
                /// 4-byte IEEE floating-point
                IEEEfloat32 = 5,
                /// 1-byte, two's complement integer
                Int8 = 8
            };
        };

        /**
         * @brief Returns the size of a single data sample given the format code
         * 
         * @param[in] format code
         * @return size of a single data sample
         * 
         * @relates SegyFileFormatCode
         */
        inline size_t sizeOfDataSample(const int16_t obj) {
            size_t value(0);
            switch ( obj ) {
                case ( SegyFileFormatCode::IBMfloat32 ):
                case ( SegyFileFormatCode::Int32      ):
                case ( SegyFileFormatCode::Fixed32    ):
                case ( SegyFileFormatCode::IEEEfloat32):
                    value = 4;
                    break;
                case ( SegyFileFormatCode::Int16      ):
                    value = 2;
                    break;
                case ( SegyFileFormatCode::Int8       ):
                    value = 1;
                    break;
                default:
                    throw std::runtime_error("Invalid \"Data sample format code\"\n");
                    break;
            }
            return value;
        }
        
        /**
         * @brief Exposes an enumeration of the possible "Trace sorting code"
         */
        struct TraceSortingCode {

            enum {
                /// Other (should be explained in user Extended Textual File Header stanza
                other = -1,
                /// Unknown
                unknown = 0,
                /// As recorded (no sorting)
                asRecorder = 1,
                /// CDP ensemble
                CDPEnsemble = 2,
                /// Single fold continuous profile
                singleFoldContinuousProfile = 3,
                /// Horizontally stacked
                horizontallyStacked = 4,
                /// Common source point
                commonSourcePoint = 5,
                /// Common receiver point
                commonReceiverPoint = 6,
                /// Common offset point
                commonOffsetPoint = 7,
                /// Common mid-point
                commonMidPoint = 8,
                /// Common conversion point
                commonConversionPoint = 9
            };
        };

        /**
         * @brief Exposes an enumeration of the possible "Sweep type code"
         */
        struct SweepTypeCode {

            enum {
                /// linear
                linear = 1,
                /// parabolic
                parabolic = 2,
                /// exponential
                exponential = 3,
                /// other
                other = 4
            };
        };

        /**
         * @brief Exposes an enumeration of the possible "Taper type"
         */
        struct TaperType {

            enum {
                /// linear
                linear = 1,
                /// \f$ cos^2 \f$
                cos2 = 2,
                /// other
                other = 3
            };
        };

        /**
         * @brief Exposes an enumeration of the possible "Correlated data traces"
         */
        struct CorrelatedDataTraces {

            enum {
                /// no
                no = 1,
                /// yes
                yes = 2
            };
        };

        /**
         * @brief Exposes an enumeration of the possible "Binary gain recovered"
         */
        struct BinaryGainRecovered {

            enum {
                /// yes
                yes = 1,
                /// no
                no = 2
            };
        };

        /**
         * @brief Exposes an enumeration of the possible "Amplitude recovery method"
         */
        struct AmplitudeRecoveryMethod {

            enum {
                /// none
                none = 1,
                /// spherical divergence
                sphericalDivergence = 2,
                /// AGC
                AGC = 3,
                /// other
                other = 4
            };
        };

        /**
         * @brief Exposes an enumeration of the possible "Measurement system"
         */
        struct MeasurementSystem {

            enum {
                /// meters
                meters = 1,
                /// feet
                feet = 2
            };
        };

        /**
         * @brief Exposes an enumeration of the possible "Impulse signal polarity"
         */
        struct ImpulseSignalPolarity {
            enum {
                /// Increase in pressure or upward geophone case movement gives negative number on tape
                negativeNumbers = 1,
                /// Increase in pressure or upward geophone case movement gives positive number on tape
                positiveNumbers = 2
            };
        };
        
        /**
         * @brief Exposes an enumeration of the possible "Data use"
         */
        struct DataUse {
            enum {
                /// Production
                production = 1,
                /// Test
                test = 2
            };
        };
        
        /**
         * @brief Exposes an enumeration of the possible "Coordinate units"
         */
        struct CoordinateUnits {
            enum {
                /// Length (meters or feet)
                length = 1,
                /// Seconds of arc
                secondsOfArc = 2,
                /// Decimal degrees
                decimalDegrees = 3,
                /// Degrees, minutes, seconds (DMS)
                degreesMinutesseconds = 4
            };
        };
        
        /**
         * @brief Exposes an enumeration of the possible "Time basis code"
         */
        struct TimeBasisCode {
            enum {
                /// Local
                local = 1,
                /// GMT (Greenwich Mean Time)
                GMT = 2,
                /// Other (should be explained in a user defined stanza in the Extended Textual File Header)
                other = 3,
                /// UTC (Coordinated Universal Time)
                UTC = 4
            };
        };
        
        /**
         * @brief Exposes an enumeration of the possible "Time basis code"
         */
        struct OverTravel {
            enum {
                /// down (or behind))
                down = 1,
                /// up (or ahead)
                up = 2
            };
        };
        /**
         * @brief Exposes an enumeration of the possible "Trace value measurement unit"
         */
        struct MeasurementUnit {
            enum {
                /// Other (should be described in Data Sample Measurement Units Stanza)
                other = -1,
                /// Unknown
                unknown = 0,
                /// Pascal (Pa)
                Pascal = 1,
                /// Volts (v)
                Volts = 2,
                /// Millivolts (mV)
                milliVolts = 3,
                /// Amperes (A)
                Amperes = 4,
                /// Meters (m)
                Meters = 5,
                /// Meters per second (m/s)
                MetersPerSecond = 6,
                /// Meters per second squared (m/s2)
                MetersPerSecondSquared = 7,
                /// Newton (N)
                Newton = 8,
                /// Watt (W) 
                Watt = 9
            };
        } ;
    }
}

#endif	/* SEGYFILE_CONSTANTS_H */

