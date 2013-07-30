#include<SeismicTrace-inl.h>

int main() {
        
    seismic::SeismicTrace trace;
    
    //
    // Set the coordinates of the receiver
    //
    trace(seismic::X) = 0.1f;
    trace(seismic::Y) = 0.2f;
    trace(seismic::Z) = 0.3f;
    
    //
    // Set the coordinates of the shot
    //
    trace.shot(seismic::X) = 10.1f;
    trace.shot(seismic::Y) = 20.1f;
    trace.shot(seismic::Z) = 30.1f;
    
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
