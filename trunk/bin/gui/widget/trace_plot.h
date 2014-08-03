#ifndef TRACE_PLOT_H
#define TRACE_PLOT_H

#include <QFrame>

namespace Ui {
class trace_plot;
}

class trace_plot : public QFrame
{
    Q_OBJECT

public:
    explicit trace_plot(QWidget *parent = 0);
    ~trace_plot();

private:
    Ui::trace_plot *ui;
};

#endif // TRACE_PLOT_H
