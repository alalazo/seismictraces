#ifndef SEGYFILE_CONSTANTS_H
#define	SEGYFILE_CONSTANTS_H

namespace seismic {
    
    struct SegyFileFormatCode {
        enum {
            IBMfloat32 = 1,
            Int32 = 2,
            Int16 = 3,
            IEEEfloat32 = 5,
            Int8 = 8
        };
    } ;
    
    struct TraceSortingCode {
        enum {
            other = -1,
            unknown = 0,
            asRecorder = 1,
            CDPEnsemble = 2,
            singleFoldContinuousProfile = 3,
            horizontallyStacked = 4,
            commonSourcePoint = 5,
            commonReceiverPoint = 6,
            commonOffsetPoint = 7,
            commonMidPoint = 8,
            commonConversionPoint = 9
        };
    };
    
    struct SweepTypeCode {
        enum {
            linear = 1,
            parabolic = 2,
            exponential = 3,
            other = 4
        };
    };
    
    struct TaperType {
        enum {
            linear = 1,
            cos = 2,
            other = 3
        };
    };
    
    struct CorrelatedDataTraces {
        enum { no = 1, yes = 2 };
    };
    
    struct BinaryGainRecovered {
        enum { yes = 1, no = 2 };
    };
    
    struct AmplitudeRecoveryMethod {
        enum {
            none = 1,
            sphericalDivergence = 2,
            AGC = 3,
            other = 4
        };
    };
    
    struct MeasurementSystem {
        enum { meters = 1, feet = 2 };
    };
    
    struct ImpulseSignalPolarity {
        enum { negativeNumbers = 1, positiveNumbers = 2 };
    };
}

#endif	/* SEGYFILE_CONSTANTS_H */

