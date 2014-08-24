#include "BinaryFileHeaderViewer.h"
#include "ui_BinaryFileHeaderViewer.h"

BinaryFileHeaderViewer::BinaryFileHeaderViewer(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::BinaryFileHeaderViewer)
{
    m_ui->setupUi(this);
    m_ui->tableWidget->setRowCount(10);
    m_ui->tableWidget->setColumnCount(2);
    m_ui->tableWidget->verticalHeader()->setVisible(false);
}
