#ifndef SEGYFILE_CONSTANTS_H
#define	SEGYFILE_CONSTANTS_H

namespace seismic {

    /// Textual file header size in byte
    const int textualFileHeaderSize = 3200;
    /// Binary file header file size in byte
    const int binaryFileHeaderSize = 400;
    /// Extended textual file header size in byte
    const int extendedTextualFileHeaderSize = 3200;
    /// Trace header size in byte
    const int traceHeaderSize = 240;
    
//    /* Number of field (good + unassigned) of BFH */
//#define CS_NUMBFH  32
//    /* From CS_UNASSBFH1STA to CS_UNASSBFH1END field of BFH are not unassigned (good field ) */
//#define CS_UNASSBFH1STA  0
//#define CS_UNASSBFH1END  26
//#define CS_UNASSBFH2STA  28
//#define CS_UNASSBFH2END  30
//
//    /* Trace Header */
//#define CS_SIZETRH 240
//    /* Number of field (good + unassigned) of TRH */
//#define CS_NUMTRH  90
//    /* See BFH */
//#define CS_UNASSTRH1STA  0
//#define CS_UNASSTRH1END  88
//
//#define CS_SIZEHEADER (CS_SIZETFH+CS_SIZEBFH)
//
//    /* Format code (byte 25-26) of BFH */
//#define CS_FC_4IBM   1
//#define CS_FC_4INT   2
//#define CS_FC_2INT   3
//#define CS_FC_4FXD   4
//#define CS_FC_4IEEE  5
//#define CS_FC_NOTUS1 6
//#define CS_FC_NOTUS2 7
//#define CS_FC_1INT   8
//
//#define CS_SUCCESS EXIT_SUCCESS
//#define CS_FAILURE EXIT_FAILURE
//#define CS_NOTIMPLEMENTED -1
//
}

#endif	/* SEGYFILE_CONSTANTS_H */

