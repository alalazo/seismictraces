/**
 * @file SegyFile-BinaryFileHeader.h
 * @brief Binary file header of a SEGY file
 */
#ifndef SEGYFILE_BINARYFILEHEADER_H
#define	SEGYFILE_BINARYFILEHEADER_H

#include<iostream>
#include<vector>

// Forced by the use of C++03
#include<stdint.h>

namespace seismic {
    
    /**
     * @brief Models the Binary file header of a SEGY file
     * 
     * According to SEGY rev 1 standard (May 2002):
     * 
     * > The 400-byte Binary File Header record contains binary values that 
     * > affect the whole SEG Y file.  The values in the Binary File Header 
     * > are defined as two-byte or four-byte, two's complement integers.  
     * > Certain values in this header are crucial for the processing of the 
     * > data in the file, particularly the sampling interval, trace length and
     * > format code.  This revision defines a few additional fields in the 
     * > optional portion, as well as providing some clarification on the use 
     * > of some existing entries.
     * 
     * The following is a small example of the basic use of the class:
     * @include example03.cpp
     */
    class BinaryFileHeader {
    public:
        /// Number of bytes in the Binary file header
        static const int buffer_size = 400;
        
        /**
         * @brief Fields that are mapped to 32-bit integers
         */
        enum Int32Fields {
            /// Job identification number
            jobID      = 0,
            /// Line number. For 3-D poststack data, this will typically contain the in-line number
            lineNumber = 4,
            /// Reel number
            reelNumber = 8
        };

        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int32Fields
         */
        static const std::vector<Int32Fields> Int32List;
        
        /**
         * @brief Fields that are mapped to 16-bit integers
         */
        enum Int16Fields {
            /// Number of data traces per ensemble. __Mandatory for prestack data__
            nDataTraces                    = 12,
            /// Number of auxiliary traces per ensemble. __Mandatory for prestack data__
            nAuxiliaryTraces               = 14,
            /// Sample interval in microseconds (µs). __Mandatory for all data types__
            sampleInterval                 = 16,
            /// Sample interval in microseconds (µs) of original field recording
            sampleIntervalOriginalField    = 18,
            /// Number of samples per data trace. __Mandatory for all types of data__ 
            ///
            /// The sample interval and number of samples in the Binary 
            /// File Header should be for the primary set of seismic data traces in the file
            nsamplesDataTrace              = 20,
            /// Number of samples per data trace for original field recording
            nsamplesDataTraceOriginalField = 22,
            /// Data sample format code.  __Mandatory for all data__
            ///
            /// @see constants::SegyFileFormatCode
            formatCode                     = 24,
            /// The expected number of data traces per trace ensemble (e.g. the CMP fold).
            /// __Highly recommended for all types of data__
            ensembleFold                   = 26,
            /// Trace sorting code (i.e. type of ensemble)
            /// __Highly recommended for all types of data__
            ///
            /// @see constants::TraceSortingCode
            traceSortingCode               = 28,
            /// Vertical sum code
            ///
            ///1 = no sum,
            ///2 = two sum, 
            ///…,
            ///N = M-1 sum  (M = 2 to 32,767)
            verticalSumCode = 30,
            /// Sweep frequency at start (Hz)
            sweepFrequencyStart            = 32,
            /// Sweep frequency at end (Hz)
            sweepFrequencyEnd              = 34,
            /// Sweep length (ms)
            sweepLength                    = 36,
            /// Sweep type code
            ///
            /// @see constants::SweepTypeCode
            sweepTypeID                    = 38,
            /// Trace number of sweep channel
            traceNumberSweepChannel        = 40,
            /// Sweep trace taper length in milliseconds at start if tapered 
            /// (the taper starts at zero time and is effective for this length)
            sweepTraceTaperLengthStart     = 42,
            /// Sweep trace taper length in milliseconds at end 
            /// (the ending taper starts at sweep length minus the taper length at end)
            sweepTraceTaperLengthEnd       = 44,
            /// Taper type
            ///
            /// @see constants::TaperType
            taperType                      = 46,
            /// Correlated data traces
            ///
            /// @see constants::CorrelatedDataTraces
            correlatedDataTraces           = 48,
            /// Binary gain recovered
            ///
            /// @see constants::BinaryGainRecovered
            binaryGainRecovered            = 50,            
            /// Amplitude recovery method
            ///
            /// @see constants::AmplitudeRecoveryMethod
            amplitudeRecoveryMethod        = 52,
            /// Measurement system. __Highly recommended for all types of data__
            ///
            /// If Location Data stanzas are included in the file, this entry 
            /// must agree with the Location Data stanza. If there is a 
            /// disagreement, the last Location Data stanza is the controlling 
            /// authority
            ///
            /// @see constants::Measurement system
            measurementSystem              = 54,
            /// Impulse signal polarity
            ///
            /// @see constants::ImpulseSignalPolarity
            impulseSignalPolarity          = 56,
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
            vibratoryPolarityCode = 58,
            /// SEG Y Format Revision Number
            ///
            /// This is a 16-bit unsigned value with a Q-point between the first
            /// and second bytes. Thus for SEG Y Revision 1.0, as defined in 
            /// this document, this will be recorded as 010016.  
            ///
            /// This field is mandatory for all versions of SEG Y, although a 
            /// value of zero indicates “traditional” SEG Y conforming to the 
            /// 1975 standard
            segyFormatRevisionNumber       = 300,
            /// Fixed length trace flag
            ///
            /// A value of one indicates that all traces in this SEG Y file are 
            /// guaranteed to have the same sample interval and number of 
            /// samples, as specified in Textual File Header bytes 3217-3218 
            /// and 3221-3222.
            ///
            /// A value of zero indicates that the length of the traces in the 
            /// file may vary and the number of samples in bytes 115-116 of the 
            /// Trace Header must be examined to determine the actual length of 
            /// each trace. This field is mandatory for all versions of SEG Y, 
            /// although a value of zero indicates “traditional” SEG Y 
            /// conforming to the 1975 standard.
            fixedLengthTraceFlag           = 302,
            /// Number of 3200-byte, Extended Textual File Header records following the Binary Header
            ///
            /// A value of zero indicates there are no Extended Textual File 
            /// Header records (i.e. this file has no Extended Textual File 
            /// Header(s)).
            ///
            /// A value of -1 indicates that there are a variable number of 
            /// Extended Textual File Header records and the end of the Extended
            /// Textual File Header is denoted by an ((SEG: EndText)) stanza in 
            /// the final record. 
            /// 
            /// A positive value indicates that there are exactly that many 
            /// Extended Textual File Header records. Note that, although the 
            /// exact number of Extended Textual File Header records may be a 
            /// useful piece of information, it will not always be known at the
            /// time the Binary Header is written and it is not mandatory that a
            /// positive value be recorded here.  This field is mandatory for
            /// all versions of SEG Y, although a value of zero indicates 
            /// “traditional” SEG Y conforming to the 1975 standard
            nextendedTextualFileHeader     = 304
        };
        
