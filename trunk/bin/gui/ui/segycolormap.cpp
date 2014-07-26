#include "segycolormap.h"
#include "ui_segycolormap.h"

#include <SegyFile.h>

#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_color_map.h>
#include <qwt_raster_data.h>

#include <algorithm>
#include <limits>
#include <vector>
#include <cstdint>

namespace {
template<class T>
class SegyTraceData: public QwtRasterData
{
public:
    SegyTraceData(std::shared_ptr<seismic::SegyFile> file)
    {
        using namespace seismic;

        size_t max_nsamples = 0;
        T min_value = std::numeric_limits<T>::max();
        T max_value = std::numeric_limits<T>::lowest();
        for( size_t ii = 0; ii < file->ntraces(); ++ii) {
            m_traces.push_back( std::move(file->readTraceAs<T>(ii) ) );
            max_nsamples = std::max(max_nsamples,m_traces[ii].size());
            auto minmax_value = std::minmax_element(m_traces[ii].begin(),m_traces[ii].end());
            min_value = std::min(min_value,*minmax_value.first);
            max_value = std::max(max_value,*minmax_value.second);
        }
        setInterval( Qt::XAxis, QwtInterval( 0, file->ntraces()-1 ) );
        setInterval( Qt::YAxis, QwtInterval( 0, max_nsamples-1 ) );
        setInterval( Qt::ZAxis, QwtInterval( min_value, max_value ) );
    }

    virtual double value( double x, double y ) const
    {
        return m_traces[x][y];
    }
private:
    std::vector< seismic::Trace<T> > m_traces;
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
    QWidget(parent),
    ui(new Ui::SegyColormap)
{
    ui->setupUi(this);
    auto spectrogram = new QwtPlotSpectrogram();
    spectrogram->setData( createSegyTraceData(file) );
    spectrogram->attach(ui->colormap);
    ui->colormap->setTitle("Trace amplitude ");
    ui->colormap->setAxisTitle( QwtPlot::yRight , "sample #");
}

SegyColormap::~SegyColormap()
{
    delete ui;
}
