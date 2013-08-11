#include<impl/SegyFile-TraceHeader.h>

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

        vector<TraceHeader::Int32Fields> initializeInt32List() {
            vector<TraceHeader::Int32Fields> int32List;
            int32List.push_back( TraceHeader::traceSequenceNumberWithinLine            );
            int32List.push_back( TraceHeader::traceSequenceNumberWithinSEGY            );
            int32List.push_back( TraceHeader::originalFieldRecordNumber                );
            int32List.push_back( TraceHeader::traceNumberWithinOriginalField           );
            int32List.push_back( TraceHeader::energySourcePointNumber                  );
            int32List.push_back( TraceHeader::ensembleNumber                           );
            int32List.push_back( TraceHeader::traceNumberWithinEnsemble                );
            int32List.push_back( TraceHeader::distanceFromCenterSourceToCenterReceiver );
            int32List.push_back( TraceHeader::receiverGroupElevation                   );
            int32List.push_back( TraceHeader::surfaceElevationAtSource                 );
            int32List.push_back( TraceHeader::sourceDepthBelowSurface                  );
            int32List.push_back( TraceHeader::datumElevationAtReceiverGroup            );
            int32List.push_back( TraceHeader::datumElevationAtSource                   );
            int32List.push_back( TraceHeader::waterDepthAtSource                       );
            int32List.push_back( TraceHeader::waterDepthAtGroup                        );
            int32List.push_back( TraceHeader::sourceCoordinateX                        );
            int32List.push_back( TraceHeader::sourceCoordinateY                        );
            int32List.push_back( TraceHeader::groupCoordinateX                         );
            int32List.push_back( TraceHeader::groupCoordinateY                         );
            int32List.push_back( TraceHeader::ensembleCoordinateX                      );
            int32List.push_back( TraceHeader::ensembleCoordinateY                      );
            int32List.push_back( TraceHeader::inlineNumber                             );
            int32List.push_back( TraceHeader::crosslineNumber                          );
            int32List.push_back( TraceHeader::shotpointNumber                          );
            int32List.push_back( TraceHeader::transductionConstantMantissa             );
            int32List.push_back( TraceHeader::sourceMeasurementMantissa                );
            return int32List;
        }
        
        vector<TraceHeader::Int16Fields> initializeInt16List() {
            vector<TraceHeader::Int16Fields> int16List;
            int16List.push_back( TraceHeader::traceIdentificationCode           );
            int16List.push_back( TraceHeader::numberOfVerticallySummedTraces    );
            int16List.push_back( TraceHeader::numberOfHorizontallyStackedTraces );
            int16List.push_back( TraceHeader::dataUse                           );
            int16List.push_back( TraceHeader::scalarElevation                   );
            int16List.push_back( TraceHeader::scalarCoordinates                 );
            int16List.push_back( TraceHeader::coordinateUnits                   );
            int16List.push_back( TraceHeader::weatheringVelocity                );
            int16List.push_back( TraceHeader::subweatheringVelocity             );
            int16List.push_back( TraceHeader::upholeTimeAtSource                );
            int16List.push_back( TraceHeader::upholeTimeAtGroup                 );
            int16List.push_back( TraceHeader::sourceStaticCorrection            );
            int16List.push_back( TraceHeader::groupStaticCorrection             );
            int16List.push_back( TraceHeader::totalStaticApplied                );
            int16List.push_back( TraceHeader::lagTimeA                          );
            int16List.push_back( TraceHeader::lagTimeB                          );
            int16List.push_back( TraceHeader::delayRecordingTime                );
            int16List.push_back( TraceHeader::muteTimeStart                     );
            int16List.push_back( TraceHeader::muteTimeEnd                       );
            int16List.push_back( TraceHeader::nsamplesTrace                     );
            int16List.push_back( TraceHeader::sampleInterval                    );
            int16List.push_back( TraceHeader::gainType                          );
            int16List.push_back( TraceHeader::instrumentGainConstant            );
            int16List.push_back( TraceHeader::instrumentEarlyGain               );
            int16List.push_back( TraceHeader::correlated                        );
            int16List.push_back( TraceHeader::sweepFrequencyStart               );
            int16List.push_back( TraceHeader::sweepFrequencyEnd                 );
            int16List.push_back( TraceHeader::sweepLength                       );
            int16List.push_back( TraceHeader::sweepType                         );
            int16List.push_back( TraceHeader::sweepTraceTaperLengthStart        );
            int16List.push_back( TraceHeader::sweepTraceTaperLengthEnd          );
            int16List.push_back( TraceHeader::taperType                         );
            int16List.push_back( TraceHeader::aliasFilterFrequency              );
            int16List.push_back( TraceHeader::aliasFilterSlope                  );
            int16List.push_back( TraceHeader::notchFilterFrequency              );
            int16List.push_back( TraceHeader::notchFilterSlope                  );
            int16List.push_back( TraceHeader::lowCutFrequency                   );
            int16List.push_back( TraceHeader::highCutFrequency                  );
            int16List.push_back( TraceHeader::lowCutSlope                       );
            int16List.push_back( TraceHeader::highCutSlope                      );
            int16List.push_back( TraceHeader::yearDataRecorded                  );
            int16List.push_back( TraceHeader::dayOfTheYear                      );
            int16List.push_back( TraceHeader::hourOfDay                         );
            int16List.push_back( TraceHeader::minuteOfHour                      );
            int16List.push_back( TraceHeader::secondOfMinute                    );
            int16List.push_back( TraceHeader::timeBasisCode                     );
            int16List.push_back( TraceHeader::traceWeightingFactor              );
            int16List.push_back( TraceHeader::geophoneGroupNumberOfRollSwitch   );
            int16List.push_back( TraceHeader::geophoneGroupNumberOfTraceNumber  );
            int16List.push_back( TraceHeader::geophoneGroupNumberOfLastTrace    );
            int16List.push_back( TraceHeader::gapSize                           );
            int16List.push_back( TraceHeader::overTravel                        );
            int16List.push_back( TraceHeader::scalarShotpointNumber             );
            int16List.push_back( TraceHeader::traceValueMeasurementUnit         );
            int16List.push_back( TraceHeader::transductionConstantExponent      );
            int16List.push_back( TraceHeader::transductionUnits                 );
            int16List.push_back( TraceHeader::traceIdentifier                   );
            int16List.push_back( TraceHeader::scalarTime                        );
            int16List.push_back( TraceHeader::sourceOrientation                 );
            int16List.push_back( TraceHeader::sourceMeasurementExponent         );
            int16List.push_back( TraceHeader::sourceMeasurementUnit             );
            return int16List;
        }
        
    }
    ////////////////////
    // Static vectors
    ////////////////////
    const vector<TraceHeader::Int32Fields> TraceHeader::Int32List( initializeInt32List() );
    const vector<TraceHeader::Int16Fields> TraceHeader::Int16List( initializeInt16List() );

    ////////////////////
    // Related functions
    ////////////////////    
    ostream& operator<<(ostream& cout, const TraceHeader& th) {
        cout << "|------------|" << endl;
        cout << "|TRACE HEADER|" << endl;
        cout << "|------------|" << endl;
        cout << endl;
        cout << "Trace sequence number within line:                         " << th[TraceHeader::traceSequenceNumberWithinLine]     << endl;
        cout << "Trace sequence number within SEG Y file:                   " << th[TraceHeader::traceSequenceNumberWithinSEGY]     << endl;
        cout << "Original field record number:                              " << th[TraceHeader::originalFieldRecordNumber]         << endl;
        cout << "Trace number within the original field record:             " << th[TraceHeader::traceNumberWithinOriginalField]    << endl;
        cout << "Energy source point number:                                " << th[TraceHeader::energySourcePointNumber]           << endl;
        cout << "Ensemble number:                                           " << th[TraceHeader::ensembleNumber]                    << endl;
        cout << "Trace number within the ensemble:                          " << th[TraceHeader::traceNumberWithinEnsemble]         << endl;
        cout << "Trace identification code:                                 " << th[TraceHeader::traceIdentificationCode]           << endl;
        cout << "Number of vertically summed traces yielding this trace:    " << th[TraceHeader::numberOfVerticallySummedTraces]    << endl;
        cout << "Number of horizontally stacked traces yielding this trace: " << th[TraceHeader::numberOfHorizontallyStackedTraces] << endl;
        cout << "Data use:                                                  " << th[TraceHeader::dataUse]                           << endl;
        cout << "Distance from the source point to the receiver group:      " << th[TraceHeader::distanceFromCenterSourceToCenterReceiver] << endl;
        cout << "Receiver group elevation:                                  " << th[TraceHeader::receiverGroupElevation]            << endl;
        cout << "Surface elevation at source:                               " << th[TraceHeader::surfaceElevationAtSource]          << endl;
        cout << "Source depth below surface (a positive number):            " << th[TraceHeader::sourceDepthBelowSurface]           << endl;
        cout << "Datum elevation at receiver group:                         " << th[TraceHeader::datumElevationAtReceiverGroup]     << endl;
        cout << "Datum elevation at source:                                 " << th[TraceHeader::datumElevationAtSource]            << endl;
        cout << "Water depth at source:                                     " << th[TraceHeader::waterDepthAtSource]                << endl;
        cout << "Water depth at group:                                      " << th[TraceHeader::waterDepthAtGroup]                 << endl;
        cout << "Scalar to be applied to all elevations and depths:         " << th[TraceHeader::scalarElevation]                   << endl;
        cout << "Scalar to be applied to all coordinates:                   " << th[TraceHeader::scalarCoordinates]                 << endl;
        cout << "Source coordinate ‑ X:                                     " << th[TraceHeader::sourceCoordinateX]                 << endl;
        cout << "Source coordinate ‑ Y:                                     " << th[TraceHeader::sourceCoordinateY]                 << endl;
        cout << "Group coordinate ‑ X:                                      " << th[TraceHeader::groupCoordinateX]                  << endl;
        cout << "Group coordinate ‑ Y:                                      " << th[TraceHeader::groupCoordinateY]                  << endl;
        cout << "Coordinate units:                                          " << th[TraceHeader::coordinateUnits]                   << endl;
        cout << "Weathering velocity:                                       " << th[TraceHeader::weatheringVelocity]                << endl;
        cout << "Subweathering velocity:                                    " << th[TraceHeader::subweatheringVelocity]             << endl;
        cout << "Uphole time at source in milliseconds:                     " << th[TraceHeader::upholeTimeAtSource]                << endl;
        cout << "Uphole time at group in milliseconds:                      " << th[TraceHeader::upholeTimeAtGroup]                 << endl;
        cout << "Source static correction in milliseconds:                  " << th[TraceHeader::sourceStaticCorrection]            << endl;
        cout << "Group static correction in milliseconds:                   " << th[TraceHeader::groupStaticCorrection]             << endl;
        cout << "Total static applied in milliseconds:                      " << th[TraceHeader::totalStaticApplied]                << endl;
        cout << "Lag time A:                                                " << th[TraceHeader::lagTimeA]                          << endl;
        cout << "Lag time B:                                                " << th[TraceHeader::lagTimeB]                          << endl;
        cout << "Delay recording time:                                      " << th[TraceHeader::delayRecordingTime]                << endl;
        cout << "Mute time — Start time in milliseconds:                    " << th[TraceHeader::muteTimeStart]                     << endl;
        cout << "Mute time — End time in milliseconds:                      " << th[TraceHeader::muteTimeEnd]                       << endl;
        cout << "Number of samples in this trace:                           " << th[TraceHeader::nsamplesTrace]                     << endl;
        cout << "Sample interval in microseconds:                           " << th[TraceHeader::sampleInterval]                    << endl;
        cout << "Gain type of field instruments:                            " << th[TraceHeader::gainType]                          << endl;
        cout << "Instrument gain constant:                                  " << th[TraceHeader::instrumentGainConstant]            << endl;
        cout << "Instrument early or initial gain:                          " << th[TraceHeader::instrumentEarlyGain]               << endl;
        cout << "Correlated:                                                " << th[TraceHeader::correlated]                        << endl;
        cout << "Sweep frequency at start (Hz):                             " << th[TraceHeader::sweepFrequencyStart]               << endl;
        cout << "Sweep frequency at end (Hz):                               " << th[TraceHeader::sweepFrequencyEnd]                 << endl;
        cout << "Sweep length in milliseconds:                              " << th[TraceHeader::sweepLength]                       << endl;
        cout << "Sweep type:                                                " << th[TraceHeader::sweepType]                         << endl;
        cout << "Sweep trace taper length at start in milliseconds:         " << th[TraceHeader::sweepTraceTaperLengthStart]        << endl;
        cout << "Sweep trace taper length at end in milliseconds:           " << th[TraceHeader::sweepTraceTaperLengthEnd]          << endl;
        cout << "Taper type:                                                " << th[TraceHeader::taperType]                         << endl;
        cout << "Alias filter frequency (Hz), if used:                      " << th[TraceHeader::aliasFilterFrequency]              << endl;
        cout << "Alias filter slope (dB/octave):                            " << th[TraceHeader::aliasFilterSlope]                  << endl;
        cout << "Notch filter frequency (Hz), if used:                      " << th[TraceHeader::notchFilterFrequency]              << endl;
        cout << "Notch filter slope (dB/octave):                            " << th[TraceHeader::notchFilterSlope]                  << endl;
        cout << "Low-cut frequency (Hz), if used:                           " << th[TraceHeader::lowCutFrequency]                   << endl;
        cout << "High-cut frequency (Hz), if used:                          " << th[TraceHeader::highCutFrequency]                  << endl;
        cout << "Low-cut slope (dB/octave):                                 " << th[TraceHeader::lowCutSlope]                       << endl;
        cout << "High-cut slope (dB/octave):                                " << th[TraceHeader::highCutSlope]                      << endl;
        cout << "Year data recorded:                                        " << th[TraceHeader::yearDataRecorded]                  << endl;
        cout << "Day of year:                                               " << th[TraceHeader::dayOfTheYear]                      << endl;
        cout << "Hour of day (24 hour clock):                               " << th[TraceHeader::hourOfDay]                         << endl;
        cout << "Minute of hour:                                            " << th[TraceHeader::minuteOfHour]                      << endl;
        cout << "Second of minute:                                          " << th[TraceHeader::secondOfMinute]                    << endl;
        cout << "Time basis code:                                           " << th[TraceHeader::timeBasisCode]                     << endl;
        cout << "Trace weighting factor:                                    " << th[TraceHeader::traceWeightingFactor]              << endl;
        cout << "Geophone group number (roll switch position one):          " << th[TraceHeader::geophoneGroupNumberOfRollSwitch]   << endl;
        cout << "Geophone group number (trace 1 within original field):     " << th[TraceHeader::geophoneGroupNumberOfTraceNumber]  << endl;
        cout << "Geophone group number (last trace within original field):  " << th[TraceHeader::geophoneGroupNumberOfLastTrace]    << endl;
        cout << "Gap size (total number of groups dropped):                 " << th[TraceHeader::gapSize]                           << endl;
        cout << "Over travel associated with taper:                         " << th[TraceHeader::overTravel]                        << endl;
        cout << "X coordinate of ensemble:                                  " << th[TraceHeader::ensembleCoordinateX]               << endl;
        cout << "Y coordinate of ensemble:                                  " << th[TraceHeader::ensembleCoordinateY]               << endl;
        cout << "In-line number:                                            " << th[TraceHeader::inlineNumber]                      << endl;
        cout << "Cross-line number:                                         " << th[TraceHeader::crosslineNumber]                   << endl;
        cout << "Shotpoint number:                                          " << th[TraceHeader::shotpointNumber]                   << endl;
        cout << "Scalar to be applied to the shotpoint number:              " << th[TraceHeader::scalarShotpointNumber]             << endl;
        cout << "Trace value measurement unit:                              " << th[TraceHeader::traceValueMeasurementUnit]         << endl;
        cout << "Transduction Constant (mantissa):                          " << th[TraceHeader::transductionConstantMantissa]      << endl;
        cout << "Transduction Constant (exponent):                          " << th[TraceHeader::transductionConstantExponent]      << endl;
        cout << "Transduction Units:                                        " << th[TraceHeader::transductionUnits]                 << endl;
        cout << "Device/Trace Identifier:                                   " << th[TraceHeader::traceIdentifier]                   << endl;
        cout << "Scalar to be applied to times:                             " << th[TraceHeader::scalarTime]                        << endl;
        cout << "Source Type/Orientation:                                   " << th[TraceHeader::sourceOrientation]                 << endl;
        //cout << "Source Energy Direction with respect to the orientation:   " << th[TraceHeader::sour]                 << endl;
        cout << "Source Measurement (mantissa)                              " << th[TraceHeader::sourceMeasurementMantissa]         << endl;
        cout << "Source Measurement (exponent)                              " << th[TraceHeader::sourceMeasurementExponent]         << endl;
        cout << "Source Measurement Unit:                                   " << th[TraceHeader::sourceMeasurementUnit]             << endl;
        return cout;
    }
    
}
