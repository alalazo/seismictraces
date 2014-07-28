#include "segycolormap.h"
#include "ui_segycolormap.h"

#include <SegyFile.h>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_color_map.h>
#include <qwt_raster_data.h>
#include <qwt_scale_widget.h>

#include <algorithm>
#include <limits>
#include <vector>
#include <cstdint>

namespace {

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
    const seismic::Trace<T>& trace(size_t traceIdx) const {
        updateBuffer(traceIdx);
        return m_buffer.at(traceIdx - m_minimum_idx);
    }

    /**
     * @brief Returns the value of a sample for a given trace
     *
     * @param[in] traceIdx trace index
     * @param[in] sampleIdx sample index
     * @return reference to the value
     */
    seismic::Trace<T>& trace(size_t traceIdx) {
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
    mutable std::vector< seismic::Trace<T> > m_buffer;

    /// Maximum size that can be held in byte
    size_t m_max_size_in_byte = 1024 * 1024 * 1024;
    /// Number of traces per interval
    size_t m_step = 0;
    /// Current minimum index
    mutable size_t m_minimum_idx = 0;
    /// One past the maximum index
    mutable size_t m_maximum_idx = 0;
};

template<class T>
class SegyTraceData: public QwtRasterData
{
public:
    SegyTraceData(std::shared_ptr<seismic::SegyFile> file) :m_file(file)
    {
        using namespace seismic;

        auto buffer = TraceBuffer<T>::get();
        buffer->setCurrentFile(m_file);
        size_t max_nsamples = 0;
        T min_value = std::numeric_limits<T>::max();
        T max_value = std::numeric_limits<T>::lowest();
        for( size_t ii = 0; ii < m_file->ntraces(); ++ii) {
            //m_traces.push_back( std::move(file->readTraceAs<T>(ii) ) );
            auto current_trace = buffer->trace(ii);
            max_nsamples = std::max(max_nsamples,current_trace.size());
            auto minmax_value = std::minmax_element(current_trace.begin(),current_trace.end());
            min_value = std::min(min_value,*minmax_value.first);
            max_value = std::max(max_value,*minmax_value.second);
        }
        setInterval( Qt::XAxis, QwtInterval( 0, max_nsamples-1 ) );
        setInterval( Qt::YAxis, QwtInterval( 0, m_file->ntraces()-1 ) );
        setInterval( Qt::ZAxis, QwtInterval( min_value, max_value ) );
    }

    virtual double value( double x, double y ) const
    {
        auto buffer = TraceBuffer<T>::get();
        buffer->setCurrentFile(m_file);
        return buffer->trace(y)[x];
    }
private:
    std::shared_ptr<seismic::SegyFile> m_file;
    //std::vector< seismic::Trace<T> > m_traces;
    //TraceBuffer<T> m_buffer;
};

/**
 * @brief Poor man's factory to return the correct raster data type
 * @param[in] file handle to the SEG-Y file
 * @return raster data
 */
QwtRasterData * createSegyTraceData(std::shared_ptr<seismic::SegyFile> file) {
    using namespace seismic;

    auto& bfh = file->getBinaryFileHeader();
    auto format = bfh[rev0::bfh::formatCode];
    switch( format ) {
    case (constants::SegyFileFormatCode::IBMfloat32):
    case (constants::SegyFileFormatCode::IEEEfloat32):
    {
        return new SegyTraceData<float>(file);
    }
    case (constants::SegyFileFormatCode::Int32):
    {
        return new SegyTraceData<int32_t>(file);
    }
    case (constants::SegyFileFormatCode::Int16):
    {
        return new SegyTraceData<int16_t>(file);
    }
    case (constants::SegyFileFormatCode::Int8):
    {
        return new SegyTraceData<int8_t>(file);
    }
    default:
        break;
    }
    return nullptr;
}

QwtPlotCurve * createTracePlot(std::shared_ptr<seismic::SegyFile> file, size_t ii) {
    using namespace seismic;

    QVector<double> x;
    QVector<double> y;

    auto& bfh = file->getBinaryFileHeader();
    auto format = bfh[rev0::bfh::formatCode];
    switch( format ) {
    case (constants::SegyFileFormatCode::IBMfloat32):
    case (constants::SegyFileFormatCode::IEEEfloat32):
    {
        auto buffer = TraceBuffer<float>::get();
        auto ctrace = buffer->trace(ii);
        for(size_t ii = 0; ii < ctrace.size(); ++ii) {
            x.push_back(ii);
            y.push_back(ctrace[ii]);
        }
    }
    case (constants::SegyFileFormatCode::Int32):
    {

    }
    case (constants::SegyFileFormatCode::Int16):
    {

    }
    case (constants::SegyFileFormatCode::Int8):
    {

    }
    default:
        break;
    }

    auto plot = new QwtPlotCurve;
    plot->setSamples(x,y);
    return plot;
}

}
SegyColormap::SegyColormap(std::shared_ptr<seismic::SegyFile> file, QWidget *parent) :
    QWidget(parent), m_ui(new Ui::SegyColormap), m_file(file)
{
    m_ui->setupUi(this);

    //////////
    // Spectrogram
    auto spectrogram = new QwtPlotSpectrogram();
    spectrogram->setData( createSegyTraceData(m_file) );
    // Set colormap
    auto zinterval = spectrogram->interval(Qt::ZAxis);
    auto spectrogram_colormap = new QwtLinearColorMap(Qt::darkBlue,Qt::red);
    auto factor = zinterval.maxValue() - zinterval.minValue();
    auto zero_in_colormap = (std::max(zinterval.minValue(),0.0)-zinterval.minValue())/factor;
    spectrogram_colormap->addColorStop( zero_in_colormap*0.5,Qt::cyan);
    spectrogram_colormap->addColorStop( zero_in_colormap ,Qt::gray);
    spectrogram_colormap->addColorStop( (1 + zero_in_colormap)*0.5,Qt::yellow);
    spectrogram->setColorMap( spectrogram_colormap );
    // Set titles on the plot
    m_ui->colormap->setTitle("Amplitude Colormap");
    m_ui->colormap->setAxisTitle( QwtPlot::yLeft  ,"trace #");
    m_ui->colormap->setAxisTitle( QwtPlot::xBottom,"sample #");
    // Colormap on the right
    m_ui->colormap->enableAxis( QwtPlot::yRight );
    m_ui->colormap->setAxisTitle( QwtPlot::yRight, "Amplitude");
    auto axisWidget = m_ui->colormap->axisWidget(QwtPlot::yRight);
    axisWidget->setColorBarEnabled( true );
    auto interval = spectrogram->data()->interval( Qt::ZAxis );
    axisWidget->setColorMap( interval, spectrogram_colormap );
    m_ui->colormap->setAxisScale(QwtPlot::yRight, interval.minValue(), interval.maxValue());
    // Attach spectogram
    spectrogram->attach(m_ui->colormap);
    //////////

    //////////
    // Trace plot
    auto trace_plot = createTracePlot(m_file,0);
    // Set title
    m_ui->tracePlot->setTitle("Trace Plot");
    m_ui->tracePlot->setAxisTitle(QwtPlot::xBottom,"time");
    m_ui->tracePlot->setAxisTitle(QwtPlot::yLeft,"amplitude");
    trace_plot->attach(m_ui->tracePlot);
    m_ui->traceIdxSpinBox->setMaximum(m_file->ntraces());
    //////////
}

void SegyColormap::on_traceIdxSpinBox_valueChanged(int value) {
    auto trace_plot = createTracePlot(m_file,value);
    trace_plot->attach(m_ui->tracePlot);
}
