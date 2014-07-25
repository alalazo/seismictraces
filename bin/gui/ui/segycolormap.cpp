#include "segycolormap.h"
#include "ui_segycolormap.h"

#include <SegyFile.h>

#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_color_map.h>
#include <qwt_raster_data.h>

#include <algorithm>
#include <vector>
#include <cstdint>

namespace {
class SegyTraceData: public QwtRasterData
{
public:
    SegyTraceData(std::shared_ptr<seismic::SegyFile> file)
    {
        using namespace seismic;

        size_t max_nsamples = 0;
        float min_value = INT16_MAX;
        float max_value = INT16_MIN;
        for( size_t ii = 0; ii < file->ntraces(); ++ii) {
            m_traces.push_back( std::move(file->readTraceAs<float>(ii) ) );
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
    std::vector< seismic::Trace<float> > m_traces;
};
}

SegyColormap::SegyColormap(std::shared_ptr<seismic::SegyFile> file, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SegyColormap)
{
    ui->setupUi(this);
    auto spectrogram = new QwtPlotSpectrogram();
    spectrogram->setData( new SegyTraceData(file) );
    spectrogram->attach(ui->colormap);
    ui->colormap->setTitle("Trace amplitude ");
    ui->colormap->setAxisTitle( QwtPlot::yRight , "sample #");
}

SegyColormap::~SegyColormap()
{
    delete ui;
}
