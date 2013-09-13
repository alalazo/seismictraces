#include<impl/rev1/SegyFile-TraceHeader-Rev1.h>
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

        vector<rev1::th::Int32FieldsRev1> initializeInt32List() {
            vector<rev1::th::Int32FieldsRev1> int32List;
            int32List.push_back( rev1::th::ensembleCoordinateX                      );
            int32List.push_back( rev1::th::ensembleCoordinateY                      );
            int32List.push_back( rev1::th::inlineNumber                             );
            int32List.push_back( rev1::th::crosslineNumber                          );
            int32List.push_back( rev1::th::shotpointNumber                          );
            int32List.push_back( rev1::th::transductionConstantMantissa             );
            int32List.push_back( rev1::th::sourceMeasurementMantissa                );
            return int32List;
        }
        
        vector<rev1::th::Int16FieldsRev1> initializeInt16List() {
            vector<rev1::th::Int16FieldsRev1> int16List;
            int16List.push_back( rev1::th::scalarShotpointNumber             );
            int16List.push_back( rev1::th::traceValueMeasurementUnit         );
            int16List.push_back( rev1::th::transductionConstantExponent      );
            int16List.push_back( rev1::th::transductionUnits                 );
            int16List.push_back( rev1::th::traceIdentifier                   );
            int16List.push_back( rev1::th::scalarTime                        );
            int16List.push_back( rev1::th::sourceOrientation                 );
            int16List.push_back( rev1::th::sourceMeasurementExponent         );
            int16List.push_back( rev1::th::sourceMeasurementUnit             );
            return int16List;
        }
        
    }
    ////////////////////
    // Static vectors
    ////////////////////
    const vector<rev1::th::Int32FieldsRev1> ConcreteTraceHeader<Rev1>::Int32List( initializeInt32List() );
    const vector<rev1::th::Int16FieldsRev1> ConcreteTraceHeader<Rev1>::Int16List( initializeInt16List() );

    namespace {

        /// @todo TO BE SUBSTITUTED WITH LAMBDAS AS SOON AS C++11 WILL BE ALLOWED 
        
        /**
         * @brief Functor that given a field of a trace header file, swaps its byte order
         */
        class ThSwapByteOrder {
        public:

            ThSwapByteOrder(ConcreteTraceHeader<Rev1>& th) : th_(th) {
            }

            void operator()(rev1::th::Int16FieldsRev1 idx) {
                invertByteOrder(th_[field(idx)]);
            }

            void operator()(rev1::th::Int32FieldsRev1 idx) {
                invertByteOrder(th_[field(idx)]);
            }

        private:
            ConcreteTraceHeader<Rev1>& th_;
        } ;        
    }
    
    void ConcreteTraceHeader<Rev1>::print(std::ostream& cout) const {
        ConcreteTraceHeader<Rev0>::print(cout);
        cout << endl;
        cout << "**** REV-1 FIELDS ****" << endl;
        cout << endl;
        cout << "X coordinate of ensemble:                                  " << (*this)[ field(rev1::th::ensembleCoordinateX) ]               << endl;
        cout << "Y coordinate of ensemble:                                  " << (*this)[ field(rev1::th::ensembleCoordinateY) ]               << endl;
        cout << "In-line number:                                            " << (*this)[ field(rev1::th::inlineNumber) ]                      << endl;
        cout << "Cross-line number:                                         " << (*this)[ field(rev1::th::crosslineNumber) ]                   << endl;
        cout << "Shotpoint number:                                          " << (*this)[ field(rev1::th::shotpointNumber) ]                   << endl;
        cout << "Scalar to be applied to the shotpoint number:              " << (*this)[ field(rev1::th::scalarShotpointNumber) ]             << endl;
        cout << "Trace value measurement unit:                              " << (*this)[ field(rev1::th::traceValueMeasurementUnit) ]         << endl;
        cout << "Transduction Constant (mantissa):                          " << (*this)[ field(rev1::th::transductionConstantMantissa) ]      << endl;
        cout << "Transduction Constant (exponent):                          " << (*this)[ field(rev1::th::transductionConstantExponent) ]      << endl;
        cout << "Transduction Units:                                        " << (*this)[ field(rev1::th::transductionUnits) ]                 << endl;
        cout << "Device/Trace Identifier:                                   " << (*this)[ field(rev1::th::traceIdentifier) ]                   << endl;
        cout << "Scalar to be applied to times:                             " << (*this)[ field(rev1::th::scalarTime) ]                        << endl;
        cout << "Source Type/Orientation:                                   " << (*this)[ field(rev1::th::sourceOrientation) ]                 << endl;
        //cout << "Source Energy Direction with respect to the orientation:   " << (*this)[ field(sour) ]                 << endl;
        cout << "Source Measurement (mantissa)                              " << (*this)[ field(rev1::th::sourceMeasurementMantissa) ]         << endl;
        cout << "Source Measurement (exponent)                              " << (*this)[ field(rev1::th::sourceMeasurementExponent) ]         << endl;
        cout << "Source Measurement Unit:                                   " << (*this)[ field(rev1::th::sourceMeasurementUnit) ]             << endl;        
        cout << endl;        
    }
    
    
    void ConcreteTraceHeader<Rev1>::invertByteOrder() {
        ThSwapByteOrder swapVisitor( *this );
        ConcreteTraceHeader<Rev0>::invertByteOrder();
        std::for_each(ConcreteTraceHeader<Rev1>::Int32List.begin(), ConcreteTraceHeader<Rev1>::Int32List.end(), swapVisitor);
        std::for_each(ConcreteTraceHeader<Rev1>::Int16List.begin(), ConcreteTraceHeader<Rev1>::Int16List.end(), swapVisitor);
    }
    
    void ConcreteTraceHeader<Rev1>::checkConsistencyOrThrow() const {
        cout << "WARNING: ConcreteTraceHeader<Rev0> trace header consistency check still to be implemented" << endl;
    }
    
    const bool ConcreteTraceHeader<Rev1>::isRegistered(
            TraceHeaderInterface::factory_type::getFactory()->registerType("Rev1",new ConcreteTraceHeader<Rev1>)
            );
}
