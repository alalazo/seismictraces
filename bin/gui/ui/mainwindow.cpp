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
#include <segycolormap.h>

#include <SegyFile.h>

#include <QFileDialog>
#include <QMessageBox>

#include <sstream>
#include <string>
#include <stdexcept>

using namespace seismic;


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
    auto tfh = segy_handle->getTextualFileHeader();
    ebcdic2ascii(tfh);
    tfh_stream << tfh;
    m_ui->textualFileHeaderBrowser->setText(tfh_stream.str().c_str());
}

void MainWindow::on_actionSEG_Y_Colormap_triggered() {
    // Get current row from the active list
    auto irow = m_ui->segyFileList->currentRow();
    try {
        // Construct the colormap
        m_ui->tabWidget->addTab(new SegyColormap(m_segy_file_list.at(irow)),
                                m_segy_file_list.at(irow)->path().filename().c_str());
    } catch(std::exception& e) {
        QMessageBox::warning(this,"No SEG-Y file selected",
                             e.what());
    }
}

void MainWindow::on_actionAbout_triggered() {
    About aboutWindow(this);
    aboutWindow.exec();
}

void MainWindow::on_tabWidget_tabCloseRequested(int idx) {
    try {
        m_ui->tabWidget->removeTab(idx);
    } catch(std::exception& e) {
        QMessageBox::warning(this,"Unexpected error",
                             e.what());
    }
}
