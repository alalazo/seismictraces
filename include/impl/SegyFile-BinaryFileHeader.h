#ifndef SEGYFILE_BINARYFILEHEADER_H
#define	SEGYFILE_BINARYFILEHEADER_H

#include<string>
#include<iostream>

// Forced by the use of C++03
#include<stdint.h>

namespace seismic {
    
    class BinaryFileHeader {
    public:
        static const int buffer_size = 400;
        
        enum Int32Fields {
            jobID      = 0,            
            lineNumber = 4,
            reelNumber = 8
        };

        enum Int16Fields {
            nDataTraces                    = 12,
            nAuxiliaryTraces               = 14,
            sampleInterval                 = 16,
            sampleIntervalOriginalField    = 18,
            nsamplesDataTrace              = 20,
            nsamplesDataTraceOriginalField = 22,
            formatCode                     = 24,
            ensembleFold                   = 26,
            traceSortingCode               = 28,
            verticalSumCode                = 30,
            sweepFrequencyStart            = 32,
            sweepFrequencyEnd              = 34,
            sweepLength                    = 36,
            sweepTypeID                    = 38,
            traceNumberSweepChannel        = 40,
            sweepTraceTaperLengthStart     = 42,
            sweepTraceTaperLengthEnd       = 44,
            taperType                      = 46,
            correlatedDataTraces           = 48,
            binaryGainRecovery             = 50,
            amplitudeRecoveryMethod        = 52,
            measurementSystem              = 54,
            impulseSignalPolarity          = 56,
            vibratoryPolarityCode          = 58,
            segyFormatRevisionNumber       = 300,
            fixedLengthTraceFlag           = 302,
            nextendedTextualFileHeader     = 304
        };
        
        //BinaryFileHeader();
        
        const int32_t& operator[](const Int32Fields id) const {
            const char * pnt(&buffer_[id]);
            return *( reinterpret_cast<const int32_t *>( pnt ) );
        }
        
        const int16_t& operator[](const Int16Fields id) const {
            const char * pnt (&buffer_[id]);
            return *( reinterpret_cast<const int16_t *>( pnt ) );
        }
        
        int32_t& operator[](const Int32Fields id) {
            return const_cast<int32_t&>( static_cast<const BinaryFileHeader&>(*this)[id] );
        }
        
        int16_t& operator[](const Int16Fields id) {
            return const_cast<int16_t&>( static_cast<const BinaryFileHeader&>(*this)[id] );
        }
               
        const char * get() const {
            return &buffer_[0];
        }
        
        char * get() {
            return const_cast<char *>( static_cast<const BinaryFileHeader&>(*this).get() );
        }
        
    private:
        char buffer_[buffer_size];
    };
    
    std::ostream& operator<<(std::ostream& cout, const BinaryFileHeader& bfh);
}



#endif	/* SEGYFILE_BINARYFILEHEADER_H */

