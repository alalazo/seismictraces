#include<SegyFile.h>

#include<iostream>

using namespace seismic;
using namespace std;

int main() {

    //
    // When a TextualFileHeader is constructed, its buffer table is initialized
    // to avoid the presence of garbage entries
    //
    TextualFileHeader tfh;
        
    // A single line in the text header file can be assigned from:
    
    //
    // 1. Raw literals
    // 
    tfh[0] = "This is a fake first line!";
    
    //
    // 2. C++ strings
    //
    string line("The best second line ever! :-)");
    tfh[1] = line;
    
    //
    // 3. Other Lines
    //
    tfh[2] = tfh[1];
    
    // Exceptions are thrown if for out of range accesses
    
    try {
      tfh[40] = "Assign out of range";
    } catch(exception& e) {
        cerr << e.what() << endl;
    }
    try {
      tfh[0][80] = '@';
    } catch(exception& e) {
        cerr << e.what() << endl;
    }
    
    //
    // A TextualFileHeader may be streamed 
    // 
    cout << tfh << endl;        
    
    return 0;
}

