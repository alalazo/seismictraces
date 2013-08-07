/**
 * @file SegyFile-constants.h
 * @brief Contains all the enums and constants needed to describe a SEGY file
 */
#ifndef SEGYFILE_CONSTANTS_H
#define	SEGYFILE_CONSTANTS_H

namespace seismic {
    
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
    } ;
    
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
}

#endif	/* SEGYFILE_CONSTANTS_H */

