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

#include <SegyFile.h>

#include <QFileDialog>

#include <sstream>
#include <string>

using namespace seismic;

#include<impl/rev1/SegyFile-Fields-Rev1.h>

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
  if( !filename.isEmpty() ) { // If a file has been selected
      // Convert to const char * and insert into the vector of data
      auto c_filename = filename.toLocal8Bit();
      m_segy_file_list.push_back( std::shared_ptr<SegyFile>(new SegyFile(c_filename.data(),"Rev1")) );
      auto & list = *m_ui->segyFileList;
      list.addItem(filename);
  }
}

void MainWindow::on_segyFileList_currentRowChanged(int row) {
    const auto & segy_handle = m_segy_file_list.at(row);

    std::stringstream tfh_stream;
    ebcdic2ascii(segy_handle->getTextualFileHeader());
    tfh_stream << segy_handle->getTextualFileHeader() ;
    m_ui->textualFileHeaderBrowser->setText(tfh_stream.str().c_str());
}

void MainWindow::on_actionAbout_triggered() {
    About aboutWindow(this);
    aboutWindow.exec();
}
