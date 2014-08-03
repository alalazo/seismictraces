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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <vector>

namespace Ui {
class MainWindow;
}

namespace seismic {
class SegyFile;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:

    /**
     * @brief Prompts for the selection of a new file
     */
    void on_actionOpen_triggered();

    /**
     * @brief Creates the about window as a child of this
     * using modal mode
     */
    void on_actionAbout_triggered();

    /**
     * @brief Set new content in the widgets, based on the current selection
     * @param[in] row currently selected row
     */
    void on_segyFileList_currentRowChanged(int row);

    /**
     * @brief Creates a new analysis tab
     */
    void on_actionSEG_Y_Colormap_triggered();

    /**
     * @brief Close the tab for which the request was issued
     * @param[in] idx tab index
     */
    void on_tabWidget_tabCloseRequested(int idx);

    /**
     * @brief Closes an open SEG-Y file
     */
    void on_actionClose_triggered();

private:    
    /// Implementation generated from forms
    std::shared_ptr<Ui::MainWindow> m_ui;
    /// List of handles to SEG-Y files that are currently open
    std::vector< std::shared_ptr<seismic::SegyFile> > m_segy_file_list;
};

#endif // MAINWINDOW_H
