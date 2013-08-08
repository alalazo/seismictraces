/** 
 * @file SegyFile-TraceHeader.h
 * @brief Trace header of a SEGY file 
 */
#ifndef SEGYFILE_TRACEHEADER_H
#define	SEGYFILE_TRACEHEADER_H

#include<iostream>

// Forced by the use of C++03
#include<stdint.h>

namespace seismic {

    /**
     * @brief Models the Trace header of a SEGY file
     * 
     * According to SEGY rev 1 standard (May 2002):
     * 
     * > The SEG Y trace header contains trace attributes, which are defined as 
     * > two-byte or four-byte, two's complement integers. The values in bytes 
     * > 1-180 were defined in the 1975 standard and these entries remain 
     * > unchanged, although clarification and extensions may be supplied where 
     * > appropriate. Bytes 181-240 were for optional information in the 1975 
     * > standard and this has been the main area of conflict between different 
     * > flavors of SEG Y. This revision defines standard locations in bytes 
     * > 181-240 for certain values that are needed in modern data processing. 
     * > In particular, standard locations for a shotpoint number and ensemble 
     * > coordinates are defined. Bytes 203 to 210 allow the measurement units 
     * > for the Data Trace samples to be defined and transduction constants to 
     * > be defined. These entries allow the Data Trace values to be converted 
     * > to engineering units.
     * >
     * > The values included in the Trace Header are limited and intended to 
     * > provide information that may change on a trace-by-trace basis and the 
     * > basic information needed to process and identify the trace. The trace 
     * > headers are not intended to be a repository for significant amounts of 
     * > ancillary data. If significant amounts of ancillary data need to be 
     * > exchanged, it is recommended that SEG Ancillary Data Standard data 
     * > set(s) be used.
     * 
     * 
     */
    class TraceHeader {
    public:
        static const int buffer_size = 240;

