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
 * @file SegyFile-Fields-Rev0.h
 * @brief Contains constants for SEG-Y format revision 0
 */
#ifndef SEGYFILE_FIELDS_REV0_H
#define	SEGYFILE_FIELDS_REV0_H

#include<impl/metafunctions-inl.h>

/**
 * @brief Main namespace in which all the entities in the library are enclosed
 */
namespace seismic {

    /**
     * @brief Template tag to intantiate a Rev0 conforming class
     */
    class Rev0 {
    };

    /**
     * @brief Constants used in SEG-Y format revision 0
     */
    namespace rev0 {

        /**
         * @addtogroup BfhConstants Binary file header constants
         * 
         * @brief Constants used to identify fields in binary file headers
         * 
         * @{
         */

        /**
         * @brief Binary file header constants
         */
        namespace bfh {
            /// >
            /// > Job identification number
            /// >
            extern const Int32Field jobID;
            /// >
            /// > Line number. For 3-D poststack data, this will typically contain the in-line number
            /// >
            extern const Int32Field lineNumber;
            /// >
            /// > Reel number
            /// >
            extern const Int32Field reelNumber;

            /// >
            /// > Number of data traces per ensemble. __Mandatory for prestack data__
            /// >
            extern const Int16Field nDataTraces;
            /// >
            /// > Number of auxiliary traces per ensemble. __Mandatory for prestack data__
            /// >
            extern const Int16Field nAuxiliaryTraces;
            /// >
            /// > Sample interval in microseconds (µs). __Mandatory for all data types__
            /// >
            extern const Int16Field sampleInterval;
            /// >
            /// > Sample interval in microseconds (µs) of original field recording
            /// >
            extern const Int16Field sampleIntervalOriginalField;
            /// > Number of samples per data trace. __Mandatory for all types of data__ 
            /// >
            /// > The sample interval and number of samples in the Binary 
            /// > File Header should be for the primary set of seismic data traces in the file
            extern const Int16Field nsamplesDataTrace;
            /// >
            /// > Number of samples per data trace for original field recording
            /// >
            extern const Int16Field nsamplesDataTraceOriginalField;
            /// > Data sample format code.  __Mandatory for all data__
            /// >
            /// > @see constants::SegyFileFormatCode
            extern const Int16Field formatCode;
            /// > The expected number of data traces per trace ensemble (e.g. the CMP fold).
            /// > __Highly recommended for all types of data__
            extern const Int16Field ensembleFold;
            /// > Trace sorting code (i.e. type of ensemble)
            /// > __Highly recommended for all types of data__
            /// >
            /// > @see constants::TraceSortingCode
            extern const Int16Field traceSortingCode;
            /// > Vertical sum code
            /// > 
            /// > 1 = no sum,
            /// > 2 = two sum, 
            /// > …,
            /// > N = M-1 sum  (M = 2 to 32,767)
            extern const Int16Field verticalSumCode;
            /// >
            /// > Sweep frequency at start (Hz)
            /// >
            extern const Int16Field sweepFrequencyStart;
            /// >
            /// > Sweep frequency at end (Hz)
            /// >
            extern const Int16Field sweepFrequencyEnd;
            /// >
            /// > Sweep length (ms)
            /// >
            extern const Int16Field sweepLength;
            /// >
            /// > Sweep type code
            /// >
            /// > @see constants::SweepTypeCode
            extern const Int16Field sweepTypeID;
            /// >
            /// > Trace number of sweep channel
            /// >
            extern const Int16Field traceNumberSweepChannel;
            /// > Sweep trace taper length in milliseconds at start if tapered 
            /// > (the taper starts at zero time and is effective for this length)
            extern const Int16Field sweepTraceTaperLengthStart;
            /// > Sweep trace taper length in milliseconds at end 
            /// > (the ending taper starts at sweep length minus the taper length at end)
            extern const Int16Field sweepTraceTaperLengthEnd;
            /// > Taper type
            /// >
            /// > @see constants::TaperType
            extern const Int16Field taperType;
            /// > Correlated data traces
            /// >
            /// > @see constants::CorrelatedDataTraces
            extern const Int16Field correlatedDataTraces;
            /// > Binary gain recovered
            /// >
            /// > @see constants::BinaryGainRecovered
            extern const Int16Field binaryGainRecovered;
            /// > Amplitude recovery method
            /// >
            /// > @see constants::AmplitudeRecoveryMethod
            extern const Int16Field amplitudeRecoveryMethod;
            /// > Measurement system. __Highly recommended for all types of data__
            /// >
            /// > If Location Data stanzas are included in the file, this entry 
            /// > must agree with the Location Data stanza. If there is a 
            /// > disagreement, the last Location Data stanza is the controlling 
            /// > authority
            /// >
            /// > @see constants::Measurement system
            extern const Int16Field measurementSystem;
            /// > Impulse signal polarity
            /// >
            /// > @see constants::ImpulseSignalPolarity
            extern const Int16Field impulseSignalPolarity;
            /// > Vibratory polarity code
            /// >
            /// > Seismic signal lags pilot signal by:
            /// > 1 = 337.5° to  22.5°
            /// > 2 =  22.5° to  67.5°
            /// > 3 =  67.5° to 112.5°
            /// > 4 = 112.5° to 157.5°
            /// > 5 = 157.5° to 202.5°
            /// > 6 = 202.5° to 247.5°
            /// > 7 = 247.5° to 292.5°
            /// > 8 = 292.5° to 337.5°
            extern const Int16Field vibratoryPolarityCode;
        }

