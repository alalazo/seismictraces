#include <SegySpectrogram.h>
#include <ui_SegySpectrogram.h>
#include <TraceBuffer.h>

#include <SegyFile.h>

#include <qwt_raster_data.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_color_map.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_engine.h>

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
        break;
    }
    case (constants::SegyFileFormatCode::Int32):
    {
        return new SegyTraceData<int32_t>(file);
        break;
    }
    case (constants::SegyFileFormatCode::Int16):
    {
        return new SegyTraceData<int16_t>(file);
        break;
    }
    case (constants::SegyFileFormatCode::Int8):
    {
        return new SegyTraceData<int8_t>(file);
        break;
    }
    default:
        break;
    }
    return nullptr;
}

}

SegySpectrogram::SegySpectrogram(QWidget *parent) :
    QFrame(parent),
    m_ui(new Ui::SegySpectrogram)
{
    m_ui->setupUi(this);
    // Set style
    // Set titles on the plot
    m_ui->spectrogram->setTitle("Amplitude Colormap");
    m_ui->spectrogram->setAxisTitle( QwtPlot::yLeft  ,"trace #");
    m_ui->spectrogram->setAxisTitle( QwtPlot::xBottom,"sample #");
    // Colormap on the right
    m_ui->spectrogram->enableAxis( QwtPlot::yRight );
    m_ui->spectrogram->setAxisTitle( QwtPlot::yRight, "Amplitude");
}

void SegySpectrogram::setSegyFile(std::shared_ptr<SegyFile> file) {
    m_file = file;
    // Set Spectrogram data
    auto spectrogram = new QwtPlotSpectrogram();
    spectrogram->setData( createSegyTraceData(m_file) );
    // Colormap
    auto zinterval = spectrogram->interval(Qt::ZAxis);
    auto spectrogram_colormap = new QwtLinearColorMap(Qt::darkBlue,Qt::red);
    auto factor = zinterval.maxValue() - zinterval.minValue();
    auto zero_in_colormap = (std::max(zinterval.minValue(),0.0)-zinterval.minValue())/factor;
    spectrogram_colormap->addColorStop( zero_in_colormap*0.5,Qt::cyan);
    spectrogram_colormap->addColorStop( zero_in_colormap ,Qt::gray);
    spectrogram_colormap->addColorStop( (1 + zero_in_colormap)*0.5,Qt::yellow);
    spectrogram->setColorMap( spectrogram_colormap );    
    m_maximum = zinterval.maxValue();
    m_minimum = zinterval.minValue();
    // Colorbar on the right
    auto axisWidget = m_ui->spectrogram->axisWidget(QwtPlot::yRight);
    axisWidget->setColorMap( zinterval, spectrogram_colormap );
    axisWidget->setColorBarEnabled( true );
    // Plot
    m_ui->spectrogram->setAxisScale(QwtPlot::yRight,m_minimum,m_maximum);
    m_ui->spectrogram->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating,true);
    m_ui->spectrogram->axisScaleEngine(QwtPlot::yLeft)->setAttribute(QwtScaleEngine::Floating,true);
    spectrogram->attach( m_ui->spectrogram );
}
