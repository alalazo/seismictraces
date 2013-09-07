#ifndef SEGYFILE_FIELDS_REV1_H
#define	SEGYFILE_FIELDS_REV1_H

#include<impl/metafunctions-inl.h>
#include<impl/rev0/SegyFile-Fields-Rev0.h>

// Forced by the use of C++03
#include<stdint.h>

namespace seismic {
    /**
     * @brief Template tag to intantiate a Rev0 conforming class
     */
    class Rev1 {};
    
    namespace rev1 {
        namespace bfh {
            using namespace rev0::bfh;

            /**
             * @brief Fields that are mapped to 16-bit integers
             */
            enum Int16FieldsRev1 {
                /// SEG Y Format Revision Number
                ///
                /// This is a 16-bit unsigned value with a Q-point between the first
                /// and second bytes. Thus for SEG Y Revision 1.0, as defined in 
                /// this document, this will be recorded as 010016.  
                ///
                /// This field is mandatory for all versions of SEG Y, although a 
                /// value of zero indicates “traditional” SEG Y conforming to the 
                /// 1975 standard
                segyFormatRevisionNumber = 300,
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
                fixedLengthTraceFlag = 302,
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
                nextendedTextualFileHeader = 304
            };
        }
    }
    
    SET_SUBSCRIPT_RETURN_TYPE( rev1::bfh::Int16FieldsRev1 , int16_t )
        
}

#endif	/* SEGYFILE_FIELDS_REV1_H */

