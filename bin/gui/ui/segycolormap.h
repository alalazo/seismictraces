#ifndef SEGYCOLORMAP_H
#define SEGYCOLORMAP_H

#include <QWidget>

#include<memory>

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
    ~SegyColormap();

private:
    Ui::SegyColormap *ui;
};

#endif // SEGYCOLORMAP_H