        /**
         * @brief Fields that are mapped to 32-bit integers
         */
        enum Int32Fields {
            /// Trace sequence number within line. __Highly recommended for all types of data__ 
            ///
            /// Numbers continue to increase if the same line continues across multiple SEG Y files
            traceSequenceNumberWithinLine = 0,
            /// Trace sequence number within SEG Y file 
            /// 
            /// Each file starts with trace sequence one
            traceSequenceNumberWithinSEGY = 4,
            /// Original field record number. __Highly recommended for all types of data__
            originalFieldRecordNumber = 8,
            /// Trace number within the original field record. __Highly recommended for all types of data__
            traceNumberWithinOriginalField = 12,
            /// Energy source point number 
            ///
            /// Used when more than one record occurs at the same effective 
            /// surface location. It is recommended that the new entry defined 
            /// in Trace Header bytes 197-202 be used for shotpoint number
            energySourcePointNumber = 16,
            /// Ensemble number (i.e. CDP, CMP, CRP, etc.)
            ensembleNumber = 20,
            /// Trace number within the ensemble 
            ///
            /// Each ensemble starts with trace number one
            traceNumberWithinEnsemble = 24,
            /// Distance from center of the source point to the center of the receiver group 
            /// 
            /// Negative if opposite to direction in which line is shot
            distanceFromCenterSourceToCenterReceiver = 36,
            /// Receiver group elevation (all elevations above the Vertical datum are positive and below are negative)
            ///
            /// The scalar in Trace Header bytes 69-70 applies to these values. 
            /// The units are feet or meters as specified in Binary File Header 
            /// bytes 3255-3256. 
            /// 
            /// The Vertical Datum should be defined through a Location Data 
            /// stanza (see section D-1)
            receiverGroupElevation = 40,
            /// Surface elevation at source
            ///
            /// The scalar in Trace Header bytes 69-70 applies to these values. 
            /// The units are feet or meters as specified in Binary File Header 
            /// bytes 3255-3256. 
            /// 
            /// The Vertical Datum should be defined through a Location Data 
            /// stanza (see section D-1)
            surfaceElevationAtSource = 44,
            /// Source depth below surface (a positive number)
            ///
            /// The scalar in Trace Header bytes 69-70 applies to these values. 
            /// The units are feet or meters as specified in Binary File Header 
            /// bytes 3255-3256. 
            /// 
            /// The Vertical Datum should be defined through a Location Data 
            /// stanza (see section D-1)
            sourceDepthBelowSurface = 48,
            /// Datum elevation at receiver group
            ///
            /// The scalar in Trace Header bytes 69-70 applies to these values. 
            /// The units are feet or meters as specified in Binary File Header 
            /// bytes 3255-3256. 
            /// 
            /// The Vertical Datum should be defined through a Location Data 
            /// stanza (see section D-1)
            datumElevationAtReceiverGroup = 52,
            /// Datum elevation at source
            ///
            /// The scalar in Trace Header bytes 69-70 applies to these values. 
            /// The units are feet or meters as specified in Binary File Header 
            /// bytes 3255-3256. 
            /// 
            /// The Vertical Datum should be defined through a Location Data 
            /// stanza (see section D-1)
            datumElevationAtSource = 56,
            /// Water depth at source
            ///
            /// The scalar in Trace Header bytes 69-70 applies to these values. 
            /// The units are feet or meters as specified in Binary File Header 
            /// bytes 3255-3256. 
            /// 
            /// The Vertical Datum should be defined through a Location Data 
            /// stanza (see section D-1)
            waterDepthAtSource = 60,
            /// Water depth at group
            ///
            /// The scalar in Trace Header bytes 69-70 applies to these values. 
            /// The units are feet or meters as specified in Binary File Header 
            /// bytes 3255-3256. 
            /// 
            /// The Vertical Datum should be defined through a Location Data 
            /// stanza (see section D-1)
            waterDepthAtGroup = 64,
            /// Source coordinate ‑ X
            ///
            /// The coordinate reference system should be identified through an
            /// extended header Location Data stanza (see section D-1).
            sourceCoordinateX = 72,
            /// Source coordinate ‑ Y
            ///
            /// The coordinate reference system should be identified through an
            /// extended header Location Data stanza (see section D-1).
            sourceCoordinateY = 76,
            /// Group coordinate ‑ X
            ///
            /// The coordinate reference system should be identified through an
            /// extended header Location Data stanza (see section D-1).
            groupCoordinateX = 80,
            /// Group coordinate ‑ Y
            ///
            /// The coordinate reference system should be identified through an
            /// extended header Location Data stanza (see section D-1).
            groupCoordinateY = 84,
            /// X coordinate of ensemble (CDP) position of this trace (scalar in Trace Header bytes 71-72 applies)
            ///
            /// The coordinate reference system should be identified through an 
            /// extended header Location Data stanza (see section D-1)
            ensembleCoordinateX = 180,
            /// Y coordinate of ensemble (CDP) position of this trace (scalar in bytes Trace Header 71-72 applies)
            ///
            /// The coordinate reference system should be identified through an
            /// extended header Location Data stanza (see section D-1)
            ensembleCoordinateY = 184,
            /// For 3-D poststack data, this field should be used for the in-line number
            ///
            /// If one in-line per SEG Y file is being recorded, this value 
            /// should be the same for all traces in the file and the same value
            /// will be recorded in bytes 3205-3208 of the Binary File Header
            inlineNumber = 188,
            /// For 3-D poststack data, this field should be used for the cross-line number
            ///
            /// This will typically be the same value as the ensemble (CDP) 
            /// number in Trace Header bytes 21-24, but this does not have to 
            /// be the case
            crosslineNumber = 192,
            /// Shotpoint number 
            ///
            /// This is probably only applicable to 2-D poststack data. 
            /// Note that it is assumed that the shotpoint number refers to the 
            /// source location nearest to the ensemble (CDP) location for a 
            /// particular trace. If this is not the case, there should be a 
            /// comment in the Textual File Header explaining what the 
            /// shotpoint number actually refers to
            shotpointNumber = 196,
            /// Transduction Constant 
            ///
            /// The multiplicative constant used to convert the Data Trace 
            /// samples to the Transduction Units (specified in Trace Header 
            /// bytes 211-212). The constant is encoded as a four-byte, two's 
            /// complement integer (bytes 205-208) which is the mantissa and a 
            /// two-byte, two's complement integer (bytes 209-210) which is the 
            /// power of ten exponent (i.e. Bytes 205-208 * 10**Bytes 209-210)
            transductionConstantMantissa = 204,
            /// Source Measurement 
            /// 
            /// Describes the source effort used to generate the trace. The 
            /// measurement can be simple, qualitative measurements such as the
            /// total weight of explosive used or the peak air gun pressure or 
            /// the number of vibrators times the sweep duration. Although these
            /// simple measurements are acceptable, it is preferable to use true
            /// measurement units of energy or work.
            ///
            /// The constant is encoded as a four-byte, two's complement integer
            /// (bytes 225-228) which is the mantissa and a two-byte, two's 
            /// complement integer (bytes 209-230) which is the power of ten 
            /// exponent (i.e. Bytes 225-228 * 10**Bytes 229-230)
            sourceMeasurementMantissa = 224,
        };

