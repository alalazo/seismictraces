#include <trace_plot.h>
#include <ui_trace_plot.h>
#include <TraceBuffer.h>

#include <SegyFile.h>

#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_engine.h>

using namespace seismic;

namespace {
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
    // Create plot curve
    auto plot = new QwtPlotCurve;
    plot->setSamples(x,y);
    // Set style
    plot->setPen(Qt::red);

    return plot;
}

}

trace_plot::trace_plot(QWidget *parent) : QFrame(parent), m_ui(new Ui::trace_plot){
    // Initialize the form
    m_ui->setupUi(this);
}

void trace_plot::setSegyFile(std::shared_ptr<SegyFile> file)
{    
    m_file = file;
    // Set style
    m_ui->plot->setTitle("Trace Plot");
    m_ui->plot->setAxisTitle(QwtPlot::xBottom,"time");
    m_ui->plot->setAxisTitle(QwtPlot::yLeft,"amplitude");
    //m_ui->plot->setAxisScale(QwtPlot::yLeft,interval.minValue(),interval.maxValue());
    m_ui->plot->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Floating,true);
    // Add a grid
    auto grid = new QwtPlotGrid;
    grid->attach(m_ui->plot);
    // Set limit for spin box
    m_ui->idxSpinBox->setMaximum(m_file->ntraces());
    // Set plot to trace 0
    auto trace_plot = createTracePlot(m_file,0);
    trace_plot->attach( m_ui->plot );
    m_ui->plot->replot();
}

void trace_plot::setAxisScale(int axisID, double min, double max, double step) {
    m_ui->plot->setAxisScale(axisID,min,max,step);
}

void trace_plot::on_idxSpinBox_valueChanged(int value) {
    auto trace_plot = createTracePlot(m_file,value);
    m_ui->plot->detachItems();
    trace_plot->attach( m_ui->plot );
    /// @fixme It should not be necessary to detach the grid
    auto grid = new QwtPlotGrid;
    grid->attach(m_ui->plot);
    m_ui->plot->replot();
}