        /**
         * @brief Static vector used to iterate over all the items of a
         * non-contiguous enumeration
         * 
         * @see Int16Fields
         */
        static const std::vector<Int16Fields> Int16List;        
        
        /**
         * @brief Returns the corresponding integer value
         * 
         * @param[in] id constants associated with the requested field
         * @return requested field 
         */
        const int32_t& operator[](const Int32Fields id) const {
            // Pointer needed to induce aliasing
            const char * pnt(&buffer_[id]);
            return *( reinterpret_cast<const int32_t *>( pnt ) );
        }
        
        /**
         * @brief Returns the corresponding integer value
         * 
         * @param[in] id constants associated with the requested field
         * @return requested field 
         */
        const int16_t& operator[](const Int16Fields id) const {
            // Pointer needed to induce aliasing
            const char * pnt (&buffer_[id]);
            return *( reinterpret_cast<const int16_t *>( pnt ) );
        }
        
        /**
         * @brief Returns the corresponding integer value
         * 
         * @param[in] id constants associated with the requested field
         * @return requested field 
         */
        int32_t& operator[](const Int32Fields id) {
            return const_cast<int32_t&>( static_cast<const BinaryFileHeader&>(*this)[id] );
        }
        
        /**
         * @brief Returns the corresponding integer value
         * 
         * @param[in] id constants associated with the requested field
         * @return requested field 
         */
        int16_t& operator[](const Int16Fields id) {
            return const_cast<int16_t&>( static_cast<const BinaryFileHeader&>(*this)[id] );
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
            return const_cast<char *>( static_cast<const BinaryFileHeader&>(*this).get() );
        }
        
    private:
        char buffer_[buffer_size];
    };
    
    /**
     * @brief Output stream operator for BinaryFileHeader
     * 
     * @param cout stream
     * @param bfh input binary file header 
     * @return cout
     * 
     * @relates BinaryFileHeader
     */
    std::ostream& operator<<(std::ostream& cout, const BinaryFileHeader& bfh);
        
}



#endif	/* SEGYFILE_BINARYFILEHEADER_H */