        /**
         * @}
         */

        /**
         * @addtogroup ThConstants Trace header constants
         * 
         * @brief Constants used to identify fields in trace headers
         * 
         * @{
         */

        /**
         * @brief Trace header constants
         */
        namespace th {
            /// > Trace sequence number within line. __Highly recommended for all types of data__ 
            /// >
            /// > Numbers continue to increase if the same line continues across multiple SEG Y files            
            extern const Int32Field traceSequenceNumberWithinLine;
            /// > Trace sequence number within SEG Y file 
            /// >
            /// > Each file starts with trace sequence one
            extern const Int32Field traceSequenceNumberWithinSEGY;
            /// >
            /// > Original field record number. __Highly recommended for all types of data__
            /// >
            extern const Int32Field originalFieldRecordNumber;
            /// >
            /// > Trace number within the original field record. __Highly recommended for all types of data__
            /// >
            extern const Int32Field traceNumberWithinOriginalField;
            /// > Energy source point number 
            /// > 
            /// > Used when more than one record occurs at the same effective 
            /// > surface location. It is recommended that the new entry defined 
            /// > in Trace Header bytes 197-202 be used for shotpoint number
            extern const Int32Field energySourcePointNumber;
            /// >
            /// > Ensemble number (i.e. CDP, CMP, CRP, etc.)
            /// >
            extern const Int32Field ensembleNumber;
            /// > Trace number within the ensemble 
            /// > 
            /// > Each ensemble starts with trace number one
            extern const Int32Field traceNumberWithinEnsemble;
            /// > Distance from center of the source point to the center of the receiver group 
            /// > 
            /// > Negative if opposite to direction in which line is shot
            extern const Int32Field distanceFromCenterSourceToCenterReceiver;
            /// > Receiver group elevation (all elevations above the Vertical datum are positive and below are negative)
            /// >
            /// > The scalar in Trace Header bytes 69-70 applies to these values. 
            /// > The units are feet or meters as specified in Binary File Header 
            /// > bytes 3255-3256. 
            /// > 
            /// > The Vertical Datum should be defined through a Location Data 
            /// > stanza (see section D-1)
            extern const Int32Field receiverGroupElevation;
            /// > Surface elevation at source
            /// >
            /// > The scalar in Trace Header bytes 69-70 applies to these values. 
            /// > The units are feet or meters as specified in Binary File Header 
            /// > bytes 3255-3256. 
            /// > 
            /// > The Vertical Datum should be defined through a Location Data 
            /// > stanza (see section D-1)
            extern const Int32Field surfaceElevationAtSource;
            /// > Source depth below surface (a positive number)
            /// >
            /// > The scalar in Trace Header bytes 69-70 applies to these values. 
            /// > The units are feet or meters as specified in Binary File Header 
            /// > bytes 3255-3256. 
            /// > 
            /// > The Vertical Datum should be defined through a Location Data 
            /// > stanza (see section D-1)
            extern const Int32Field sourceDepthBelowSurface;
            /// > Datum elevation at receiver group
            /// >
            /// > The scalar in Trace Header bytes 69-70 applies to these values. 
            /// > The units are feet or meters as specified in Binary File Header 
            /// > bytes 3255-3256. 
            /// > 
            /// > The Vertical Datum should be defined through a Location Data 
            /// > stanza (see section D-1)
            extern const Int32Field datumElevationAtReceiverGroup;
            /// > Datum elevation at source
            /// >
            /// > The scalar in Trace Header bytes 69-70 applies to these values. 
            /// > The units are feet or meters as specified in Binary File Header 
            /// > bytes 3255-3256. 
            /// > 
            /// > The Vertical Datum should be defined through a Location Data 
            /// > stanza (see section D-1)
            extern const Int32Field datumElevationAtSource;
            /// > Water depth at source
            /// >
            /// > The scalar in Trace Header bytes 69-70 applies to these values. 
            /// > The units are feet or meters as specified in Binary File Header 
            /// > bytes 3255-3256. 
            /// > 
            /// > The Vertical Datum should be defined through a Location Data 
            /// > stanza (see section D-1)
            extern const Int32Field waterDepthAtSource;
            /// > Water depth at group
            /// >
            /// > The scalar in Trace Header bytes 69-70 applies to these values. 
            /// > The units are feet or meters as specified in Binary File Header 
            /// > bytes 3255-3256. 
            /// > 
            /// > The Vertical Datum should be defined through a Location Data 
            /// > stanza (see section D-1)
            extern const Int32Field waterDepthAtGroup;
            /// > Source coordinate ‑ X
            /// >
            /// > The coordinate reference system should be identified through an
            /// > extended header Location Data stanza (see section D-1).
            extern const Int32Field sourceCoordinateX;
            /// > Source coordinate ‑ Y
            /// >
            /// > The coordinate reference system should be identified through an
            /// > extended header Location Data stanza (see section D-1).
            extern const Int32Field sourceCoordinateY;
            /// > Group coordinate ‑ X
            /// >
            /// > The coordinate reference system should be identified through an
            /// > extended header Location Data stanza (see section D-1).
            extern const Int32Field groupCoordinateX;
            /// > Group coordinate ‑ Y
            /// >
            /// > The coordinate reference system should be identified through an
            /// > extended header Location Data stanza (see section D-1).
            extern const Int32Field groupCoordinateY;

