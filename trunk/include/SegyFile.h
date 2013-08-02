#ifndef SEGYFILE_H
#define	SEGYFILE_H

#include<string>
#include<iostream>

namespace seismic {
    
    class TextualFileHeader;
    class BinaryFileHeader;
    class SeismicTrace;
    
    class SegyFile {
    public:
        enum FileMode {READ, WRITE, READWRITE};
        
        SegyFile(
                const std::string& filename, const FileMode mode,
                TextualFileHeader& tfh, BinaryFileHeader& bfh
                );
        
        void read  (SeismicTrace& trace, int n) const;
        void append(SeismicTrace& trace);
        
        ~SegyFile();
        
    private:
        int ntraces_;
    };
    
    
    /**
     * @brief This class models the Textual file header of a SEGY file
     * 
     * According to SEGY rev 1 standard (May 2002):
     * 
     * > The first 3200-byte, Textual file header record contains 40 lines 
     * > of textual information, providing a human readable description of the 
     * > seismic data in the SEGY file.
     * 
     * The class can be thought as a 40 x 80 table of characters with some 
     * additional checks to reveal non-conformity to the structure prescribed 
     * in the SEGY rev 1 standard.
     * 
     */
    class TextualFileHeader {
    public:
        enum { nlines = 40, line_length = 80};
    private:
        /**
         * @brief This class models a single line in the textual file header
         */
        class TextLine {
        public:

            TextLine(char * pnt) : pnt_(pnt) {
            }

            TextLine(const TextLine& other);
            
            TextLine& operator=(const TextLine& other);
            
            TextLine& operator=(const std::string& line);
            
            TextLine& operator=(const char * line);
            
            /**
             * @brief Returns a single character in the line
             * 
             * The line is 80 characters long 
             * 
             * @param n number of the characters in the line
             * @return requested character
             */
            char & operator[](const int n);
            
            /**
             * @brief Returns a single character in the line
             * 
             * The line is 80 characters long 
             * 
             * @param n number of the characters in the line
             * @return requested character
             */
            const char & operator[](const int n) const;
        private:
            char * pnt_;
        };
        
    public:                    
        TextualFileHeader() {
            for (unsigned int ii = 0; ii < TextualFileHeader::nlines; ii++) {
                for (unsigned int jj = 0; jj < TextualFileHeader::line_length; jj++) {
                    buffer_[ii][jj] = ' ';
                }
            }
        }
        
        /**
         * @brief Returns a line of the textual file header
         * 
         * __Note__: each line is 80 characters long
         * 
         * @param n number of the line to be returned (must be less than 40)
         * @return Text line number n
         */
        TextLine operator[](const int n);
        
        /**
         * @brief Returns a line of the textual file header
         * 
         * __Note__: each line is 80 characters long
         * 
         * @param n number of the line to be returned (must be less than 40)
         * @return Text line number n
         */
        const TextLine operator[](const int n) const;

    private:
        char buffer_[nlines][line_length];
    } ;

    std::ostream& operator<<(std::ostream& cout, const TextualFileHeader& tfh);
    
}


#endif	/* SEGYFILE_H */

