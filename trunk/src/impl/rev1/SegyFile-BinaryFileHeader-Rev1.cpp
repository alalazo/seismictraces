#include<impl/rev1/SegyFile-BinaryFileHeader-Rev1.h>
#include<impl/utilities-inl.h>

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
        
        vector<rev1::bfh::Int16FieldsRev1> initializeInt16List() {
            vector<rev1::bfh::Int16FieldsRev1> int16List;
            int16List.push_back( rev1::bfh::segyFormatRevisionNumber   );
	    int16List.push_back( rev1::bfh::fixedLengthTraceFlag       );
	    int16List.push_back( rev1::bfh::nextendedTextualFileHeader );
	    return int16List;
        }
    }
    ////////////////////
    // Static vectors
    ////////////////////
    const vector<rev1::bfh::Int16FieldsRev1> ConcreteBinaryFileHeader<Rev1>::Int16List(initializeInt16List());
    
    void ConcreteBinaryFileHeader<Rev1>::print(std::ostream& cout) const {
        ConcreteBinaryFileHeader<Rev0>::print(cout);
        cout << "**** REV-1 FIELDS ****" << endl;
        cout << endl;
        cout << "SEGY format revision number:                       " << (*this)[field(rev1::bfh::segyFormatRevisionNumber)] << endl;
        cout << "Fixed length trace flag:                           " << (*this)[field(rev1::bfh::fixedLengthTraceFlag)] << endl;
        cout << "Number of Extended Textual File Headers:           " << (*this)[field(rev1::bfh::nextendedTextualFileHeader)] << endl;
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

            void operator()(rev1::bfh::Int16FieldsRev1 idx) {
                invertByteOrder(bfh_[field(idx)]);
            }
            
        private:
            ConcreteBinaryFileHeader<Rev1>& bfh_;
        };

    }
    
    void ConcreteBinaryFileHeader<Rev1>::invertByteOrder() {
        ConcreteBinaryFileHeader<Rev0>::invertByteOrder();
        BfhSwapByteOrder swapVisitor( *this );        
        std::for_each(ConcreteBinaryFileHeader<Rev1>::Int16List.begin(), ConcreteBinaryFileHeader<Rev1>::Int16List.end(), swapVisitor);
    }
}