            /// > Trace identification code. __Highly recommended for all types of data__
            ///> 
            /// > -1 = Other
            /// >  0 = Unknown
            /// >  1 = Seismic data
            /// >  2 = Dead
            /// >  3 = Dummy
            /// >  4 = Time break
            /// >  5 = Uphole
            /// >  6 = Sweep
            /// >  7 = Timing
            /// >  8 = Waterbreak
            /// >  9 = Near-field gun signature
            /// > 10 = Far-field gun signature
            /// > 11 = Seismic pressure sensor
            /// > 12 = Multicomponent seismic sensor - Vertical component
            /// > 13 = Multicomponent seismic sensor - Cross-line component
            /// > 14 = Multicomponent seismic sensor - In-line component
            /// > 15 = Rotated multicomponent seismic sensor - Vertical component
            /// > 16 = Rotated multicomponent seismic sensor - Transverse component
            /// > 17 = Rotated multicomponent seismic sensor - Radial component
            /// > 18 = Vibrator reaction mass
            /// > 19 = Vibrator baseplate
            /// > 20 = Vibrator estimated ground force
            /// > 21 = Vibrator reference
            /// > 22 = Time-velocity pairs
            /// > 23 … N = optional use,  (maximum N = 32,767)                 
            extern const Int16Field traceIdentificationCode;
            /// > Number of vertically summed traces yielding this trace
            /// > 
            /// > 1 is one trace, 2 is two summed traces, etc.
            extern const Int16Field numberOfVerticallySummedTraces;
            /// > Number of horizontally stacked traces yielding this trace
            /// > 
            /// > 1 is one trace, 2 is two stacked traces, etc.
            extern const Int16Field numberOfHorizontallyStackedTraces;
            /// > 
            /// > Data use
            /// > 
            extern const Int16Field dataUse;
            /// > Scalar to be applied to all elevations and depths specified in Trace Header bytes 41‑68 to give the real value.
            /// > 
            /// > Scalar = 1, +10, +100, +1000, or +10,000. If positive, scalar is
            /// > used as a multiplier; if negative, scalar is used as a divisor
            extern const Int16Field scalarElevation;
            /// > Scalar to be applied to all coordinates specified in Trace Header bytes 73‑88 and to bytes Trace Header 181-188 to give the real value. 
            /// > 
            /// > Scalar = 1, +10, +100, +1000, or +10,000.  If positive, scalar is
            /// > used as a multiplier; if negative, scalar is used as divisor
            extern const Int16Field scalarCoordinates;
            /// > Coordinate units
            /// > 
            /// > Note: To encode ±DDDMMSS bytes 89-90 equal = ±DDD*104 + MM*102 + SS 
            /// > with bytes 71-72 set to 1; To encode ±DDDMMSS.ss bytes 89-90 
            /// > equal = ±DDD*106 + MM*104 + SS*102 with bytes 71-72 set to -100
            /// > 
            /// > @see constants::CoordinateUnits
            extern const Int16Field coordinateUnits;
            /// > Weathering velocity
            /// > 
            /// > ft/s or m/s as specified in Binary File Header bytes 3255-3256
            extern const Int16Field weatheringVelocity;
            /// > Subweathering velocity
            /// > 
            /// > ft/s or m/s as specified in Binary File Header bytes 3255-3256
            extern const Int16Field subweatheringVelocity;
            /// > Uphole time at source in milliseconds
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field upholeTimeAtSource;
            /// > Uphole time at group in milliseconds
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field upholeTimeAtGroup;
            /// > Source static correction in milliseconds
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field sourceStaticCorrection;
            /// > Group static correction in milliseconds
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field groupStaticCorrection;
            /// > Total static applied in milliseconds (zero if no static has been applied)
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field totalStaticApplied;
            /// > Lag time A
            /// > 
            /// > Time in milliseconds between end of 240‑byte trace identification
            /// > header and time break. The value is positive if time break 
            /// > occurs after the end of header; negative if time break occurs 
            /// > before the end of header. Time break is defined as the initiation
            /// > pulse that may be recorded on an auxiliary trace or as otherwise
            /// > specified by the recording system
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field lagTimeA;
            /// > Lag time B
            /// > 
            /// > Time in milliseconds between time break and the initiation time 
            /// > of the energy source. May be positive or negative
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field lagTimeB;
            /// > Delay recording time 
            /// > 
            /// > Time in milliseconds between initiation time of energy source 
            /// > and the time when recording of data samples begins. In SEG Y 
            /// > rev 0 this entry was intended for deep-water work if data 
            /// > recording does not start at zero time. The entry can be negative
            /// > to accommodate negative start times (i.e. data recorded before 
            /// > time zero, presumably as a result of static application to the 
            /// > data trace). If a non-zero value (negative or positive) is 
            /// > recorded in this entry, a comment to that effect should appear 
            /// > in the Textual File Header
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field delayRecordingTime;
            /// > Mute time — Start time in milliseconds
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field muteTimeStart;
            /// > Mute time — End time in milliseconds
            /// > 
            /// > Time in milliseconds as scaled by the scalar specified in 
            /// > Trace Header bytes 215-216
            extern const Int16Field muteTimeEnd;
            /// > 
            /// > Number of samples in this trace. __Highly recommended for all types of data__
            /// > 
            extern const Int16Field nsamplesTrace;
            /// > Sample interval in microseconds (µs) for this trace. __Highly recommended for all types of data__
            /// > 
            /// > The number of bytes in a trace record must be consistent with 
            /// > the number of samples written in the trace header. This is 
            /// > important for all recording media; but it is particularly 
            /// > crucial for the correct processing of SEG Y data in disk files
            /// > 
            /// > If the fixed length trace flag in bytes 3503-3504 of the Binary 
            /// > File Header is set, the sample interval and number of samples in
            /// > every trace in the SEG Y file must be the same as the values 
            /// > recorded in the Binary File Header. If the fixed length trace 
            /// > flag is not set, the sample interval and number of samples may 
            /// > vary from trace to trace.
            extern const Int16Field sampleInterval;
            /// > Gain type of field instruments
            /// > 
            /// > 1 = fixed
            /// > 2 = binary
            /// > 3 = floating point
            /// > 4 … N = optional use
            extern const Int16Field gainType;
            /// > 
            /// > Instrument gain constant (dB)
            /// > 
            extern const Int16Field instrumentGainConstant;
            /// > 
            /// > Instrument early or initial gain (dB)
            /// > 
            extern const Int16Field instrumentEarlyGain;
            /// > Correlated
            /// > 
            /// > @see constants::CorrelatedDataTraces
            extern const Int16Field correlated;
            /// > 
            /// > Sweep frequency at start (Hz)
            /// > 
            extern const Int16Field sweepFrequencyStart;
            /// > 
            /// > Sweep frequency at end (Hz)
            /// > 
            extern const Int16Field sweepFrequencyEnd;
            /// > 
            /// > Sweep length in milliseconds
            /// > 
            extern const Int16Field sweepLength;
            /// > Sweep type
            /// > 
            /// @see constants::SweepTypeCode
            extern const Int16Field sweepType;
            /// > 
            /// > Sweep trace taper length at start in milliseconds
            /// > 
            extern const Int16Field sweepTraceTaperLengthStart;
            /// >
            /// > Sweep trace taper length at end in milliseconds
            /// >
            extern const Int16Field sweepTraceTaperLengthEnd;
            /// > Taper type
            /// >
            /// > @see constants::TaperType
            extern const Int16Field taperType;
            /// >
            /// > Alias filter frequency (Hz), if used
            /// >
            extern const Int16Field aliasFilterFrequency;
            /// >
            /// > Alias filter slope (dB/octave)
            /// >
            extern const Int16Field aliasFilterSlope;
            /// >
            /// > Notch filter frequency (Hz), if used
            /// >
            extern const Int16Field notchFilterFrequency;
            /// >
            /// > Notch filter slope (dB/octave)
            /// >
            extern const Int16Field notchFilterSlope;
            /// >
            /// > Low-cut frequency (Hz), if used
            /// >
            extern const Int16Field lowCutFrequency;
            /// >
            /// > High-cut frequency (Hz), if used
            /// >
            extern const Int16Field highCutFrequency;
            /// >
            /// > Low-cut slope (dB/octave)
            /// >
            extern const Int16Field lowCutSlope;
            /// >
            /// > High-cut slope (dB/octave)
            /// >
            extern const Int16Field highCutSlope;
            /// > Year data recorded 
            /// >
            /// > The 1975 standard is unclear as to whether this should be 
            /// > recorded as a 2-digit or a 4-digit year and both have been used.
            /// > For SEG Y revisions beyond rev 0, the year should be recorded 
            /// > as the complete 4-digit Gregorian calendar year (i.e. the year 
            /// > 2001 should be recorded as 2001 (0x7D1))
            extern const Int16Field yearDataRecorded;
            /// > Day of year 
            /// >
            /// > Julian day for GMT and UTC time basis
            extern const Int16Field dayOfTheYear;
            /// >
            /// > Hour of day (24 hour clock)
            /// >
            extern const Int16Field hourOfDay;
            /// >
            /// > Minute of hour
            /// >
            extern const Int16Field minuteOfHour;
            /// >
            /// > Second of minute
            /// >
            extern const Int16Field secondOfMinute;
            /// >
            /// > Time basis code
            /// >
            extern const Int16Field timeBasisCode;
            /// > Trace weighting factor 
            /// >
            /// > Defined as 2‑N volts for the least significant bit.
            /// > (N = 0, 1, …, 32767)
            extern const Int16Field traceWeightingFactor;
            /// >
            /// > Geophone group number of roll switch position one
            /// >
            extern const Int16Field geophoneGroupNumberOfRollSwitch;
            /// >
            /// > Geophone group number of trace number one within original field record
            /// >
            extern const Int16Field geophoneGroupNumberOfTraceNumber;
            /// >
            /// > Geophone group number of last trace within original field record
            /// >
            extern const Int16Field geophoneGroupNumberOfLastTrace;
            /// >
            /// > Gap size (total number of groups dropped)
            /// >
            extern const Int16Field gapSize;
            /// >
            /// > Over travel associated with taper at beginning or end of line
            /// >
            extern const Int16Field overTravel;
        }
        
        /**
         * @}
         */
    }
}

#endif	/* SEGYFILE_FIELDS_REV0_H */

