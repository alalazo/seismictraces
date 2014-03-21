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
#include<impl/rev0/SegyFile-BinaryFileHeader-Rev0.h>
#include<impl/SegyFile-constants.h>
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
        
        vector<rev0::bfh::Int32FieldsRev0> initializeInt32List() {
            vector<rev0::bfh::Int32FieldsRev0> int32List;
            int32List.push_back( rev0::bfh::jobID      );
            int32List.push_back( rev0::bfh::lineNumber );
            int32List.push_back( rev0::bfh::reelNumber );
            return int32List;
        }
        
        vector<rev0::bfh::Int16FieldsRev0> initializeInt16List() {
            vector<rev0::bfh::Int16FieldsRev0> int16List;
	    int16List.push_back(rev0::bfh::nDataTraces                   );		   
	    int16List.push_back(rev0::bfh::nAuxiliaryTraces              );	   
	    int16List.push_back(rev0::bfh::sampleInterval                );		   
	    int16List.push_back(rev0::bfh::sampleIntervalOriginalField   );
	    int16List.push_back(rev0::bfh::nsamplesDataTrace             );	   
	    int16List.push_back(rev0::bfh::nsamplesDataTraceOriginalField);
	    int16List.push_back(rev0::bfh::formatCode                    );		   
	    int16List.push_back(rev0::bfh::ensembleFold                  );		   
	    int16List.push_back(rev0::bfh::traceSortingCode              );	   
	    int16List.push_back(rev0::bfh::verticalSumCode               );	   
	    int16List.push_back(rev0::bfh::sweepFrequencyStart           );	   
	    int16List.push_back(rev0::bfh::sweepFrequencyEnd             );	   
	    int16List.push_back(rev0::bfh::sweepLength                   );		   
	    int16List.push_back(rev0::bfh::sweepTypeID                   );		   
	    int16List.push_back(rev0::bfh::traceNumberSweepChannel       );   
	    int16List.push_back(rev0::bfh::sweepTraceTaperLengthStart    );
	    int16List.push_back(rev0::bfh::sweepTraceTaperLengthEnd      );  
	    int16List.push_back(rev0::bfh::taperType                     );		   
	    int16List.push_back(rev0::bfh::correlatedDataTraces          );	   
	    int16List.push_back(rev0::bfh::binaryGainRecovered           );	   
	    int16List.push_back(rev0::bfh::amplitudeRecoveryMethod       );   
	    int16List.push_back(rev0::bfh::measurementSystem             );	   
	    int16List.push_back(rev0::bfh::impulseSignalPolarity         );	   
	    int16List.push_back(rev0::bfh::vibratoryPolarityCode         );	   
            return int16List;
        }
    }
    ////////////////////
    // Static vectors
    ////////////////////
    const vector<rev0::bfh::Int32FieldsRev0> ConcreteBinaryFileHeader<Rev0>::Int32List(initializeInt32List());
    const vector<rev0::bfh::Int16FieldsRev0> ConcreteBinaryFileHeader<Rev0>::Int16List(initializeInt16List());
    
    void ConcreteBinaryFileHeader<Rev0>::print(std::ostream& cout) const {
        cout << "|------------------|" << endl;
        cout << "|BINARY FILE HEADER|" << endl;
        cout << "|------------------|" << endl;
        cout << endl;
        cout << "**** REV-0 FIELDS ****" << endl;
        cout << endl;
        cout << "Job identification number:                         " << (*this)[ field( rev0::bfh::jobID ) ] << endl;
        cout << "Line number:                                       " << (*this)[ field( rev0::bfh::lineNumber ) ] << endl;
        cout << "Reel number:                                       " << (*this)[ field( rev0::bfh::reelNumber ) ] << endl;
        cout << "Number of data traces per ensemble:                " << (*this)[ field( rev0::bfh::nDataTraces ) ] << endl;
        cout << "Number of auxiliary traces per ensemble:           " << (*this)[ field( rev0::bfh::nAuxiliaryTraces ) ] << endl;
        cout << "Sample interval (us):                              " << (*this)[ field( rev0::bfh::sampleInterval ) ] << endl;
        cout << "Sample interval (us) of original field recording:  " << (*this)[ field( rev0::bfh::sampleIntervalOriginalField  ) ] << endl;
        cout << "Number of samples per data trace:                  " << (*this)[ field( rev0::bfh::nsamplesDataTrace  ) ] << endl;
        cout << "Number of samples per data trace (original field): " << (*this)[ field( rev0::bfh::nsamplesDataTraceOriginalField  ) ] << endl;
        cout << "Data sample format code:                           " << (*this)[ field( rev0::bfh::formatCode  ) ] << endl;
        cout << "Ensemble fold:                                     " << (*this)[ field( rev0::bfh::ensembleFold  ) ] << endl;
        cout << "Trace sorting code:                                " << (*this)[ field( rev0::bfh::traceSortingCode  ) ] << endl;
        cout << "Vertical sum code:                                 " << (*this)[ field( rev0::bfh::verticalSumCode  ) ] << endl;
        cout << "Sweep frequency (Hz) at start:                     " << (*this)[ field( rev0::bfh::sweepFrequencyStart  ) ] << endl;
        cout << "Sweep frequency (Hz) at end:                       " << (*this)[ field( rev0::bfh::sweepFrequencyEnd  ) ] << endl;
        cout << "Sweep length (ms):                                 " << (*this)[ field( rev0::bfh::sweepLength  ) ] << endl;
        cout << "Sweep type                                         " << (*this)[ field( rev0::bfh::sweepTypeID  ) ] << endl;
        cout << "Trace number of sweep channel:                     " << (*this)[ field( rev0::bfh::traceNumberSweepChannel  ) ] << endl;
        cout << "Sweep trace taper length (ms) at start:            " << (*this)[ field( rev0::bfh::sweepTraceTaperLengthStart  ) ] << endl;        
        cout << "Sweep trace taper length (ms) at end:              " << (*this)[ field( rev0::bfh::sweepTraceTaperLengthEnd  ) ] << endl;
        cout << "Taper type:                                        " << (*this)[ field( rev0::bfh::taperType  ) ] << endl;
        cout << "Correlated data traces:                            " << (*this)[ field( rev0::bfh::correlatedDataTraces  ) ] << endl;
        cout << "Binary gain recovered:                             " << (*this)[ field( rev0::bfh::binaryGainRecovered  ) ] << endl;
        cout << "Amplitude recovery method:                         " << (*this)[ field( rev0::bfh::amplitudeRecoveryMethod  ) ] << endl;
        cout << "Measurement system:                                " << (*this)[ field( rev0::bfh::measurementSystem  ) ] << endl;
        cout << "Impulse signal polarity:                           " << (*this)[ field( rev0::bfh::impulseSignalPolarity  ) ] << endl;
        cout << "Vibratory polarity code:                           " << (*this)[ field( rev0::bfh::vibratoryPolarityCode  ) ] << endl;
        cout << endl;        
    }    
    
    namespace {

        /// @todo TO BE SUBSTITUTED WITH LAMBDAS AS SOON AS C++11 WILL BE ALLOWED 
        
        /**
         * @brief Functor that given a field of a binary header file, swaps its byte order
         */
        class BfhSwapByteOrder {
        public:

            BfhSwapByteOrder(ConcreteBinaryFileHeader<Rev0>& bfh) : bfh_(bfh) {
            }

            void operator()(rev0::bfh::Int16FieldsRev0 idx) {
                invertByteOrder(bfh_[ field(idx ) ]);
            }

            void operator()(rev0::bfh::Int32FieldsRev0 idx) {
                invertByteOrder(bfh_[ field(idx ) ]);
            }

        private:
            ConcreteBinaryFileHeader<Rev0>& bfh_;
        } ;

    }
    
    void ConcreteBinaryFileHeader<Rev0>::invertByteOrder() {
        BfhSwapByteOrder swapVisitor( *this );
        std::for_each(ConcreteBinaryFileHeader<Rev0>::Int32List.begin(), ConcreteBinaryFileHeader<Rev0>::Int32List.end(), swapVisitor);
        std::for_each(ConcreteBinaryFileHeader<Rev0>::Int16List.begin(), ConcreteBinaryFileHeader<Rev0>::Int16List.end(), swapVisitor);
    }
    
    void ConcreteBinaryFileHeader<Rev0>::checkConsistencyOrThrow() const {
        stringstream estream;
        bool         checkFailed = false;
        // Number of data traces per ensemble
        if ( (*this)[ field(rev0::bfh::nDataTraces) ] < 0 ) {
            checkFailed = true;
            estream << "Number of data traces per ensemble is < 0" << endl;
        }
        // Number of auxiliary traces per ensemble
        if ( (*this)[ field(rev0::bfh::nAuxiliaryTraces) ] < 0 ) {
            checkFailed = true;
            estream << "Number of auxiliary traces per ensemble is < 0" << endl;
        }
        // Sample interval in microseconds
        if ( (*this)[ field(rev0::bfh::sampleInterval) ] < 0 ) {
            checkFailed = true;
            estream << "Sample interval is < 0" << endl;
        }
        // Number of samples per data trace
        if ( (*this)[ field(rev0::bfh::nsamplesDataTrace) ] <= 0 ) {
            checkFailed = true;
            estream << "Number of samples per data trace is <= 0" << endl;
        }
        // Data sample format code
        switch ( (*this)[ field(rev0::bfh::formatCode) ] ) {
            case ( constants::SegyFileFormatCode::IBMfloat32 ):
            case ( constants::SegyFileFormatCode::Int32      ):
            case ( constants::SegyFileFormatCode::Fixed32    ):
            case ( constants::SegyFileFormatCode::IEEEfloat32):
            case ( constants::SegyFileFormatCode::Int16      ):
            case ( constants::SegyFileFormatCode::Int8       ):
                break;
            default:
                checkFailed = true;
                estream << "Invalid value of data sample format code (" << (*this)[ field(rev0::bfh::formatCode) ] << ")" << endl;
                break;
        }
        // Throw an exception if some consistency check failed
        if ( checkFailed ) {
            throw runtime_error( estream.str() );
        }
    }
    
    const bool ConcreteBinaryFileHeader<Rev0>::isRegistered(
            BinaryFileHeader::factory_type::getFactory()->registerType( "Rev0", new ConcreteBinaryFileHeader<Rev0> )            
            );
    
    
    
}
