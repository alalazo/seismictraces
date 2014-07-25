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
#include<impl/SegyFile-TextualFileHeader.h>

#include<algorithm>
#include<iostream>
#include<iomanip>
#include<stdexcept>
#include<cstring>

#include "impl/utilities-inl.h"

using namespace std;

namespace seismic {

    //
    // TextualFileHeader
    //

    TextualFileHeader::TextLine TextualFileHeader::operator[](const int n) {
        if ((n >= nlines) || (n < 0)) {
            throw runtime_error("TextualFileHeader: line access out of range\n");
        }
        return TextualFileHeader::TextLine(&buffer_[n][0]);
    }

    const TextualFileHeader::TextLine TextualFileHeader::operator[](const int n) const {
        return static_cast<const TextualFileHeader::TextLine> (const_cast<TextualFileHeader&> (*this)[n]);
    }

    //
    // TextualFileHeader::TextLine
    // 

    TextualFileHeader::TextLine& TextualFileHeader::TextLine::operator =(const TextLine& other) {
        for (int ii = 0; ii < TextualFileHeader::line_length; ii++) {
            pnt_[ii] = other.pnt_[ii];
        }
        return (*this);
    }

    TextualFileHeader::TextLine& TextualFileHeader::TextLine::operator =(const std::string& line) {
        // Check line length and throw an exception if greater than expected
        if (line.size() > TextualFileHeader::line_length) {
            throw runtime_error("TextualFileHeader: line is wider than 80 characters\n");
        }
        // Copy the string into the array of char
        for (unsigned int ii = 0; ii < line.size(); ii++) {
            pnt_[ii] = line[ii];
        }
        // Fill with spaces up to line_length
        for (unsigned int ii = line.size(); ii < TextualFileHeader::line_length; ii++) {
            pnt_[ii] = ' ';
        }
        return (*this);
    }

    TextualFileHeader::TextLine& TextualFileHeader::TextLine::operator =(const char* line) {
        unsigned int strsize = strlen(line);
        // Check line length and throw an exception if greater than expected
        if (strsize > TextualFileHeader::line_length) {
            throw runtime_error("TextualFileHeader: line is wider than 80 characters\n");
        }
        // Copy the string into the array of char
        for (unsigned int ii = 0; ii < strsize; ii++) {
            pnt_[ii] = line[ii];
        }
        // Fill with spaces up to line_length
        for (unsigned int ii = strsize; ii < TextualFileHeader::line_length; ii++) {
            pnt_[ii] = ' ';
        }
        return (*this);
    }
    
    TextualFileHeader::TextLine::TextLine(const TextLine& other) {
        *this = other;
    }
    
    char & TextualFileHeader::TextLine::operator [](const int n) {
        if ( (n < 0) || (n >= TextualFileHeader::line_length) ) {
            throw runtime_error("TextualFileHeader: character access out of range\n"); 
        }
        return pnt_[n];
    }
    
    const char & TextualFileHeader::TextLine::operator [](const int n) const {
        return static_cast<const char&>( const_cast<TextualFileHeader::TextLine&>(*this)[n] );
    }
    
    //
    // External functions and operator overloads
    //
    
    ostream & operator<<(ostream& cout, const TextualFileHeader& tfh) {
        for( unsigned int ii = 0; ii < TextualFileHeader::nlines; ii++) {
            for( unsigned int jj = 0; jj < TextualFileHeader::line_length; jj++) {
                cout << tfh[ii][jj];
            }            
            cout << endl;
        }
        return cout;
    }
    
    void ebcdic2ascii(TextualFileHeader& tfh) {
        for_each(tfh.get(),tfh.get() + tfh.nlines*tfh.line_length,
            [](char& x){
                unsigned char * y = reinterpret_cast<unsigned char *>(&x);
                ebcdic2ascii(*y);
            });
    }
    
    void ascii2ebcdic(TextualFileHeader& tfh) {
        for_each(tfh.get(),tfh.get() + tfh.nlines*tfh.line_length,
            [](char& x){
                unsigned char * y = reinterpret_cast<unsigned char *>(&x);
                ascii2ebcdic(*y);
            });        
    }
    
}

