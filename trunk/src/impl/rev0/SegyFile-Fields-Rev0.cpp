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
    const Int32Field rev0::th::traceSequenceNumberWithinLine = 0;
    const Int32Field rev0::th::traceSequenceNumberWithinSEGY = 4;
    const Int32Field rev0::th::originalFieldRecordNumber = 8;
    const Int32Field rev0::th::traceNumberWithinOriginalField = 12;
    const Int32Field rev0::th::energySourcePointNumber = 16;
    const Int32Field rev0::th::ensembleNumber = 20;
    const Int32Field rev0::th::traceNumberWithinEnsemble = 24;
    const Int32Field rev0::th::distanceFromCenterSourceToCenterReceiver = 36;
    const Int32Field rev0::th::receiverGroupElevation = 40;
    const Int32Field rev0::th::surfaceElevationAtSource = 44;
    const Int32Field rev0::th::sourceDepthBelowSurface = 48;
    const Int32Field rev0::th::datumElevationAtReceiverGroup = 52;
    const Int32Field rev0::th::datumElevationAtSource = 56;
    const Int32Field rev0::th::waterDepthAtSource = 60;
    const Int32Field rev0::th::waterDepthAtGroup = 64;
    const Int32Field rev0::th::sourceCoordinateX = 72;
    const Int32Field rev0::th::sourceCoordinateY = 76;
    const Int32Field rev0::th::groupCoordinateX = 80;
    const Int32Field rev0::th::groupCoordinateY = 84; 
}

