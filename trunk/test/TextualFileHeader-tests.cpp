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
#include<gtest/gtest.h>

/**
 * @file  TextualFileHeader-tests.cpp
 * @brief Unit tests for TextualFileHeader class
 * @test  Tests basic features for a TextualFileHeader instance
 */

#include<string>

namespace {
    TEST(TextualFileHeader,Assignment) {
        seismic::TextualFileHeader tfh;
        EXPECT_EQ( tfh[1][0], ' ');
        
        tfh[0] = "Hello world!";
        EXPECT_EQ( tfh[0][0], 'H');
        
        std::string line("This is the second line");
        tfh[1] = line;
        
        EXPECT_EQ( tfh[1][1], 'h' );
        
        tfh[2] = tfh[1];
        
        for(unsigned int ii = 0; ii < seismic::TextualFileHeader::line_length; ii++) {
            EXPECT_EQ(tfh[1][ii],tfh[2][ii]);
        }        
        
        seismic::TextualFileHeader clone(tfh);
        for(unsigned int ii = 0; ii < seismic::TextualFileHeader::nlines; ii++) {
            for(unsigned int jj = 0; jj < seismic::TextualFileHeader::line_length; jj++) {
                EXPECT_EQ(tfh[ii][jj],clone[ii][jj]);
            }
        }
    }
    
}

int main(int argc, char ** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();    
}

