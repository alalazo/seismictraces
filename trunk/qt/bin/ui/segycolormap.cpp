#include "segycolormap.h"
#include "ui_segycolormap.h"

#include <SegyFile.h>

#include <qwt_plot.h>

using namespace seismic;

SegyColormap::SegyColormap(std::shared_ptr<SegyFile> file, QWidget *parent) :
    QWidget(parent), m_ui(new Ui::SegyColormap), m_file(file)
{
    m_ui->setupUi(this);
    //////////
    // Spectrogram
    m_ui->segyColormap->setSegyFile(m_file);
    // Trace plot
    m_ui->tracePlot->setSegyFile(m_file);
    m_ui->tracePlot->setAxisScale(QwtPlot::yLeft,m_ui->segyColormap->min(),m_ui->segyColormap->max());
    //////////
}
