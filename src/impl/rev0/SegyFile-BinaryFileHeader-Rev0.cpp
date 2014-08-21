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
        
        vector<Int32Field> initializeInt32List() {
            vector<Int32Field> int32List;
            int32List.push_back( rev0::bfh::jobID      );
            int32List.push_back( rev0::bfh::lineNumber );
            int32List.push_back( rev0::bfh::reelNumber );
            return int32List;
        }
        
        vector<Int16Field> initializeInt16List() {
            vector<Int16Field> int16List;
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
    
    const vector<Int32Field>& ConcreteBinaryFileHeader<Rev0>::Int32List() {
        const static vector<Int32Field> list( initializeInt32List() );
        return list;
    }

    const vector<Int16Field>& ConcreteBinaryFileHeader<Rev0>::Int16List() {
        const static vector<Int16Field> list( initializeInt16List() );
        return list;
    }

    void ConcreteBinaryFileHeader<Rev0>::print(std::ostream& cout) const {
        cout << "|------------------|" << endl;
        cout << "|BINARY FILE HEADER|" << endl;
        cout << "|------------------|" << endl;
        cout << endl;
        cout << "**** REV-0 FIELDS ****" << endl;
        cout << endl;
        cout << "Job identification number:                         " << (*this)[ rev0::bfh::jobID ] << endl;
        cout << "Line number:                                       " << (*this)[ rev0::bfh::lineNumber ] << endl;
        cout << "Reel number:                                       " << (*this)[ rev0::bfh::reelNumber ] << endl;
        cout << "Number of data traces per ensemble:                " << (*this)[ rev0::bfh::nDataTraces ] << endl;
        cout << "Number of auxiliary traces per ensemble:           " << (*this)[ rev0::bfh::nAuxiliaryTraces ] << endl;
        cout << "Sample interval (us):                              " << (*this)[ rev0::bfh::sampleInterval ] << endl;
        cout << "Sample interval (us) of original field recording:  " << (*this)[ rev0::bfh::sampleIntervalOriginalField  ] << endl;
        cout << "Number of samples per data trace:                  " << (*this)[ rev0::bfh::nsamplesDataTrace  ] << endl;
        cout << "Number of samples per data trace (original field): " << (*this)[ rev0::bfh::nsamplesDataTraceOriginalField  ] << endl;
        cout << "Data sample format code:                           " << (*this)[ rev0::bfh::formatCode  ] << endl;
        cout << "Ensemble fold:                                     " << (*this)[ rev0::bfh::ensembleFold  ] << endl;
        cout << "Trace sorting code:                                " << (*this)[ rev0::bfh::traceSortingCode  ] << endl;
        cout << "Vertical sum code:                                 " << (*this)[ rev0::bfh::verticalSumCode  ] << endl;
        cout << "Sweep frequency (Hz) at start:                     " << (*this)[ rev0::bfh::sweepFrequencyStart  ] << endl;
        cout << "Sweep frequency (Hz) at end:                       " << (*this)[ rev0::bfh::sweepFrequencyEnd  ] << endl;
        cout << "Sweep length (ms):                                 " << (*this)[ rev0::bfh::sweepLength  ] << endl;
        cout << "Sweep type                                         " << (*this)[ rev0::bfh::sweepTypeID  ] << endl;
        cout << "Trace number of sweep channel:                     " << (*this)[ rev0::bfh::traceNumberSweepChannel  ] << endl;
        cout << "Sweep trace taper length (ms) at start:            " << (*this)[ rev0::bfh::sweepTraceTaperLengthStart  ] << endl;        
        cout << "Sweep trace taper length (ms) at end:              " << (*this)[ rev0::bfh::sweepTraceTaperLengthEnd  ] << endl;
        cout << "Taper type:                                        " << (*this)[ rev0::bfh::taperType  ] << endl;
        cout << "Correlated data traces:                            " << (*this)[ rev0::bfh::correlatedDataTraces  ] << endl;
        cout << "Binary gain recovered:                             " << (*this)[ rev0::bfh::binaryGainRecovered  ] << endl;
        cout << "Amplitude recovery method:                         " << (*this)[ rev0::bfh::amplitudeRecoveryMethod  ] << endl;
        cout << "Measurement system:                                " << (*this)[ rev0::bfh::measurementSystem  ] << endl;
        cout << "Impulse signal polarity:                           " << (*this)[ rev0::bfh::impulseSignalPolarity  ] << endl;
        cout << "Vibratory polarity code:                           " << (*this)[ rev0::bfh::vibratoryPolarityCode  ] << endl;
        cout << endl;        
    }    
    
    void ConcreteBinaryFileHeader<Rev0>::invertByteOrder() {
        // Invert 32 bit integer fields
        std::for_each(
                ConcreteBinaryFileHeader<Rev0>::Int32List().begin(),
                ConcreteBinaryFileHeader<Rev0>::Int32List().end(),
                [this](const Int32Field& idx){
                    seismic::invertByteOrder( (*this)[idx] );
                }
                );
        std::for_each(
                ConcreteBinaryFileHeader<Rev0>::Int16List().begin(),
                ConcreteBinaryFileHeader<Rev0>::Int16List().end(),
                [this](const Int16Field& idx){
                    seismic::invertByteOrder( (*this)[idx] );                    
                }                
                );
    }
    
    void ConcreteBinaryFileHeader<Rev0>::checkConsistencyOrThrow() const {
        stringstream estream;
        bool         checkFailed = false;
        // Number of data traces per ensemble
        if ( (*this)[rev0::bfh::nDataTraces] < 0 ) {
            checkFailed = true;
            estream << "Number of data traces per ensemble is < 0" << endl;
        }
        // Number of auxiliary traces per ensemble
        if ( (*this)[rev0::bfh::nAuxiliaryTraces] < 0 ) {
            checkFailed = true;
            estream << "Number of auxiliary traces per ensemble is < 0" << endl;
        }
        // Sample interval in microseconds
        if ( (*this)[rev0::bfh::sampleInterval] < 0 ) {
            checkFailed = true;
            estream << "Sample interval is < 0" << endl;
        }
        // Number of samples per data trace
        if ( (*this)[rev0::bfh::nsamplesDataTrace] <= 0 ) {
            checkFailed = true;
            estream << "Number of samples per data trace is <= 0" << endl;
        }
        // Data sample format code
        switch ( (*this)[rev0::bfh::formatCode] ) {
            case ( constants::SegyFileFormatCode::IBMfloat32 ):
            case ( constants::SegyFileFormatCode::Int32      ):
            case ( constants::SegyFileFormatCode::Fixed32    ):
            case ( constants::SegyFileFormatCode::IEEEfloat32):
            case ( constants::SegyFileFormatCode::Int16      ):
            case ( constants::SegyFileFormatCode::Int8       ):
                break;
            default:
                checkFailed = true;
                estream << "Invalid value of data sample format code (" << (*this)[rev0::bfh::formatCode] << ")" << endl;
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
