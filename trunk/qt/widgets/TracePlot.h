#ifndef TRACE_PLOT_H
#define TRACE_PLOT_H

#include <QFrame>

#include <memory>

namespace Ui {
class TracePlot;
}

namespace seismic {
class SegyFile;
}

/**
 * @brief Two dimensional plot of a seismic trace
 */
class TracePlot : public QFrame
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param[in] parent parent widget
     */
    explicit TracePlot(QWidget *parent = 0);

    /**
     * @brief Sets the underlying SEG-Y file
     *
     * @param[in] file SEG-Y file
     */
    void setSegyFile(std::shared_ptr<seismic::SegyFile> file);

    /**
     * @brief Sets the axis scale
     *
     * @param[in] axisID id of the axis
     * @param[in] min minimum value
     * @param[in] max maximum value
     * @param[in] step step
     */
    void setAxisScale(int axisID, double min, double max, double step = 0);

private slots:
    /**
     * @brief Slot to be activated when idxSpinBox changes value
     *
     * @param[in] value new value of the spin-box
     */
    void on_idxSpinBox_valueChanged(int value);

private:
    /// The underlying form
    std::shared_ptr<Ui::TracePlot> m_ui;
    /// The SEG-Y file managed by the class
    std::shared_ptr<seismic::SegyFile> m_file;
};

#endif // TRACE_PLOT_H
