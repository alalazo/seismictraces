#include "segycolormap.h"
#include "ui_segycolormap.h"

#include <TraceBuffer.h>
#include <SegyFile.h>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_color_map.h>
#include <qwt_raster_data.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_engine.h>
#include <qwt_symbol.h>

#include <algorithm>
#include <limits>
#include <vector>
#include <cstdint>

using namespace seismic;

namespace {

template<class T>
class SegyTraceData: public QwtRasterData
{
public:
    SegyTraceData(std::shared_ptr<seismic::SegyFile> file) : m_file(file)
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
    m_ui->colormap->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating,true);
    // Attach spectogram
    spectrogram->attach(m_ui->colormap);
    //////////

    //////////
    // Trace plot
    m_ui->tracePlot->setSegyFile(file);
    m_ui->tracePlot->setAxisScale(QwtPlot::yLeft,interval.minValue(),interval.maxValue());
    //////////
}
