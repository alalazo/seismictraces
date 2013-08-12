/**
 * @file utilities-inl.h
 * @brief Utility functions
 */
#ifndef UTILITIES_INL_H
#define	UTILITIES_INL_H

// Forced by the use of C++03
#include<stdint.h>

namespace seismic {
            
    void swapByteOrder(int16_t& obj) {
        char * pnt = reinterpret_cast<char*>(&obj);        
        char   tmp = pnt[0];
        
        pnt[0] = pnt[1];
        pnt[1] = tmp;
    }
    
    void swapByteOrder(int32_t& obj) {
        char * pnt = reinterpret_cast<char*>(&obj);        
        char   tmp = pnt[0];
        
        pnt[0] = pnt[3];
        pnt[3] = tmp;
        
        tmp    = pnt[1];
        pnt[1] = pnt[2];
        pnt[2] = tmp;
    }
    
    void swapByteOrder(float& obj) {
        char * pnt = reinterpret_cast<char*>(&obj);        
        char   tmp = pnt[0];
        
        pnt[0] = pnt[3];
        pnt[3] = tmp;
        
        tmp    = pnt[1];
        pnt[1] = pnt[2];
        pnt[2] = tmp;
    }
}

#endif	/* UTILITIES_INL_H */

