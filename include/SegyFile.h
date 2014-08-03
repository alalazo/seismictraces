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

/**
 * @file SegyFile.h
 * @brief File containing data in SEG Y rev. 1 format
 */
#ifndef SEGYFILE_H
#define	SEGYFILE_H

#include<impl/SegyFile-TextualFileHeader.h>
#include<impl/SegyFile-BinaryFileHeader.h>
#include<impl/SegyFile-Trace.h>

// Enumerations and constants related to SEG Y standard
#include<impl/SegyFile-constants.h>

#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>

#include<string>
#include<memory>
#include<utility>

#include<cstddef>

namespace seismic {
    
    class SegyFileIndexer;
    class SegyFileLazyWriter;
    
    /**
     * @brief Models a file conforming to SEG Y rev 1 format
     * 
     * According to SEGY rev 1 standard (May 2002):
     * 
     * >
     * > ## SEG Y File Structure
     * > 
     * > The original SEG Y standard was produced at a time when 9-track tape
     * > was the normal storage medium for seismic data, with 800 bpi and 1600
     * > bpi in common usage and 6250 bpi on the horizon. The revised format is
     * > intended to be independent of the actual medium on which it is 
     * >recorded.
     * >
     * > The stipulation in the 1975 standard that “no more than one line of 
     * > seismic data is permitted on any one reel” became impractical long ago.
     * > The term “SEG Y file” shall be used in this revision in place of the 
     * > term “seismic reel” used in the original standard. For this standard, 
     * > the terms file and data set are synonymous. Both terms are a collection
     * > of logically related data traces or ensembles of traces and the 
     * > associated ancillary data.
     * >
     * > ...
     * >
     * > ### File Structure
     * > The first 3600-bytes of the file are the Textual File Header and the 
     * > Binary File Header written as a concatenation of a 3200-byte record 
     * > and a 400-byte record. This is optionally followed by Extended Textual 
     * > File Header(s), which consists of zero or more 3200-byte Extended 
     * > Textual File Header records. The remainder of the SEG Y file contains 
     * > a variable number of Data Trace records that are each proceeded by a 
     * > 240-byte Trace Header. The Extended Textual File Header is the only 
     * > structural change introduced in this revision and while not strictly 
     * > downward compatible with the 1975 SEG Y format, it has been carefully 
     * > designed to have minimal impact on existing SEG Y reader software. It 
     * > should be simple for existing software to be modified to detect the 
     * > presence of the new header and either process or ignore the Extended 
     * > Textual File Header.
     * >
     * > ### Number Formats
     * > In the 1975 SEG Y standard, all binary values are defined as using 
     * > “big-endian” byte ordering. This conformed to the IBM tape standard and
     * > means that, within the bytes that make up a number, the most 
     * > significant byte (containing the sign bit) is written closest to the 
     * > beginning of the file and the least significant byte is written closest
     * > to the end of the file. This byte ordering convention is maintained in 
     * > this revision of the SEG Y format and it should be adhered to for all 
     * > conforming versions of SEG Y. This is independent of the medium to 
     * > which a particular SEG Y file is written (i.e. the byte ordering is no
     * > different if the file is written to tape on a mainframe or to disk on
     * > a PC).
     * >
     * > All values in the Binary File Header and the Trace Header are two's 
     * > complement integers, either two bytes or four bytes long. There are no 
     * > floating-point values defined in the headers.
     * > 
     * > Trace Data sample values are either two's complement integers or 
     * > floating-point. This revision adds data sample formats of 8-bit integer
     * > and 32-bit IEEE floating-point. Both IBM floating-point (as defined in 
     * > the original standard) and IEEE floating-point values are written in 
     * > big-endian byte order (i.e. with the sign/exponent byte written 
     * > closest to the beginning of the file).
     * >
     * > ### Varying Trace Lengths
     * > The SEG Y standard specifies fields for sampling interval and number 
     * > of samples at two separate locations in the file. The Binary File 
     * > Header contains values that apply to the whole file and the Trace 
     * > Headers contain values that apply to the associated trace. The original
     * > standard is unclear about how these are to be used together. One view 
     * > is that variable length traces are supported in SEG Y, with the number 
     * > of samples in the trace header allowed to vary from trace to trace and 
     * > to vary from the value in the Binary File Header. An alternate view is 
     * > that all traces in a SEG Y file will be the same length and the value 
     * > for the number of samples will be the same in the Binary File Header 
     * > and all Trace Headers. In the second case, the data traces are padded 
     * > or truncated as necessary.
     * >
     * > In SEGY rev 1, varying trace lengths in a file are explicitly allowed.
     * > The values for sampling interval and number of samples in the Binary 
     * > File Header should be for the primary set of seismic data traces in the
     * > file. This approach allows the Binary File Header to be read and say, 
     * > for instance, “this is six seconds data sampled at a two-millisecond 
     * > sampling interval”. The value for the number of samples in each 
     * > individual Trace Header may vary from the value in the Binary File 
     * > Header and reflect the actual number of samples in a trace. The number 
     * > of bytes in each trace record must be consistent with the number of 
     * > samples in the Trace Header.  This is particularly important for SEG Y 
     * > data written to disk files.
     * >
     * > Allowing variable length traces dictates sequential access and 
     * > precludes random access in a disk file, since the locations of traces 
     * > after the first are not known. To enable the option of random access, 
     * > a new field in the Binary File Header has been defined as a fixed 
     * > length trace flag. If this flag is set, all traces in the file must 
     * > have the same length. This will typically be the case for poststack 
     * > data.
     * >
     * > Making the value for number of samples in the Binary File Header the 
     * > maximum trace length in the file, rather than the length of the primary
     * > set of data traces was seriously considered.  However, it should be 
     * > noted that the maximum trace length is not necessarily known at the 
     * > time the Binary File Header is written, particularly in a transcription
     * > environment. This is the same reason why there are no fields in the 
     * > Binary File Header such as “first and last record number”. The fixed 
     * > length trace flag goes some way to ameliorating the problems induced by
     * > having variable length traces. If the fixed record length flag is set, 
     * > the maximum trace length in the file is known (i.e. all traces are 
     * > the same length).
     * >
     * > ### Coordinates 
     * > Knowing the source and trace locations is a primary requirement for 
     * > processing seismic data, and knowing the location of the processed data
     * > with respect to other data is essential for interpretation. 
     * > Traditionally seismic coordinates have been supplied as geographic 
     * > coordinates and/or grid coordinates. SEG Y accommodates either form. 
     * > However locations are ambiguous without clear coordinate reference 
     * > system (CRS) definition. SEG Y rev 1 significantly expands the ability 
     * > to define the CRS used for the coordinates contained within the Binary 
     * > Header, the Extended Textual Headers and the Trace Headers. A single 
     * > CRS must be used for all coordinates within an individual SEG Y data 
     * > set.  Additionally the coordinate units must be the same for all 
     * > coordinates.
     * 
     * In the following it is shown how to __read a SEGY file and convert traces__:
     * @include example05.cpp
     * 
     * In the following it is shown how to __read a SEGY file, modify the traces and write them back to another file__:
     * @include example06.cpp
     * 
     */
    class SegyFile {
    public:
        /// Trace header plus corresponding raw (stream of bytes) trace data
        using raw_trace_type = std::pair< TraceHeader::smart_reference_type, std::vector<char> >; 
        
