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
#include<impl/rev0/SegyFile-Fields-Rev0.h>

namespace seismic {
    namespace rev0 {
        // Binary file header
        namespace bfh {
            // Fields that are mapped to int32_t
            const Int32Field jobID(0);
            const Int32Field lineNumber(4);
            const Int32Field reelNumber(8);
            // Fields that are mapped to int16_t            
            const Int16Field nDataTraces(12);
            const Int16Field nAuxiliaryTraces(14);
            const Int16Field sampleInterval(16);
            const Int16Field sampleIntervalOriginalField(18);
            const Int16Field nsamplesDataTrace(20);
            const Int16Field nsamplesDataTraceOriginalField(22);
            const Int16Field formatCode(24);
            const Int16Field ensembleFold(26);
            const Int16Field traceSortingCode(28);
            const Int16Field verticalSumCode(30);
            const Int16Field sweepFrequencyStart(32);
            const Int16Field sweepFrequencyEnd(34);
            const Int16Field sweepLength(36);
            const Int16Field sweepTypeID(38);
            const Int16Field traceNumberSweepChannel(40);
            const Int16Field sweepTraceTaperLengthStart(42);
            const Int16Field sweepTraceTaperLengthEnd(44);
            const Int16Field taperType(46);
            const Int16Field correlatedDataTraces(48);
            const Int16Field binaryGainRecovered(50);
            const Int16Field amplitudeRecoveryMethod(52);
            const Int16Field measurementSystem(54);
            const Int16Field impulseSignalPolarity(56);
            const Int16Field vibratoryPolarityCode(58);
        }
        // Trace header
        namespace th {
            // Fields that are mapped to int32_t
            const Int32Field traceSequenceNumberWithinLine (0);
            const Int32Field traceSequenceNumberWithinSEGY(4);
            const Int32Field originalFieldRecordNumber(8);
            const Int32Field traceNumberWithinOriginalField(12);
            const Int32Field energySourcePointNumber(16);
            const Int32Field ensembleNumber(20);
            const Int32Field traceNumberWithinEnsemble(24);
            const Int32Field distanceFromCenterSourceToCenterReceiver(36);
            const Int32Field receiverGroupElevation(40);
            const Int32Field surfaceElevationAtSource(44);
            const Int32Field sourceDepthBelowSurface(48);
            const Int32Field datumElevationAtReceiverGroup(52);
            const Int32Field datumElevationAtSource(56);
            const Int32Field waterDepthAtSource(60);
            const Int32Field waterDepthAtGroup(64);
            const Int32Field sourceCoordinateX(72);
            const Int32Field sourceCoordinateY(76);
            const Int32Field groupCoordinateX(80);
            const Int32Field groupCoordinateY(84);
            // Fields mapped to int16_t
            const Int16Field traceIdentificationCode(28);
            const Int16Field numberOfVerticallySummedTraces(30);
            const Int16Field numberOfHorizontallyStackedTraces(32);
            const Int16Field dataUse(34);
            const Int16Field scalarElevation(68);
            const Int16Field scalarCoordinates(70);
            const Int16Field coordinateUnits(88);
            const Int16Field weatheringVelocity(90);
            const Int16Field subweatheringVelocity(92);
            const Int16Field upholeTimeAtSource(94);
            const Int16Field upholeTimeAtGroup(96);
            const Int16Field sourceStaticCorrection(98);
            const Int16Field groupStaticCorrection(100);
            const Int16Field totalStaticApplied(102);
            const Int16Field lagTimeA(104);
            const Int16Field lagTimeB(106);
            const Int16Field delayRecordingTime(108);
            const Int16Field muteTimeStart(110);
            const Int16Field muteTimeEnd(112);
            const Int16Field nsamplesTrace(114);
            const Int16Field sampleInterval(116);
            const Int16Field gainType(118);
            const Int16Field instrumentGainConstant(120);
            const Int16Field instrumentEarlyGain(122);
            const Int16Field correlated(124);
            const Int16Field sweepFrequencyStart(126);
            const Int16Field sweepFrequencyEnd(128);
            const Int16Field sweepLength(130);
            const Int16Field sweepType(132);
            const Int16Field sweepTraceTaperLengthStart(134);
            const Int16Field sweepTraceTaperLengthEnd(136);
            const Int16Field taperType(138);
            const Int16Field aliasFilterFrequency(140);
            const Int16Field aliasFilterSlope(142);
            const Int16Field notchFilterFrequency(144);
            const Int16Field notchFilterSlope(146);
            const Int16Field lowCutFrequency(148);
            const Int16Field highCutFrequency(150);
            const Int16Field lowCutSlope(152);
            const Int16Field highCutSlope(154);
            const Int16Field yearDataRecorded(156);
            const Int16Field dayOfTheYear(158);
            const Int16Field hourOfDay(160);
            const Int16Field minuteOfHour(162);
            const Int16Field secondOfMinute(164);
            const Int16Field timeBasisCode(166);
            const Int16Field traceWeightingFactor(168);
            const Int16Field geophoneGroupNumberOfRollSwitch(170);
            const Int16Field geophoneGroupNumberOfTraceNumber(172);
            const Int16Field geophoneGroupNumberOfLastTrace(174);
            const Int16Field gapSize(176);
            const Int16Field overTravel(178);
        }
    }
}