        /**
         * @brief Fields that are mapped to 16-bit integers
         */
        enum Int16Fields {
            /// Trace identification code. __Highly recommended for all types of data__
            ///
            /// -1 = Other
            ///  0 = Unknown
            ///  1 = Seismic data
            ///  2 = Dead
            ///  3 = Dummy
            ///  4 = Time break
            ///  5 = Uphole
            ///  6 = Sweep
            ///  7 = Timing
            ///  8 = Waterbreak
            ///  9 = Near-field gun signature
            /// 10 = Far-field gun signature
            /// 11 = Seismic pressure sensor
            /// 12 = Multicomponent seismic sensor - Vertical component
            /// 13 = Multicomponent seismic sensor - Cross-line component
            /// 14 = Multicomponent seismic sensor - In-line component
            /// 15 = Rotated multicomponent seismic sensor - Vertical component
            /// 16 = Rotated multicomponent seismic sensor - Transverse component
            /// 17 = Rotated multicomponent seismic sensor - Radial component
            /// 18 = Vibrator reaction mass
            /// 19 = Vibrator baseplate
            /// 20 = Vibrator estimated ground force
            /// 21 = Vibrator reference
            /// 22 = Time-velocity pairs
            /// 23 … N = optional use,  (maximum N = 32,767)                 
            traceIdentificationCode = 28,
            /// Number of vertically summed traces yielding this trace
            ///
            /// 1 is one trace, 2 is two summed traces, etc.
            numberOfVerticallySummedTraces = 30,
            /// Number of horizontally stacked traces yielding this trace
            ///
            /// 1 is one trace, 2 is two stacked traces, etc.
            numberOfHorizontallyStackedTraces = 32,
            /// Data use
            dataUse = 34,
            /// Scalar to be applied to all elevations and depths specified in Trace Header bytes 41‑68 to give the real value.
            ///
            /// Scalar = 1, +10, +100, +1000, or +10,000. If positive, scalar is
            /// used as a multiplier; if negative, scalar is used as a divisor
            scalarElevation = 68,
            /// Scalar to be applied to all coordinates specified in Trace Header bytes 73‑88 and to bytes Trace Header 181-188 to give the real value. 
            ///
            /// Scalar = 1, +10, +100, +1000, or +10,000.  If positive, scalar is
            /// used as a multiplier; if negative, scalar is used as divisor
            scalarCoordinates = 70,
            /// Coordinate units
            ///
            /// Note: To encode ±DDDMMSS bytes 89-90 equal = ±DDD*104 + MM*102 + SS 
            /// with bytes 71-72 set to 1; To encode ±DDDMMSS.ss bytes 89-90 
            /// equal = ±DDD*106 + MM*104 + SS*102 with bytes 71-72 set to -100
            ///
            /// @see constants::CoordinateUnits
            coordinateUnits = 88,
            /// Weathering velocity
            ///
            /// ft/s or m/s as specified in Binary File Header bytes 3255-3256
            weatheringVelocity = 90,
            /// Subweathering velocity
            ///
            /// ft/s or m/s as specified in Binary File Header bytes 3255-3256
            subweatheringVelocity = 92,
            /// Uphole time at source in milliseconds
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            upholeTimeAtSource = 94,
            /// Uphole time at group in milliseconds
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            upholeTimeAtGroup = 96,
            /// Source static correction in milliseconds
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            sourceStaticCorrection = 98,
            /// Group static correction in milliseconds
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            groupStaticCorrection = 100,
            /// Total static applied in milliseconds (zero if no static has been applied)
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            totalStaticApplied = 102,
            /// Lag time A
            ///
            /// Time in milliseconds between end of 240‑byte trace identification
            /// header and time break. The value is positive if time break 
            /// occurs after the end of header; negative if time break occurs 
            /// before the end of header. Time break is defined as the initiation
            /// pulse that may be recorded on an auxiliary trace or as otherwise
            /// specified by the recording system
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            lagTimeA = 104,
            /// Lag time B
            ///
            /// Time in milliseconds between time break and the initiation time 
            /// of the energy source. May be positive or negative
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            lagTimeB = 106,
            /// Delay recording time 
            ///
            /// Time in milliseconds between initiation time of energy source 
            /// and the time when recording of data samples begins. In SEG Y 
            /// rev 0 this entry was intended for deep-water work if data 
            /// recording does not start at zero time. The entry can be negative
            /// to accommodate negative start times (i.e. data recorded before 
            /// time zero, presumably as a result of static application to the 
            /// data trace). If a non-zero value (negative or positive) is 
            /// recorded in this entry, a comment to that effect should appear 
            /// in the Textual File Header
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            delayRecordingTime = 108,
            /// Mute time — Start time in milliseconds
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            muteTimeStart = 110,
            /// Mute time — End time in milliseconds
            ///
            /// Time in milliseconds as scaled by the scalar specified in 
            /// Trace Header bytes 215-216
            muteTimeEnd = 112,
            /// Number of samples in this trace. __Highly recommended for all types of data__
            nsamplesTrace = 114,
            /// Sample interval in microseconds (µs) for this trace. __Highly recommended for all types of data__
            /// 
            /// The number of bytes in a trace record must be consistent with 
            /// the number of samples written in the trace header. This is 
            /// important for all recording media; but it is particularly 
            /// crucial for the correct processing of SEG Y data in disk files
            ///
            /// If the fixed length trace flag in bytes 3503-3504 of the Binary 
            /// File Header is set, the sample interval and number of samples in
            /// every trace in the SEG Y file must be the same as the values 
            /// recorded in the Binary File Header. If the fixed length trace 
            /// flag is not set, the sample interval and number of samples may 
            /// vary from trace to trace.
            sampleInterval = 116,
            /// Gain type of field instruments
            ///
            /// 1 = fixed
            /// 2 = binary
            /// 3 = floating point
            /// 4 … N = optional use
            gainType = 118,
            /// Instrument gain constant (dB)
            instrumentGainConstant = 120,
            /// Instrument early or initial gain (dB)
            instrumentEarlyGain = 122,
            /// Correlated
            ///
            /// @see constants::CorrelatedDataTraces
            correlated = 124,
            /// Sweep frequency at start (Hz)
            sweepFrequencyStart = 126,
            /// Sweep frequency at end (Hz)
            sweepFrequencyEnd = 128,
            /// Sweep length in milliseconds
            sweepLength = 130,
            /// Sweep type
            ///
            /// @see constants::SweepTypeCode
            sweepType = 132,
            /// Sweep trace taper length at start in milliseconds
            sweepTraceTaperLengthStart = 134,
            /// Sweep trace taper length at end in milliseconds
            sweepTraceTaperLengthEnd = 136,
            /// Taper type
            ///
            /// @see constants::TaperType
            taperType = 138,
            /// Alias filter frequency (Hz), if used
            aliasFilterFrequency = 140,
            /// Alias filter slope (dB/octave)
            aliasFilterSlope = 142,
            /// Notch filter frequency (Hz), if used
            notchFilterFrequency = 144,
            /// Notch filter slope (dB/octave)
            notchFilterSlope = 146,
            /// Low-cut frequency (Hz), if used
            lowCutFrequency = 148,
            /// High-cut frequency (Hz), if used
            highCutFrequency = 150,
            /// Low-cut slope (dB/octave)
            lowCutSlope = 152,
            /// High-cut slope (dB/octave)
            highCutSlope = 154,
            /// Year data recorded 
            ///
            /// The 1975 standard is unclear as to whether this should be 
            /// recorded as a 2-digit or a 4-digit year and both have been used.
            /// For SEG Y revisions beyond rev 0, the year should be recorded 
            /// as the complete 4-digit Gregorian calendar year (i.e. the year 
            /// 2001 should be recorded as 2001 (0x7D1))
            yearDataRecorded = 156,
            /// Day of year 
            ///
            /// Julian day for GMT and UTC time basis
            dayOfTheYear = 158,
            /// Hour of day (24 hour clock)
            hourOfDay = 160,
            /// Minute of hour
            minuteOfHour = 162,
            /// Second of minute
            secondOfMinute = 164,
            /// Time basis code
            timeBasisCode = 166,
            /// Trace weighting factor 
            ///
            /// Defined as 2‑N volts for the least significant bit.
            /// (N = 0, 1, …, 32767)
            traceWeightingFactor = 168,
            /// Geophone group number of roll switch position one
            geophoneGroupNumberOfRollSwitch = 170,
            /// Geophone group number of trace number one within original field record
            geophoneGroupNumberOfTraceNumber = 172,
            /// Geophone group number of last trace within original field record
            geophoneGroupNumberOfLastTrace = 174,
            /// Gap size (total number of groups dropped)
            gapSize = 176,
            /// Over travel associated with taper at beginning or end of line
            overTravel = 178,
            /// Scalar to be applied to the shotpoint number in Trace Header bytes 197-200 to give the real value
            ///
            /// If positive, scalar is used as a multiplier; if negative as a 
            /// divisor; if zero the shotpoint number is not scaled (i.e. it is 
            /// an integer. A typical value will be -10, allowing shotpoint 
            /// numbers with one decimal digit to the right of the decimal
            /// point)
            scalarShotpointNumber = 200,
            /// Trace value measurement unit
            ///
            /// @see constants::MeasurementUnit
            traceValueMeasurementUnit = 202,
            /// Transduction Constant 
            ///
            /// The multiplicative constant used to convert the Data Trace 
            /// samples to the Transduction Units (specified in Trace Header 
            /// bytes 211-212). The constant is encoded as a four-byte, two's 
            /// complement integer (bytes 205-208) which is the mantissa and a 
            /// two-byte, two's complement integer (bytes 209-210) which is the 
            /// power of ten exponent (i.e. Bytes 205-208 * 10**Bytes 209-210)
            transductionConstantExponent = 208,
            /// Transduction Units 
            ///
            /// The unit of measurement of the Data Trace samples after they 
            /// have been multiplied by the Transduction Constant specified in 
            /// Trace Header bytes 205-210
            ///
            /// @see constants::MeasurementUnit
            transductionUnits = 210,
            /// Device/Trace Identifier 
            ///
            /// The unit number or id number of the device associated with the 
            /// Data Trace (i.e. 4368 for vibrator serial number 4368 or 20316 
            /// for gun 16 on string 3 on vessel 2). This field allows traces 
            /// to be associated across trace ensembles independently of the 
            /// trace number (Trace Header bytes 25-28)
            traceIdentifier = 212,
            /// Scalar to be applied to times specified in Trace Header bytes 95-114 to give the true time value in milliseconds
            ///
            /// Scalar = 1, +10, +100, +1000, or +10,000.  If positive, scalar 
            /// is used as a multiplier; if negative, scalar is used as divisor.
            /// A value of zero is assumed to be a scalar value of 1
            scalarTime = 214,
            /// Source Type/Orientation
            ///
            /// Defines the type and the orientation of the energy source. The
            /// terms vertical, cross-line and in-line refer to the three axes 
            /// of an orthogonal coordinate system. The absolute azimuthal 
            /// orientation of the coordinate system axes can be defined in the 
            /// Bin Grid Definition Stanza (page 28).
            ///
            /// -1 to -n = Other
            ///        0 = Unknown
            ///        1 = Vibratory - Vertical orientation
            ///        2 = Vibratory - Cross-line orientation
            ///        3 = Vibratory - In-line orientation
            ///        4 = Impulsive - Vertical orientation
            ///        5 = Impulsive - Cross-line orientation
            ///        6 = Impulsive - In-line orientation
            ///        7 = Distributed Impulsive - Vertical orientation
            ///        8 = Distributed Impulsive - Cross-line orientation
            ///        9 = Distributed Impulsive - In-line orientation
            sourceOrientation = 216,
            /// Source Measurement 
            /// 
            /// Describes the source effort used to generate the trace. The 
            /// measurement can be simple, qualitative measurements such as the
            /// total weight of explosive used or the peak air gun pressure or 
            /// the number of vibrators times the sweep duration. Although these
            /// simple measurements are acceptable, it is preferable to use true
            /// measurement units of energy or work.
            ///
            /// The constant is encoded as a four-byte, two's complement integer
            /// (bytes 225-228) which is the mantissa and a two-byte, two's 
            /// complement integer (bytes 209-230) which is the power of ten 
            /// exponent (i.e. Bytes 225-228 * 10**Bytes 229-230)
            sourceMeasurementExponent = 228,
            /// Source Measurement Unit 
            ///
            /// The unit used for the Source Measurement, Trace header bytes 225-230.
            /// -1 = Other (should be described in Source Measurement Unit stanza, page 40)
            ///  0 = Unknown
            ///  1 = Joule (J)
            ///  2 = Kilowatt (kW)
            ///  3 = Pascal (Pa)
            ///  4 = Bar (Bar)
            ///  4 = Bar-meter (Bar-m)
            ///  5 = Newton (N)
            ///  6 = Kilograms (kg)
            sourceMEasurementUnit = 230
        };

