#include<SeismicTrace-inl.h>
#include<gtest/gtest.h>

namespace {
    TEST(SeismicTrace,Assignment) {
        seismic::SeismicTrace trace;
        
        trace(seismic::X) = 0.1f;
        trace(seismic::Y) = 0.2f;
        trace(seismic::Z) = 0.3f;
        
        EXPECT_EQ(trace(seismic::X),0.1f);
        EXPECT_EQ(trace(seismic::Y),0.2f);
        EXPECT_EQ(trace(seismic::Z),0.3f);
        
        trace.shot(seismic::X) = 10.1f;
        trace.shot(seismic::Y) = 20.1f;
        trace.shot(seismic::Z) = 30.1f;

        EXPECT_EQ(trace.shot(seismic::X),10.1f);
        EXPECT_EQ(trace.shot(seismic::Y),20.1f);
        EXPECT_EQ(trace.shot(seismic::Z),30.1f);
        
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

