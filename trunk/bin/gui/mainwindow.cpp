#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::on_actionOpen_triggered() {

  QString filename = QFileDialog::getOpenFileName(this,
                                                  "Select a SEG-Y file to be opened",
                                                  ".","SEG-Y files (*.segy *.sgy)");
  if( ! filename.size() ) {

  }
}

MainWindow::~MainWindow()
{
    delete ui;
}
