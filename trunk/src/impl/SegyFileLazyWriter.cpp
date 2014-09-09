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

#include <impl/SegyFileLazyWriter.h>
#include <impl/SegyFileIndexer.h>

#include <iterator>
#include <sstream>

namespace seismic {

SegyFileLazyWriter::SegyFileLazyWriter(SegyFileIndexer& indexer, boost::filesystem::fstream& fileStream)
: indexer_(indexer), fileStream_(fileStream)
{
}

void SegyFileLazyWriter::addToOverwriteQueue(const SegyFile::raw_trace_type& trace, size_t n)
{
  overwriteMap_[n]=trace;
}

void SegyFileLazyWriter::commit(size_t sizeOfDataSample)
{
  using namespace std;
  // Commit overwrite modifications
  for (auto& x : overwriteMap_)
  {
    auto idx=x.first;
    auto trace=x.second;
    // Check consistency
    if (static_cast<size_t> (trace.first[rev0::th::nsamplesTrace]) != indexer_.nsamples(idx))
    {
      stringstream estream;
      estream << "Trying to overwrite a trace with different number of samples" << endl;
      estream << "\texpected number : " << indexer_.nsamples(idx) << endl;
      estream << "\tactually got    : " << static_cast<size_t> (trace.first[rev0::th::nsamplesTrace]) << endl;
      throw runtime_error(estream.str());
    }
    if (trace.second.size() != indexer_.nsamples(idx) * sizeOfDataSample)
    {
      stringstream estream;
      estream << "Unexpected length of trace data" << endl;
      estream << "\tnumber of samples : " << indexer_.nsamples(idx);
      estream << "\texpected length   : " << indexer_.nsamples(idx) * sizeOfDataSample << endl;
      estream << "\tactually got      : " << trace.second.size() << endl;
      throw runtime_error(estream.str());
    }
    // Overwrite trace
    fileStream_.seekp(indexer_.position(idx));
    write(fileStream_, trace.first);
    write(fileStream_, trace.second, trace.first[rev0::th::nsamplesTrace], sizeOfDataSample);
  }
  overwriteMap_.clear();
  // Commit append modifications
  fileStream_.seekp(0, ios::end);
  fileStream_.write(appendVector_.data(), appendVector_.size());
  appendVector_.clear();
  // Update index
  indexer_.updateIndex();
}

void SegyFileLazyWriter::addToAppendQueue(const SegyFile::raw_trace_type& trace, size_t sizeOfDataSample)
{
  using namespace std;
  // Declare a stream of byte
  stringstream byte_stream;
  // Write trace header
  write(byte_stream, trace.first);
  // Write trace data
  trace_data_type traceDataCopy(trace.second);
  write(byte_stream, traceDataCopy, trace.first[rev0::th::nsamplesTrace], sizeOfDataSample);
  // Append to internal buffer
  auto buffer=byte_stream.str();
  copy(buffer.begin(), buffer.end(), back_inserter(appendVector_));
}
}
