#include<impl/SegyFile-BinaryFileHeader.h>

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
        
        vector<BinaryFileHeader::Int32Fields> initializeInt32List() {
            vector<BinaryFileHeader::Int32Fields> int32List;
            int32List.push_back( BinaryFileHeader::jobID      );
            int32List.push_back( BinaryFileHeader::lineNumber );
            int32List.push_back( BinaryFileHeader::reelNumber );
            return int32List;
        }
        
        vector<BinaryFileHeader::Int16Fields> initializeInt16List() {
            vector<BinaryFileHeader::Int16Fields> int16List;
	    int16List.push_back(BinaryFileHeader::nDataTraces                   );		   
	    int16List.push_back(BinaryFileHeader::nAuxiliaryTraces              );	   
	    int16List.push_back(BinaryFileHeader::sampleInterval                );		   
	    int16List.push_back(BinaryFileHeader::sampleIntervalOriginalField   );
	    int16List.push_back(BinaryFileHeader::nsamplesDataTrace             );	   
	    int16List.push_back(BinaryFileHeader::nsamplesDataTraceOriginalField);
	    int16List.push_back(BinaryFileHeader::formatCode                    );		   
	    int16List.push_back(BinaryFileHeader::ensembleFold                  );		   
	    int16List.push_back(BinaryFileHeader::traceSortingCode              );	   
	    int16List.push_back(BinaryFileHeader::verticalSumCode               );	   
	    int16List.push_back(BinaryFileHeader::sweepFrequencyStart           );	   
	    int16List.push_back(BinaryFileHeader::sweepFrequencyEnd             );	   
	    int16List.push_back(BinaryFileHeader::sweepLength                   );		   
	    int16List.push_back(BinaryFileHeader::sweepTypeID                   );		   
	    int16List.push_back(BinaryFileHeader::traceNumberSweepChannel       );   
	    int16List.push_back(BinaryFileHeader::sweepTraceTaperLengthStart    );
	    int16List.push_back(BinaryFileHeader::sweepTraceTaperLengthEnd      );  
	    int16List.push_back(BinaryFileHeader::taperType                     );		   
	    int16List.push_back(BinaryFileHeader::correlatedDataTraces          );	   
	    int16List.push_back(BinaryFileHeader::binaryGainRecovered           );	   
	    int16List.push_back(BinaryFileHeader::amplitudeRecoveryMethod       );   
	    int16List.push_back(BinaryFileHeader::measurementSystem             );	   
	    int16List.push_back(BinaryFileHeader::impulseSignalPolarity         );	   
	    int16List.push_back(BinaryFileHeader::vibratoryPolarityCode         );	   
	    int16List.push_back(BinaryFileHeader::segyFormatRevisionNumber      );  
	    int16List.push_back(BinaryFileHeader::fixedLengthTraceFlag          );	   
	    int16List.push_back(BinaryFileHeader::nextendedTextualFileHeader    );
            return int16List;
        }
    }
    ////////////////////
    // Static vectors
    ////////////////////
    const vector<BinaryFileHeader::Int32Fields> BinaryFileHeader::Int32List(initializeInt32List());
    const vector<BinaryFileHeader::Int16Fields> BinaryFileHeader::Int16List(initializeInt16List());
    
    ////////////////////
    // Related functions
    ////////////////////    
    ostream& operator<<(ostream& cout, const BinaryFileHeader& bfh){
        cout << "|------------------|" << endl;
        cout << "|BINARY FILE HEADER|" << endl;
        cout << "|------------------|" << endl;
        cout << endl;
        cout << "Job identification number:                         " << bfh[BinaryFileHeader::jobID] << endl;
        cout << "Line number:                                       " << bfh[BinaryFileHeader::lineNumber] << endl;
        cout << "Reel number:                                       " << bfh[BinaryFileHeader::reelNumber] << endl;
        cout << "Number of data traces per ensemble:                " << bfh[BinaryFileHeader::nDataTraces] << endl;
        cout << "Number of auxiliary traces per ensemble:           " << bfh[BinaryFileHeader::nAuxiliaryTraces] << endl;
        cout << "Sample interval (us):                              " << bfh[BinaryFileHeader::sampleInterval] << endl;
        cout << "Sample interval (us) of original field recording:  " << bfh[BinaryFileHeader::sampleIntervalOriginalField] << endl;
        cout << "Number of samples per data trace:                  " << bfh[BinaryFileHeader::nsamplesDataTrace] << endl;
        cout << "Number of samples per data trace (original field): " << bfh[BinaryFileHeader::nsamplesDataTraceOriginalField] << endl;
        cout << "Data sample format code:                           " << bfh[BinaryFileHeader::formatCode] << endl;
        cout << "Ensemble fold:                                     " << bfh[BinaryFileHeader::ensembleFold] << endl;
        cout << "Trace sorting code:                                " << bfh[BinaryFileHeader::traceSortingCode] << endl;
        cout << "Vertical sum code:                                 " << bfh[BinaryFileHeader::verticalSumCode] << endl;
        cout << "Sweep frequency (Hz) at start:                     " << bfh[BinaryFileHeader::sweepFrequencyStart] << endl;
        cout << "Sweep frequency (Hz) at end:                       " << bfh[BinaryFileHeader::sweepFrequencyEnd] << endl;
        cout << "Sweep length (ms):                                 " << bfh[BinaryFileHeader::sweepLength] << endl;
        cout << "Sweep type                                         " << bfh[BinaryFileHeader::sweepTypeID] << endl;
        cout << "Trace number of sweep channel:                     " << bfh[BinaryFileHeader::traceNumberSweepChannel] << endl;
        cout << "Sweep trace taper length (ms) at start:            " << bfh[BinaryFileHeader::sweepTraceTaperLengthStart] << endl;        
        cout << "Sweep trace taper length (ms) at end:              " << bfh[BinaryFileHeader::sweepTraceTaperLengthEnd] << endl;
        cout << "Taper type:                                        " << bfh[BinaryFileHeader::taperType] << endl;
        cout << "Correlated data traces:                            " << bfh[BinaryFileHeader::correlatedDataTraces] << endl;
        cout << "Binary gain recovered:                             " << bfh[BinaryFileHeader::binaryGainRecovered] << endl;
        cout << "Amplitude recovery method:                         " << bfh[BinaryFileHeader::amplitudeRecoveryMethod] << endl;
        cout << "Measurement system:                                " << bfh[BinaryFileHeader::measurementSystem] << endl;
        cout << "Impulse signal polarity:                           " << bfh[BinaryFileHeader::impulseSignalPolarity] << endl;
        cout << "Vibratory polarity code:                           " << bfh[BinaryFileHeader::vibratoryPolarityCode] << endl;
        cout << "SEGY format revision number:                       " << bfh[BinaryFileHeader::segyFormatRevisionNumber] << endl;
        cout << "Fixed length trace flag:                           " << bfh[BinaryFileHeader::fixedLengthTraceFlag] << endl;
        cout << "Number of Extended Textual File Headers:           " << bfh[BinaryFileHeader::nextendedTextualFileHeader] << endl;
        cout << endl;
        return cout;
    }    
}
