#ifndef SEGYFILE_FIELDS_REV0_H
#define	SEGYFILE_FIELDS_REV0_H

#include<impl/metafunctions-inl.h>

// Forced by the use of C++03
#include<stdint.h>

namespace seismic {

    /**
     * @brief Template tag to intantiate a Rev0 conforming class
     */
    class Rev0 {};
    
    namespace rev0 {
        namespace bfh {

            /**
             * @brief Fields that are mapped to 32-bit integers
             */
            enum Int32FieldsRev0 {
                /// Job identification number
                jobID = 0,
                /// Line number. For 3-D poststack data, this will typically contain the in-line number
                lineNumber = 4,
                /// Reel number
                reelNumber = 8
            };

            /**
             * @brief Fields that are mapped to 16-bit integers
             */
            enum Int16FieldsRev0 {
                /// Number of data traces per ensemble. __Mandatory for prestack data__
                nDataTraces = 12,
                /// Number of auxiliary traces per ensemble. __Mandatory for prestack data__
                nAuxiliaryTraces = 14,
                /// Sample interval in microseconds (µs). __Mandatory for all data types__
                sampleInterval = 16,
                /// Sample interval in microseconds (µs) of original field recording
                sampleIntervalOriginalField = 18,
                /// Number of samples per data trace. __Mandatory for all types of data__ 
                ///
                /// The sample interval and number of samples in the Binary 
                /// File Header should be for the primary set of seismic data traces in the file
                nsamplesDataTrace = 20,
                /// Number of samples per data trace for original field recording
                nsamplesDataTraceOriginalField = 22,
                /// Data sample format code.  __Mandatory for all data__
                ///
                /// @see constants::SegyFileFormatCode
                formatCode = 24,
                /// The expected number of data traces per trace ensemble (e.g. the CMP fold).
                /// __Highly recommended for all types of data__
                ensembleFold = 26,
                /// Trace sorting code (i.e. type of ensemble)
                /// __Highly recommended for all types of data__
                ///
                /// @see constants::TraceSortingCode
                traceSortingCode = 28,
                /// Vertical sum code
                ///
                ///1 = no sum,
                ///2 = two sum, 
                ///…,
                ///N = M-1 sum  (M = 2 to 32,767)
                verticalSumCode = 30,
                /// Sweep frequency at start (Hz)
                sweepFrequencyStart = 32,
                /// Sweep frequency at end (Hz)
                sweepFrequencyEnd = 34,
                /// Sweep length (ms)
                sweepLength = 36,
                /// Sweep type code
                ///
                /// @see constants::SweepTypeCode
                sweepTypeID = 38,
                /// Trace number of sweep channel
                traceNumberSweepChannel = 40,
                /// Sweep trace taper length in milliseconds at start if tapered 
                /// (the taper starts at zero time and is effective for this length)
                sweepTraceTaperLengthStart = 42,
                /// Sweep trace taper length in milliseconds at end 
                /// (the ending taper starts at sweep length minus the taper length at end)
                sweepTraceTaperLengthEnd = 44,
                /// Taper type
                ///
                /// @see constants::TaperType
                taperType = 46,
                /// Correlated data traces
                ///
                /// @see constants::CorrelatedDataTraces
                correlatedDataTraces = 48,
                /// Binary gain recovered
                ///
                /// @see constants::BinaryGainRecovered
                binaryGainRecovered = 50,
                /// Amplitude recovery method
                ///
                /// @see constants::AmplitudeRecoveryMethod
                amplitudeRecoveryMethod = 52,
                /// Measurement system. __Highly recommended for all types of data__
                ///
                /// If Location Data stanzas are included in the file, this entry 
                /// must agree with the Location Data stanza. If there is a 
                /// disagreement, the last Location Data stanza is the controlling 
                /// authority
                ///
                /// @see constants::Measurement system
                measurementSystem = 54,
                /// Impulse signal polarity
                ///
                /// @see constants::ImpulseSignalPolarity
                impulseSignalPolarity = 56,
                /// Vibratory polarity code
                ///
                /// Seismic signal lags pilot signal by:
                /// 1 = 337.5° to  22.5°
                /// 2 =  22.5° to  67.5°
                /// 3 =  67.5° to 112.5°
                /// 4 = 112.5° to 157.5°
                /// 5 = 157.5° to 202.5°
                /// 6 = 202.5° to 247.5°
                /// 7 = 247.5° to 292.5°
                /// 8 = 292.5° to 337.5°
                vibratoryPolarityCode = 58
            };
        }
    }

    SET_SUBSCRIPT_RETURN_TYPE(rev0::bfh::Int32FieldsRev0, int32_t);
    SET_SUBSCRIPT_RETURN_TYPE(rev0::bfh::Int16FieldsRev0, int16_t);

}

#endif	/* SEGYFILE_FIELDS_REV0_H */

