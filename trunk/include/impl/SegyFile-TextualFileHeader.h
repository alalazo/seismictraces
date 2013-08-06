/**
 * @file SegyFile-TextualFileHeader.h
 * @brief Textual file header of a SEGY file
 */
#ifndef SEGYFILE_TEXTUALFILEHEADER_H
#define	SEGYFILE_TEXTUALFILEHEADER_H

#include<string>

namespace seismic {

    /**
     * @brief This class models the Textual file header of a SEGY file
     * 
     * According to SEGY rev 1 standard (May 2002):
     * 
     * > The first 3200-byte, Textual File Header record contains 40 lines of 
     * > textual information, providing a human-readable description of the 
     * > seismic data in the SEG Y file.  This information is free form and is 
     * > the least well defined of the headers in the 1975 standard, although 
     * > the standard did provide a suggested layout for the first 20 lines.  
     * > While there would be distinct advantages in making the layout of this 
     * > header more rigid, it was decided that it would not be practicable to 
     * > produce a layout that would be universally acceptable in the light of 
     * > how it is currently used.
     * >
     * > The SEG Y rev 1 standard defines a separate textual header with a more 
     * > comprehensively defined structure, where textual information can be 
     * > stored in a machine-readable way.  This new header will be known as the
     * > Extended Textual File Header.
     * > Note that the “traditional” Textual File Header is completely separate 
     * > from the Extended Textual File Header and will still be the primary 
     * > location for human readable information about the contents of the file.
     * > In particular, it should contain information about any unusual features
     * > in the file, such as if the delay recording time in trace header 
     * > bytes 109-110 is non-zero.  The revision level of the SEG-Y format 
     * > (Binary File Header bytes 3501-3502) being used must be included for 
     * > all files written in the SEG Y rev 1 format.  
     * > It is mandatory that the SEG Y revision level be included in the 
     * > Textual File Header.
     * 
     * Technicalities apart, this class is a 40 x 80 table of characters with some 
     * additional checks to reveal non-conformity to the structure prescribed 
     * in the SEGY rev 1 standard.
     * 
     */
    class TextualFileHeader {
    public:
        /// Number of lines in the Textual fileheader
        static const int nlines = 40;
        /// Length of a single line in the Textual file header
        static const int line_length = 80;
    private:
        /**
         * @brief This class models a single line in the textual file header
         */
        class TextLine {
        public:

            /**
             * @brief Constructor from a pointer to the beginning of the line 
             * @param[in] pnt pointer to the beginning of the line
             */
            TextLine(char * pnt) : pnt_(pnt) {
            }

            /**
             * @brief Copy constructor
             * @param[in] other line to copy
             */
            TextLine(const TextLine& other);
            
            TextLine& operator=(const TextLine& other);
            
            TextLine& operator=(const std::string& line);
            
            TextLine& operator=(const char * line);
            
            /**
             * @brief Returns a single character in the line
             * 
             * The line is 80 characters long 
             * 
             * @param[in] n number of the characters in the line
             * @return requested character
             */
            char & operator[](const int n);
            
            /**
             * @brief Returns a single character in the line
             * 
             * The line is 80 characters long 
             * 
             * @param[in] n number of the characters in the line
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
         * @param[in] n number of the line to be returned (must be less than 40)
         * @return Text line number n
         */
        TextLine operator[](const int n);
        
        /**
         * @brief Returns a line of the textual file header
         * 
         * __Note__: each line is 80 characters long
         * 
         * @param[in] n number of the line to be returned (must be less than 40)
         * @return Text line number n
         */
        const TextLine operator[](const int n) const;

        /**
         * @brief Returns a raw pointer to the underlying buffer
         * 
         * @return Pointer to the beginning of the buffer
         */
        const char * get() const {
            return &buffer_[0][0];
        }
        
        /**
         * @brief Returns a raw pointer to the underlying buffer
         * 
         * @return Pointer to the beginning of the buffer
         */
        char * get() {
            return const_cast<char *>( static_cast<const TextualFileHeader&>(*this).get() );
        }
        
    private:
        char buffer_[nlines][line_length];
    } ;

    std::ostream& operator<<(std::ostream& cout, const TextualFileHeader& tfh);
    
}


#endif	/* SEGYFILE_TEXTUALFILEHEADER_H */

