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

