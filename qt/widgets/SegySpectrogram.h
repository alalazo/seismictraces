#ifndef SEGYSPECTROGRAM_H
#define SEGYSPECTROGRAM_H

#include <QFrame>

#include <memory>

namespace Ui {
class SegySpectrogram;
}

namespace seismic {
class SegyFile;
}

/**
 * @brief Spectrogram of the traces contained in a SEG-Y file
 */
class SegySpectrogram : public QFrame
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param[in] parent parent widget
     */
    explicit SegySpectrogram(QWidget *parent = 0);    

    /**
     * @brief Sets the underlying SEG-Y file
     *
     * @param[in] file SEG-Y file
     */
    void setSegyFile(std::shared_ptr<seismic::SegyFile> file);

    /**
     * @brief Returns the maximum value to be plotted
     *
     * @return maximum value to be plotted
     */
    double max() const {
        return m_maximum;
    }

    /**
     * @brief Returns the minimum value to be plotted
     *
     * @return minimum value to be plotted
     */
    double min() const {
        return m_minimum;
    }

private:
    /// The underlying form
    std::shared_ptr<Ui::SegySpectrogram> m_ui;
    /// The SEG-Y file managed by the class
    std::shared_ptr<seismic::SegyFile> m_file;
    /// Maximum value
    double m_maximum;
    /// Minimum value
    double m_minimum;
};

#endif // SEGYSPECTROGRAM_H
