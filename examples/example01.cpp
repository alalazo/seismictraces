#include<SeismicTrace-inl.h>

using namespace seismic;

int main() {
        
    SeismicTrace trace;
    
    //
    // Set the coordinates of the receiver
    //
    trace(SeismicTrace::X) = 0.1f;
    trace(SeismicTrace::Y) = 0.2f;
    trace(SeismicTrace::Z) = 0.3f;
    
    //
    // Set the coordinates of the shot
    //
    trace.shot(SeismicTrace::X) = 10.1f;
    trace.shot(SeismicTrace::Y) = 20.1f;
    trace.shot(SeismicTrace::Z) = 30.1f;
    
    //
    // Set the time sampling interval
    //
    trace.dt() = 0.1f;
    
    //
    // Push back samples into the trace
    //
    for(int ii = 0; ii < 100; ii++) {
        trace.push_back(ii*2.5f);
    }
        
    return 0;
}
