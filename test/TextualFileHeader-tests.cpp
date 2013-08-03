#include<impl/SegyFile-TextualFileHeader.h>
#include<gtest/gtest.h>

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

