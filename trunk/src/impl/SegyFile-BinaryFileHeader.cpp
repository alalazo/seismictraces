#include<impl/SegyFile-BinaryFileHeader.h>

using namespace std;

namespace seismic {        
    
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
        cout << "Sample interval (us):                              " << bfh[BinaryFileHeader::nDataTraces] << endl;
        cout << "Sample interval (us) of original field recording:  " << bfh[BinaryFileHeader::nAuxiliaryTraces] << endl;
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
        cout << "Binary gain recovered:                             " << bfh[BinaryFileHeader::binaryGainRecovery] << endl;
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
