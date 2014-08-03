#ifndef SEGYCOLORMAP_H
#define SEGYCOLORMAP_H

#include <QWidget>

#include <memory>

namespace Ui {
class SegyColormap;
}

namespace seismic {
class SegyFile;
}

class SegyColormap : public QWidget
{
    Q_OBJECT

public:
    explicit SegyColormap(std::shared_ptr<seismic::SegyFile> file, QWidget *parent = 0);

private:
    std::shared_ptr<Ui::SegyColormap> m_ui;
    std::shared_ptr<seismic::SegyFile> m_file;
};

#endif // SEGYCOLORMAP_H
