/*
 *  SeismicTraces : another C++ library that reads files in SEG-Y format
 *
 *  Copyright (C) 2014  Massimiliano Culpo
 *
 *  This file is part of SeismicTraces.
 *
 *  SeismicTraces is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SeismicTraces is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SeismicTraces.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
}

void MainWindow::on_actionOpen_triggered() {

  QString filename = QFileDialog::getOpenFileName(this,
                                                  "Select a SEG-Y file to be opened",
                                                  ".","SEG-Y files (*.segy *.sgy)");
  if( ! filename.size() ) {

  }
}

void MainWindow::on_actionAbout_triggered() {
    About aboutWindow(this);
    aboutWindow.exec();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
