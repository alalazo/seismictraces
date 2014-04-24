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
#include<impl/rev0/SegyFile-TraceHeader-Rev0.h>
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
            int32List.push_back( rev0::th::traceSequenceNumberWithinLine            );
            int32List.push_back( rev0::th::traceSequenceNumberWithinSEGY            );
            int32List.push_back( rev0::th::originalFieldRecordNumber                );
            int32List.push_back( rev0::th::traceNumberWithinOriginalField           );
            int32List.push_back( rev0::th::energySourcePointNumber                  );
            int32List.push_back( rev0::th::ensembleNumber                           );
            int32List.push_back( rev0::th::traceNumberWithinEnsemble                );
            int32List.push_back( rev0::th::distanceFromCenterSourceToCenterReceiver );
            int32List.push_back( rev0::th::receiverGroupElevation                   );
            int32List.push_back( rev0::th::surfaceElevationAtSource                 );
            int32List.push_back( rev0::th::sourceDepthBelowSurface                  );
            int32List.push_back( rev0::th::datumElevationAtReceiverGroup            );
            int32List.push_back( rev0::th::datumElevationAtSource                   );
            int32List.push_back( rev0::th::waterDepthAtSource                       );
            int32List.push_back( rev0::th::waterDepthAtGroup                        );
            int32List.push_back( rev0::th::sourceCoordinateX                        );
            int32List.push_back( rev0::th::sourceCoordinateY                        );
            int32List.push_back( rev0::th::groupCoordinateX                         );
            int32List.push_back( rev0::th::groupCoordinateY                         );
            return int32List;
        }

        vector<Int16Field> initializeInt16List() {
            vector<Int16Field> int16List;
            int16List.push_back( rev0::th::traceIdentificationCode           );
            int16List.push_back( rev0::th::numberOfVerticallySummedTraces    );
            int16List.push_back( rev0::th::numberOfHorizontallyStackedTraces );
            int16List.push_back( rev0::th::dataUse                           );
            int16List.push_back( rev0::th::scalarElevation                   );
            int16List.push_back( rev0::th::scalarCoordinates                 );
            int16List.push_back( rev0::th::coordinateUnits                   );
            int16List.push_back( rev0::th::weatheringVelocity                );
            int16List.push_back( rev0::th::subweatheringVelocity             );
            int16List.push_back( rev0::th::upholeTimeAtSource                );
            int16List.push_back( rev0::th::upholeTimeAtGroup                 );
            int16List.push_back( rev0::th::sourceStaticCorrection            );
            int16List.push_back( rev0::th::groupStaticCorrection             );
            int16List.push_back( rev0::th::totalStaticApplied                );
            int16List.push_back( rev0::th::lagTimeA                          );
            int16List.push_back( rev0::th::lagTimeB                          );
            int16List.push_back( rev0::th::delayRecordingTime                );
            int16List.push_back( rev0::th::muteTimeStart                     );
            int16List.push_back( rev0::th::muteTimeEnd                       );
            int16List.push_back( rev0::th::nsamplesTrace                     );
            int16List.push_back( rev0::th::sampleInterval                    );
            int16List.push_back( rev0::th::gainType                          );
            int16List.push_back( rev0::th::instrumentGainConstant            );
            int16List.push_back( rev0::th::instrumentEarlyGain               );
            int16List.push_back( rev0::th::correlated                        );
            int16List.push_back( rev0::th::sweepFrequencyStart               );
            int16List.push_back( rev0::th::sweepFrequencyEnd                 );
            int16List.push_back( rev0::th::sweepLength                       );
            int16List.push_back( rev0::th::sweepType                         );
            int16List.push_back( rev0::th::sweepTraceTaperLengthStart        );
            int16List.push_back( rev0::th::sweepTraceTaperLengthEnd          );
            int16List.push_back( rev0::th::taperType                         );
            int16List.push_back( rev0::th::aliasFilterFrequency              );
            int16List.push_back( rev0::th::aliasFilterSlope                  );
            int16List.push_back( rev0::th::notchFilterFrequency              );
            int16List.push_back( rev0::th::notchFilterSlope                  );
            int16List.push_back( rev0::th::lowCutFrequency                   );
            int16List.push_back( rev0::th::highCutFrequency                  );
            int16List.push_back( rev0::th::lowCutSlope                       );
            int16List.push_back( rev0::th::highCutSlope                      );
            int16List.push_back( rev0::th::yearDataRecorded                  );
            int16List.push_back( rev0::th::dayOfTheYear                      );
            int16List.push_back( rev0::th::hourOfDay                         );
            int16List.push_back( rev0::th::minuteOfHour                      );
            int16List.push_back( rev0::th::secondOfMinute                    );
            int16List.push_back( rev0::th::timeBasisCode                     );
            int16List.push_back( rev0::th::traceWeightingFactor              );
            int16List.push_back( rev0::th::geophoneGroupNumberOfRollSwitch   );
            int16List.push_back( rev0::th::geophoneGroupNumberOfTraceNumber  );
            int16List.push_back( rev0::th::geophoneGroupNumberOfLastTrace    );
            int16List.push_back( rev0::th::gapSize                           );
            int16List.push_back( rev0::th::overTravel                        );
            return int16List;
        }
    }
    ////////////////////
    // Static vectors
    ////////////////////
    const vector<Int32Field> ConcreteTraceHeader<Rev0>::Int32List( initializeInt32List() );
    const vector<Int16Field> ConcreteTraceHeader<Rev0>::Int16List( initializeInt16List() );

    void ConcreteTraceHeader<Rev0>::print(std::ostream& cout) const {
        cout << "|------------|" << endl;
        cout << "|TRACE HEADER|" << endl;
        cout << "|------------|" << endl;
        cout << endl;
        cout << "**** REV-0 FIELDS ****" << endl;
        cout << endl;
        cout << "Trace sequence number within line:                         " << (*this)[ rev0::th::traceSequenceNumberWithinLine ]     << endl;
        cout << "Trace sequence number within SEG Y file:                   " << (*this)[ rev0::th::traceSequenceNumberWithinSEGY ]     << endl;
        cout << "Original field record number:                              " << (*this)[ rev0::th::originalFieldRecordNumber ]         << endl;
        cout << "Trace number within the original field record:             " << (*this)[ rev0::th::traceNumberWithinOriginalField ]    << endl;
        cout << "Energy source point number:                                " << (*this)[ rev0::th::energySourcePointNumber ]           << endl;
        cout << "Ensemble number:                                           " << (*this)[ rev0::th::ensembleNumber ]                    << endl;
        cout << "Trace number within the ensemble:                          " << (*this)[ rev0::th::traceNumberWithinEnsemble ]         << endl;
        cout << "Trace identification code:                                 " << (*this)[ rev0::th::traceIdentificationCode ]           << endl;
        cout << "Number of vertically summed traces yielding this trace:    " << (*this)[ rev0::th::numberOfVerticallySummedTraces ]    << endl;
        cout << "Number of horizontally stacked traces yielding this trace: " << (*this)[ rev0::th::numberOfHorizontallyStackedTraces ] << endl;
        cout << "Data use:                                                  " << (*this)[ rev0::th::dataUse ]                           << endl;
        cout << "Distance from the source point to the receiver group:      " << (*this)[ rev0::th::distanceFromCenterSourceToCenterReceiver] << endl;
        cout << "Receiver group elevation:                                  " << (*this)[ rev0::th::receiverGroupElevation ]            << endl;
        cout << "Surface elevation at source:                               " << (*this)[ rev0::th::surfaceElevationAtSource ]          << endl;
        cout << "Source depth below surface (a positive number):            " << (*this)[ rev0::th::sourceDepthBelowSurface ]           << endl;
        cout << "Datum elevation at receiver group:                         " << (*this)[ rev0::th::datumElevationAtReceiverGroup ]     << endl;
        cout << "Datum elevation at source:                                 " << (*this)[ rev0::th::datumElevationAtSource ]            << endl;
        cout << "Water depth at source:                                     " << (*this)[ rev0::th::waterDepthAtSource ]                << endl;
        cout << "Water depth at group:                                      " << (*this)[ rev0::th::waterDepthAtGroup ]                 << endl;
        cout << "Scalar to be applied to all elevations and depths:         " << (*this)[ rev0::th::scalarElevation ]                   << endl;
        cout << "Scalar to be applied to all coordinates:                   " << (*this)[ rev0::th::scalarCoordinates ]                 << endl;
        cout << "Source coordinate ‑ X:                                     " << (*this)[ rev0::th::sourceCoordinateX ]                 << endl;
        cout << "Source coordinate ‑ Y:                                     " << (*this)[ rev0::th::sourceCoordinateY ]                 << endl;
        cout << "Group coordinate ‑ X:                                      " << (*this)[ rev0::th::groupCoordinateX ]                  << endl;
        cout << "Group coordinate ‑ Y:                                      " << (*this)[ rev0::th::groupCoordinateY ]                  << endl;
        cout << "Coordinate units:                                          " << (*this)[ rev0::th::coordinateUnits ]                   << endl;
        cout << "Weathering velocity:                                       " << (*this)[ rev0::th::weatheringVelocity ]                << endl;
        cout << "Subweathering velocity:                                    " << (*this)[ rev0::th::subweatheringVelocity ]             << endl;
        cout << "Uphole time at source in milliseconds:                     " << (*this)[ rev0::th::upholeTimeAtSource ]                << endl;
        cout << "Uphole time at group in milliseconds:                      " << (*this)[ rev0::th::upholeTimeAtGroup ]                 << endl;
        cout << "Source static correction in milliseconds:                  " << (*this)[ rev0::th::sourceStaticCorrection ]            << endl;
        cout << "Group static correction in milliseconds:                   " << (*this)[ rev0::th::groupStaticCorrection ]             << endl;
        cout << "Total static applied in milliseconds:                      " << (*this)[ rev0::th::totalStaticApplied ]                << endl;
        cout << "Lag time A:                                                " << (*this)[ rev0::th::lagTimeA ]                          << endl;
        cout << "Lag time B:                                                " << (*this)[ rev0::th::lagTimeB ]                          << endl;
        cout << "Delay recording time:                                      " << (*this)[ rev0::th::delayRecordingTime ]                << endl;
        cout << "Mute time — Start time in milliseconds:                    " << (*this)[ rev0::th::muteTimeStart ]                     << endl;
        cout << "Mute time — End time in milliseconds:                      " << (*this)[ rev0::th::muteTimeEnd ]                       << endl;
        cout << "Number of samples in this trace:                           " << (*this)[ rev0::th::nsamplesTrace ]                     << endl;
        cout << "Sample interval in microseconds:                           " << (*this)[ rev0::th::sampleInterval ]                    << endl;
        cout << "Gain type of field instruments:                            " << (*this)[ rev0::th::gainType ]                          << endl;
        cout << "Instrument gain constant:                                  " << (*this)[ rev0::th::instrumentGainConstant ]            << endl;
        cout << "Instrument early or initial gain:                          " << (*this)[ rev0::th::instrumentEarlyGain ]               << endl;
        cout << "Correlated:                                                " << (*this)[ rev0::th::correlated ]                        << endl;
        cout << "Sweep frequency at start (Hz):                             " << (*this)[ rev0::th::sweepFrequencyStart ]               << endl;
        cout << "Sweep frequency at end (Hz):                               " << (*this)[ rev0::th::sweepFrequencyEnd ]                 << endl;
        cout << "Sweep length in milliseconds:                              " << (*this)[ rev0::th::sweepLength ]                       << endl;
        cout << "Sweep type:                                                " << (*this)[ rev0::th::sweepType ]                         << endl;
        cout << "Sweep trace taper length at start in milliseconds:         " << (*this)[ rev0::th::sweepTraceTaperLengthStart ]        << endl;
        cout << "Sweep trace taper length at end in milliseconds:           " << (*this)[ rev0::th::sweepTraceTaperLengthEnd ]          << endl;
        cout << "Taper type:                                                " << (*this)[ rev0::th::taperType ]                         << endl;
        cout << "Alias filter frequency (Hz), if used:                      " << (*this)[ rev0::th::aliasFilterFrequency ]              << endl;
        cout << "Alias filter slope (dB/octave):                            " << (*this)[ rev0::th::aliasFilterSlope ]                  << endl;
        cout << "Notch filter frequency (Hz), if used:                      " << (*this)[ rev0::th::notchFilterFrequency ]              << endl;
        cout << "Notch filter slope (dB/octave):                            " << (*this)[ rev0::th::notchFilterSlope ]                  << endl;
        cout << "Low-cut frequency (Hz), if used:                           " << (*this)[ rev0::th::lowCutFrequency ]                   << endl;
        cout << "High-cut frequency (Hz), if used:                          " << (*this)[ rev0::th::highCutFrequency ]                  << endl;
        cout << "Low-cut slope (dB/octave):                                 " << (*this)[ rev0::th::lowCutSlope ]                       << endl;
        cout << "High-cut slope (dB/octave):                                " << (*this)[ rev0::th::highCutSlope ]                      << endl;
        cout << "Year data recorded:                                        " << (*this)[ rev0::th::yearDataRecorded ]                  << endl;
        cout << "Day of year:                                               " << (*this)[ rev0::th::dayOfTheYear ]                      << endl;
        cout << "Hour of day (24 hour clock):                               " << (*this)[ rev0::th::hourOfDay ]                         << endl;
        cout << "Minute of hour:                                            " << (*this)[ rev0::th::minuteOfHour ]                      << endl;
        cout << "Second of minute:                                          " << (*this)[ rev0::th::secondOfMinute ]                    << endl;
        cout << "Time basis code:                                           " << (*this)[ rev0::th::timeBasisCode ]                     << endl;
        cout << "Trace weighting factor:                                    " << (*this)[ rev0::th::traceWeightingFactor ]              << endl;
        cout << "Geophone group number (roll switch position one):          " << (*this)[ rev0::th::geophoneGroupNumberOfRollSwitch ]   << endl;
        cout << "Geophone group number (trace 1 within original field):     " << (*this)[ rev0::th::geophoneGroupNumberOfTraceNumber ]  << endl;
        cout << "Geophone group number (last trace within original field):  " << (*this)[ rev0::th::geophoneGroupNumberOfLastTrace ]    << endl;
        cout << "Gap size (total number of groups dropped):                 " << (*this)[ rev0::th::gapSize ]                           << endl;
        cout << "Over travel associated with taper:                         " << (*this)[ rev0::th::overTravel ]                        << endl;
    }
    
    namespace {

        /// @todo TO BE SUBSTITUTED WITH LAMBDAS AS SOON AS C++11 WILL BE ALLOWED 
        
        /**
         * @brief Functor that given a field of a trace header file, swaps its byte order
         */
        class ThSwapByteOrder {
        public:

            ThSwapByteOrder(ConcreteTraceHeader<Rev0>& th) : th_(th) {
            }

            void operator()(Int16Field idx) {
                invertByteOrder(th_[idx]);
            }

            void operator()(Int32Field idx) {
                invertByteOrder(th_[idx]);
            }

        private:
            ConcreteTraceHeader<Rev0>& th_;
        } ;
        
    }

    void ConcreteTraceHeader<Rev0>::invertByteOrder() {
        ThSwapByteOrder swapVisitor( *this );
        std::for_each(ConcreteTraceHeader<Rev0>::Int32List.begin(), ConcreteTraceHeader<Rev0>::Int32List.end(), swapVisitor);
        std::for_each(ConcreteTraceHeader<Rev0>::Int16List.begin(), ConcreteTraceHeader<Rev0>::Int16List.end(), swapVisitor);
    }
    
    void ConcreteTraceHeader<Rev0>::checkConsistencyOrThrow() const {
        cout << "WARNING: ConcreteTraceHeader<Rev0> trace header consistency check still to be implemented" << endl;
    }
    
    const bool ConcreteTraceHeader<Rev0>::isRegistered(
            TraceHeaderInterface::factory_type::getFactory()->registerType("Rev0",new ConcreteTraceHeader<Rev0>)
            );
}
