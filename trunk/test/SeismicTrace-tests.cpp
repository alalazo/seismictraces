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
#include<SeismicTrace-inl.h>
#include<gtest/gtest.h>

using namespace seismic;

namespace {
    TEST(SeismicTrace,Assignment) {
        SeismicTrace trace;
        
        trace(SeismicTrace::X) = 0.1f;
        trace(SeismicTrace::Y) = 0.2f;
        trace(SeismicTrace::Z) = 0.3f;
        
        EXPECT_EQ(trace(SeismicTrace::X),0.1f);
        EXPECT_EQ(trace(SeismicTrace::Y),0.2f);
        EXPECT_EQ(trace(SeismicTrace::Z),0.3f);
        
        trace.shot(SeismicTrace::X) = 10.1f;
        trace.shot(SeismicTrace::Y) = 20.1f;
        trace.shot(SeismicTrace::Z) = 30.1f;

        EXPECT_EQ(trace.shot(SeismicTrace::X),10.1f);
        EXPECT_EQ(trace.shot(SeismicTrace::Y),20.1f);
        EXPECT_EQ(trace.shot(SeismicTrace::Z),30.1f);
        
        trace.dt() = 0.1f;

        EXPECT_EQ(trace.dt(),0.1f);
        
        for (int ii = 0; ii < 100; ii++) {
            trace.push_back(ii * 2.5f);
        }
        EXPECT_EQ(trace.size(),100);
    }
}

int main(int argc, char ** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();    
}

