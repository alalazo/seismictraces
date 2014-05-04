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
#include<impl/rev1/SegyFile-BinaryFileHeader-Rev1.h>
#include<impl/utilities-inl.h>

#include<sstream>
#include<stdexcept>

using namespace std;

namespace seismic {
    
    namespace {        
        ////////////////////
        // The following functions are needed to initalize the static vectors
        // that contain all the items of non-contiguous enumerations
        //
        // NOTE: they need to be updated manually whenever the enumerations are 
        // changed
        //
        ////////////////////
        
        vector<Int16Field> initializeInt16List() {
            vector<Int16Field> int16List;
            int16List.push_back( rev1::bfh::segyFormatRevisionNumber   );
	    int16List.push_back( rev1::bfh::fixedLengthTraceFlag       );
	    int16List.push_back( rev1::bfh::nextendedTextualFileHeader );
	    return int16List;
        }
    }
    ////////////////////
    // Static vectors
    ////////////////////

    const vector<Int16Field>& ConcreteBinaryFileHeader<Rev1>::Int16List() {
        static const vector<Int16Field> list( initializeInt16List() );
        return list;
    }

    void ConcreteBinaryFileHeader<Rev1>::print(std::ostream& cout) const {
        ConcreteBinaryFileHeader<Rev0>::print(cout);
        cout << "**** REV-1 FIELDS ****" << endl;
        cout << endl;
        cout << "SEGY format revision number:                       " << (*this)[rev1::bfh::segyFormatRevisionNumber] << endl;
        cout << "Fixed length trace flag:                           " << (*this)[rev1::bfh::fixedLengthTraceFlag] << endl;
        cout << "Number of Extended Textual File Headers:           " << (*this)[rev1::bfh::nextendedTextualFileHeader] << endl;
        cout << endl;        
    }
    
    namespace {

        /// @todo TO BE SUBSTITUTED WITH LAMBDAS AS SOON AS C++11 WILL BE ALLOWED 
        
        /**
         * @brief Functor that given a field of a binary header file, swaps its byte order
         */
        class BfhSwapByteOrder {
        public:

            BfhSwapByteOrder(ConcreteBinaryFileHeader<Rev1>& bfh) : bfh_(bfh) {
            }

            void operator()(Int16Field idx) {
                invertByteOrder(bfh_[idx]);
            }
            
        private:
            ConcreteBinaryFileHeader<Rev1>& bfh_;
        };

    }
    
    void ConcreteBinaryFileHeader<Rev1>::invertByteOrder() {
        // Invert the fields of Rev0
        ConcreteBinaryFileHeader<Rev0>::invertByteOrder();
        // Invert fields that are specific to Rev1
        std::for_each(
                ConcreteBinaryFileHeader<Rev1>::Int16List().begin(),
                ConcreteBinaryFileHeader<Rev1>::Int16List().end(),
                [this](const Int16Field & idx) {
                    seismic::invertByteOrder((*this)[idx]);
                }
        );
    }

    void ConcreteBinaryFileHeader<Rev1>::checkConsistencyOrThrow() const {
        ConcreteBinaryFileHeader<Rev0>::checkConsistencyOrThrow();
        stringstream estream;
        bool         checkFailed = false;
        // Fixed length trace flag
        switch ( (*this)[rev1::bfh::fixedLengthTraceFlag] ) {
            case( 0 ):
            case( 1 ):
                break;
            default:
                checkFailed = true;
                estream << " Invalid value of fixed length trace flag (" << (*this)[rev1::bfh::fixedLengthTraceFlag] << ")" << endl;
                break;
        }
        // Number of extended textual file headers
        if ( (*this)[rev1::bfh::nextendedTextualFileHeader] < -1 ) {
            checkFailed = true;
            estream << "Invalid number of extended textual file header (" << (*this)[rev1::bfh::nextendedTextualFileHeader] << ")" << endl;
        }
        // Throw an exception if some consistency check failed
        if ( checkFailed ) {
            throw runtime_error( estream.str() );
        }
    }
    
    const bool ConcreteBinaryFileHeader<Rev1>::isRegistered(
            BinaryFileHeader::factory_type::getFactory()->registerType( "Rev1", new ConcreteBinaryFileHeader<Rev1> )
            );
    
}
