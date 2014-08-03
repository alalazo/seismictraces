#include "trace_plot.h"
#include "ui_trace_plot.h"

trace_plot::trace_plot(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::trace_plot)
{
    ui->setupUi(this);
}

trace_plot::~trace_plot()
{
    delete ui;
}
