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

        vector<Int32Field> initializeInt32List() {
            vector<Int32Field> int32List;
            int32List.push_back( rev1::th::ensembleCoordinateX                      );
            int32List.push_back( rev1::th::ensembleCoordinateY                      );
            int32List.push_back( rev1::th::inlineNumber                             );
            int32List.push_back( rev1::th::crosslineNumber                          );
            int32List.push_back( rev1::th::shotpointNumber                          );
            int32List.push_back( rev1::th::transductionConstantMantissa             );
            int32List.push_back( rev1::th::sourceMeasurementMantissa                );
            return int32List;
        }
        
        vector<Int16Field> initializeInt16List() {
            vector<Int16Field> int16List;
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

    const std::vector<Int16Field>& ConcreteTraceHeader<Rev1>::Int16List() {
        static const vector<Int16Field> list( initializeInt16List() );
        return list;
    }

    const std::vector<Int32Field>& ConcreteTraceHeader<Rev1>::Int32List() {
        static const vector<Int32Field> list( initializeInt32List() );
        return list;
    }
    
    void ConcreteTraceHeader<Rev1>::print(std::ostream& cout) const {
        ConcreteTraceHeader<Rev0>::print(cout);
        cout << endl;
        cout << "**** REV-1 FIELDS ****" << endl;
        cout << endl;
        cout << "X coordinate of ensemble:                                  " << (*this)[ rev1::th::ensembleCoordinateX ]               << endl;
        cout << "Y coordinate of ensemble:                                  " << (*this)[ rev1::th::ensembleCoordinateY ]               << endl;
        cout << "In-line number:                                            " << (*this)[ rev1::th::inlineNumber ]                      << endl;
        cout << "Cross-line number:                                         " << (*this)[ rev1::th::crosslineNumber ]                   << endl;
        cout << "Shotpoint number:                                          " << (*this)[ rev1::th::shotpointNumber ]                   << endl;
        cout << "Scalar to be applied to the shotpoint number:              " << (*this)[ rev1::th::scalarShotpointNumber ]             << endl;
        cout << "Trace value measurement unit:                              " << (*this)[ rev1::th::traceValueMeasurementUnit ]         << endl;
        cout << "Transduction Constant (mantissa):                          " << (*this)[ rev1::th::transductionConstantMantissa ]      << endl;
        cout << "Transduction Constant (exponent):                          " << (*this)[ rev1::th::transductionConstantExponent ]      << endl;
        cout << "Transduction Units:                                        " << (*this)[ rev1::th::transductionUnits ]                 << endl;
        cout << "Device/Trace Identifier:                                   " << (*this)[ rev1::th::traceIdentifier ]                   << endl;
        cout << "Scalar to be applied to times:                             " << (*this)[ rev1::th::scalarTime ]                        << endl;
        cout << "Source Type/Orientation:                                   " << (*this)[ rev1::th::sourceOrientation ]                 << endl;
        //cout << "Source Energy Direction with respect to the orientation:   " << (*this)[ field(sour ]                 << endl;
        cout << "Source Measurement (mantissa)                              " << (*this)[ rev1::th::sourceMeasurementMantissa ]         << endl;
        cout << "Source Measurement (exponent)                              " << (*this)[ rev1::th::sourceMeasurementExponent ]         << endl;
        cout << "Source Measurement Unit:                                   " << (*this)[ rev1::th::sourceMeasurementUnit ]             << endl;        
        cout << endl;        
    }
    
    
    void ConcreteTraceHeader<Rev1>::invertByteOrder() {
        ConcreteTraceHeader<Rev0>::invertByteOrder();
        std::for_each(
                ConcreteTraceHeader<Rev1>::Int32List().begin(),
                ConcreteTraceHeader<Rev1>::Int32List().end(),
                [this](const Int32Field & idx) {
                    seismic::invertByteOrder((*this)[idx]);
                }
        );
        std::for_each(
                ConcreteTraceHeader<Rev1>::Int16List().begin(),
                ConcreteTraceHeader<Rev1>::Int16List().end(),
                [this](const Int16Field & idx) {
                    seismic::invertByteOrder((*this)[idx]);
                });
    }
    
    void ConcreteTraceHeader<Rev1>::checkConsistencyOrThrow() const {
        cout << "WARNING: ConcreteTraceHeader<Rev0> trace header consistency check still to be implemented" << endl;
    }
    
    const bool ConcreteTraceHeader<Rev1>::isRegistered(
            TraceHeaderInterface::factory_type::getFactory()->registerType("Rev1",new ConcreteTraceHeader<Rev1>)
            );
}
