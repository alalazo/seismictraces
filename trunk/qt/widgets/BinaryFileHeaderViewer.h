#ifndef BINARYFILEHEADERVIEWER_H
#define BINARYFILEHEADERVIEWER_H

#include <QWidget>

#include <memory>

namespace Ui {
class BinaryFileHeaderViewer;
}

class BinaryFileHeaderViewer : public QWidget
{
    Q_OBJECT

public:
    explicit BinaryFileHeaderViewer(QWidget *parent = 0);

private:
    std::shared_ptr<Ui::BinaryFileHeaderViewer> m_ui;
};

#endif // BINARYFILEHEADERVIEWER_H
