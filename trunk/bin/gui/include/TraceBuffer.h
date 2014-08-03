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

/**
 * @file TraceBuffer.h
 * @brief Singleton buffer for traces in a SEG-Y file
 */

#ifndef TRACEBUFFER_H
#define TRACEBUFFER_H

#include <SegyFile.h>

#include <vector>

namespace seismic {

/**
 * @brief Buffer of traces implemented as a singleton
 *
 * @tparam T value type
 */
template<class T>
class TraceBuffer {
public:

    /**
     * @brief Gets the buffers
     *
     * @return pointer to the unique buffer
     */
    static TraceBuffer * get() {
        static std::shared_ptr<TraceBuffer> pnt(new TraceBuffer);
        return pnt.get();
    }

    /**
     * @brief Sets the current file under buffering
     *
     * @param[in] file file to be buffered
     */
    void setCurrentFile(std::shared_ptr<seismic::SegyFile> file) {
        auto& bfh = file->getBinaryFileHeader();
        auto nsamples = bfh[seismic::rev0::bfh::nsamplesDataTrace];
        m_step = m_max_size_in_byte / ( nsamples * sizeof(T) );
        m_file = file;
    }

    /**
     * @brief Returns an handle to the current file
     *
     * @return handle to the current file
     */
    std::shared_ptr<seismic::SegyFile> currentFile() const {
        return m_file;
    }

    /**
     * @brief Returns a reference to a given trace
     *
     * @param[in] traceIdx trace index
     *
     * @return reference to the value
     */
    const seismic::SegyFile::trace_type<T>& trace(size_t traceIdx) const {
        updateBuffer(traceIdx);
        return m_buffer[traceIdx - m_minimum_idx];
    }

    /**
     * @brief Returns the value of a sample for a given trace
     *
     * @param[in] traceIdx trace index
     * @param[in] sampleIdx sample index
     * @return reference to the value
     */
    seismic::SegyFile::trace_type<T>& trace(size_t traceIdx) {
        return const_cast< seismic::Trace<T>& >( static_cast<const TraceBuffer&>(*this).trace(traceIdx) );
    }

private:
    /**
     * @brief The class is implemented as a singleton (only one buffer per value_type)
     */
    TraceBuffer() {}

    void updateBuffer(size_t traceIdx) const {
        auto minimum_idx = traceIdx / m_step;
        minimum_idx *= m_step;
        auto maximum_idx = std::min(minimum_idx + m_step,m_file->ntraces());
        if( maximum_idx != m_maximum_idx || minimum_idx != m_minimum_idx ) {
            loadFromFile(minimum_idx,maximum_idx);
            m_minimum_idx = minimum_idx;
            m_maximum_idx = maximum_idx;
        }
    }

    void loadFromFile(size_t minimum_idx, size_t maximum_idx) const {
        m_buffer.clear();
        for(size_t ii = minimum_idx; ii < maximum_idx; ++ii) {
            m_buffer.push_back( std::move(m_file->readTraceAs<T>(ii)) );
        }
    }

    /// Handle to the currently buffered SEG-Y file
    std::shared_ptr<seismic::SegyFile> m_file;
    /// Buffer holdinga certain number of traces
    mutable std::vector< seismic::SegyFile::trace_type<T> > m_buffer;

    /// Maximum size that can be held in byte
    size_t m_max_size_in_byte = 1024 * 1024 * 1024;
    /// Number of traces per interval
    size_t m_step = 0;
    /// Current minimum index
    mutable size_t m_minimum_idx = 0;
    /// One past the maximum index
    mutable size_t m_maximum_idx = 0;
};

}

#endif // TRACEBUFFER_H
