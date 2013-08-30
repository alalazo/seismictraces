#include<Conversion.h>
#include<impl/utilities-inl.h>

#include<algorithm>
#include<stdexcept>

using namespace std;

namespace seismic {
    
    void SegyConverter::operator ()(const SegyFile::trace_type& segyTrace, SeismicTrace& seismicTrace) {

        //////////        
        // Copy metadata information into the seismic trace
        //////////
        
        seismicTrace(SeismicTrace::X) = segyTrace.first[TraceHeader::groupCoordinateX];
        seismicTrace(SeismicTrace::Y) = segyTrace.first[TraceHeader::groupCoordinateY];
        seismicTrace(SeismicTrace::Z) = 0.0f;
        
        seismicTrace.shot(SeismicTrace::X) = segyTrace.first[TraceHeader::sourceCoordinateX];
        seismicTrace.shot(SeismicTrace::Y) = segyTrace.first[TraceHeader::sourceCoordinateY];
        seismicTrace.shot(SeismicTrace::Z) = 0.0f;
        
        seismicTrace.dt() = segyTrace.first[TraceHeader::sampleInterval];

        //////////
        // Read trace data
        //////////
        
        size_t nsamples   = segyTrace.first[TraceHeader::nsamplesTrace];        
        size_t sampleSize = constants::sizeOfDataSample(bfh_[BinaryFileHeader::formatCode]);
        
        seismicTrace.resize(nsamples,0.0f);                
        
        switch ( bfh_[BinaryFileHeader::formatCode] ) {
            case ( constants::SegyFileFormatCode::IBMfloat32 ) :
                // IBM floating point format
                for (size_t ii = 0; ii < nsamples; ii++) {
                    int32_t value = *( reinterpret_cast<const int32_t*> ( &segyTrace.second[ii * sampleSize ] ) );
                    ibm2ieee(value);
                    const float * pnt = reinterpret_cast<float*> ( &value );
                    seismicTrace[ii] = *pnt;
                }                
                break;
            case( constants::SegyFileFormatCode::IEEEfloat32 ) :
                for (size_t ii = 0; ii < nsamples; ii++) {
                    seismicTrace[ii] = *( reinterpret_cast<const float*> ( &segyTrace.second[ii * sampleSize ] ) );                    
                }                                  
                break;
            case( constants::SegyFileFormatCode::Int32 ) :
                for (size_t ii = 0; ii < nsamples; ii++) {
                    seismicTrace[ii] = *( reinterpret_cast<const int32_t*> ( &segyTrace.second[ii * sampleSize ] ) );                    
                }                                  
                break;
            case( constants::SegyFileFormatCode::Int16 ) :
                for (size_t ii = 0; ii < nsamples; ii++) {
                    seismicTrace[ii] = *( reinterpret_cast<const int16_t*> ( &segyTrace.second[ii * sampleSize ] ) );                    
                }                                  
                break;
            case( constants::SegyFileFormatCode::Int8  ) :
                for (size_t ii = 0; ii < nsamples; ii++) {
                    seismicTrace[ii] = *( reinterpret_cast<const int8_t*> ( &segyTrace.second[ii * sampleSize ] ) );                    
                }                                  
                break;
            case( constants::SegyFileFormatCode::Fixed32 ) :                
                throw std::runtime_error("Conversion to be implemented\n");
                break;
            default:
                throw std::runtime_error("Invalid \"Data sample format code\"\n");                    
                break;                
        }        
    }
      
    void SegyConverter::operator ()(const SeismicTrace& seismicTrace, SegyFile::trace_type& segyTrace) {
        //////////        
        // Copy metadata information into the trace header
        //////////
        
        segyTrace.first[TraceHeader::groupCoordinateX]  = seismicTrace(SeismicTrace::X);
        segyTrace.first[TraceHeader::groupCoordinateY]  = seismicTrace(SeismicTrace::Y);

        segyTrace.first[TraceHeader::sourceCoordinateX] = seismicTrace.shot(SeismicTrace::X);
        segyTrace.first[TraceHeader::sourceCoordinateY] = seismicTrace.shot(SeismicTrace::Y);
        
        segyTrace.first[TraceHeader::sampleInterval]    = seismicTrace.dt();
        segyTrace.first[TraceHeader::nsamplesTrace]     = seismicTrace.size();
        
        //////////
        // Read trace data
        //////////
        size_t nsamples   = segyTrace.first[TraceHeader::nsamplesTrace];        
        size_t sampleSize = constants::sizeOfDataSample(bfh_[BinaryFileHeader::formatCode]);
        
        // Resize buffer
        segyTrace.second.resize( nsamples*sampleSize );
        
        // Convert from float to format
        switch ( bfh_[BinaryFileHeader::formatCode] ) {
            case ( constants::SegyFileFormatCode::IBMfloat32 ) :
                // IBM floating point format
                for (size_t ii = 0; ii < nsamples; ii++) {
                    int32_t value = *( reinterpret_cast<const int32_t*> ( &seismicTrace[ii] ) );
                    ieee2ibm(value);
                    int32_t * pnt = reinterpret_cast<int32_t *> ( &segyTrace.second[ii*sampleSize] );
                    *pnt = value;
                }
                break;
            case( constants::SegyFileFormatCode::IEEEfloat32 ) :
                for (size_t ii = 0; ii < nsamples; ii++) {
                    float * pnt = reinterpret_cast<float *> ( &segyTrace.second[ii*sampleSize] );
                    *pnt = seismicTrace[ii];                    
                }                                  
                break;
            case( constants::SegyFileFormatCode::Int32 ) :
                for (size_t ii = 0; ii < nsamples; ii++) {
                    int32_t * pnt = reinterpret_cast<int32_t *> ( &segyTrace.second[ii*sampleSize] );
                    *pnt = seismicTrace[ii];                    
                }                                  
                break;
            case( constants::SegyFileFormatCode::Int16 ) :
                for (size_t ii = 0; ii < nsamples; ii++) {
                    int16_t * pnt = reinterpret_cast<int16_t *> ( &segyTrace.second[ii*sampleSize] );
                    *pnt = seismicTrace[ii];
                }                                  
                break;
            case( constants::SegyFileFormatCode::Int8  ) :
                for (size_t ii = 0; ii < nsamples; ii++) {
                    int8_t * pnt = reinterpret_cast<int8_t *> ( &segyTrace.second[ii*sampleSize] );
                    *pnt = seismicTrace[ii];                }                                  
                break;
            case( constants::SegyFileFormatCode::Fixed32 ) :                
                throw std::runtime_error("Conversion to be implemented\n");
                break;
            default:
                throw std::runtime_error("Invalid \"Data sample format code\"\n");                    
                break;                
        }                      
    }
    
}