        /**
         * @brief Returns the corresponding integer value
         * 
         * @param[in] id constants associated with the requested field
         * @return requested field 
         */
        const int32_t& operator[](const Int32Fields id) const {
            // Pointer needed to induce aliasing
            const char * pnt(&buffer_[id]);
            return *(reinterpret_cast<const int32_t *> (pnt));
        }

        /**
         * @brief Returns the corresponding integer value
         * 
         * @param[in] id constants associated with the requested field
         * @return requested field 
         */
        const int16_t& operator[](const Int16Fields id) const {
            // Pointer needed to induce aliasing
            const char * pnt(&buffer_[id]);
            return *(reinterpret_cast<const int16_t *> (pnt));
        }

        /**
         * @brief Returns the corresponding integer value
         * 
         * @param[in] id constants associated with the requested field
         * @return requested field 
         */
        int32_t& operator[](const Int32Fields id) {
            return const_cast<int32_t&> (static_cast<const TraceHeader&> (*this)[id]);
        }

        /**
         * @brief Returns the corresponding integer value
         * 
         * @param[in] id constants associated with the requested field
         * @return requested field 
         */
        int16_t& operator[](const Int16Fields id) {
            return const_cast<int16_t&> (static_cast<const TraceHeader&> (*this)[id]);
        }

        /**
         * @brief Returns a raw pointer to the underlying buffer
         * 
         * @return Pointer to the beginning of the buffer
         */
        const char * get() const {
            return &buffer_[0];
        }

        /**
         * @brief Returns a raw pointer to the underlying buffer
         * 
         * @return Pointer to the beginning of the buffer
         */
        char * get() {
            return const_cast<char *> (static_cast<const TraceHeader&> (*this).get());
        }

    private:
        char buffer_[buffer_size];
    };

    /**
     * @brief Output stream operator for TraceHeader
     * 
     * @param cout stream
     * @param th input trace header 
     * @return cout
     * 
     * @see TraceHeader
     */
    std::ostream& operator<<(std::ostream& cout, const TraceHeader& th);

}

#endif	/* SEGYFILE_TRACEHEADER_H */