        /// Trace header plus corresponding trace data of type T
        template <class T>
        using trace_type = Trace<T>;

        /**
         * @brief Opens an existing SEG Y file in r/w mode
         * 
         * @param[in] filename name of the SEG Y file to be read/written
         * @param[in] revision_tag type of SEG Y file to be created
         * 
         */
        SegyFile(const char * filename, const std::string & revision_tag = "Rev0");
        
        /**
         * @brief Returns the textual file header
         * 
         * @return textual file header
         */
        const TextualFileHeader& getTextualFileHeader() const;
        
        /**
         * @brief Returns the textual file header
         * 
         * @return textual file header
         */
        TextualFileHeader& getTextualFileHeader();
        
        /**
         * @brief Returns the binary file header
         * 
         * @return binary file header
         */
        const BinaryFileHeader& getBinaryFileHeader() const;
        
        /**
         * @brief Returns the binary file header
         * 
         * @return binary file header
         */
        BinaryFileHeader& getBinaryFileHeader();        
        
        /**
         * @brief Commits in memory modifications to file headers
         */
        void commitFileHeaderModifications(); 
        
        /**
         * @brief Commits in memory modifications to the list of traces
         */
        void commitTraceModifications();
                
        /**
         * @brief Returns the number of traces that are currently stored in the SEG Y file
         * 
         * @return number of traces
         */
        size_t ntraces() const;
        
        /**
         * @brief Reads a trace from file
         * 
         * Indexes are zero-based
         * 
         * @param[in] n index of the trace to be read
         * @return trace header and trace data
         */
        raw_trace_type readRawTrace(const size_t n);
        
        /**
         * @brief Appends a trace to the end of the SEG Y file
         * 
         * @param[in] trace trace to be appended
         */
        void appendRawTrace(const raw_trace_type& trace);
        
        /**
         * @brief Overwrites a trace at position n
         * 
         * @param[in] trace trace to be overwritten
         * @param[in] n index of the trace to be overwritten
         */
        void overwriteRawTrace(const raw_trace_type& trace, const size_t n);
        
        /**
         * @brief Reads a trace from file
         * 
         * Indexes are zero-based
         * 
         * @param[in] n index of the trace to be read
         * @return seismic trace (header + data)
         */
        template<class T>
        Trace<T> readTraceAs(const size_t n);
        
        /**
         * @brief Appends a trace to the end of the SEG Y file
         * 
         * @param[in] trace trace to be appended
         */
        template<class T>
        void appendTrace(const Trace<T>& trace);        
        
        /**
         * @brief Overwrites a trace at position n
         * 
         * @param[in] trace trace to be overwritten
         * @param[in] n index of the trace to be overwritten
         */
        template<class T>
        void overwriteTrace(const Trace<T>& trace, const size_t n);
                
        /**
         * @brief Returns the revision tag for the given SEG Y file
         * 
         * @return tag for the given SEG Y file
         */
        const std::string & tag() const;
        
        /**
         * @brief Returns the path of the SEG Y file
         * 
         * @return path of the SEG Y file
         */
        const boost::filesystem::path& path() const;
        
        ~SegyFile();

    private:
        //////////
        // Helper methods
        //////////
        
        template<class T>
        void checkConsistencyWithType();
        
        template<class T>
        raw_trace_type convertToRawType(const Trace<T>& trace);
        
        //////////
        // File related information
        //////////
        boost::filesystem::path filePath_;
        boost::filesystem::fstream fstream_;                
        std::shared_ptr<TextualFileHeader> tfh_;
        std::shared_ptr<BinaryFileHeader> bfh_;
        const std::string tag_;
        //////////
        // Indexer
        //////////
        std::shared_ptr<SegyFileIndexer> indexer_;
        //////////
        // Lazy writer
        //////////
        std::shared_ptr<SegyFileLazyWriter> writer_;                
    };
        
}


#endif	/* SEGYFILE_H */

