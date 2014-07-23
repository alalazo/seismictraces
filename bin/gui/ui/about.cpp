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

#include "about.h"
#include "ui_about.h"

const QString About::m_url("https://sourceforge.net/projects/seismictraces/");

About::About(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::About)
{
    m_ui->setupUi(this);
    setWindowTitle(tr("About %1").arg(QCoreApplication::applicationName()) );
    //////////
    // Set title string and fonts
    auto& title = *(m_ui->title);
    title.setText("SeismoView v 1.0");
    QFont title_font;
    title_font.setBold(true);
    title_font.setPointSize( title_font.pointSize() + 4 );
    title.setFont(title_font);
    //////////

    //////////
    // Set content text
    auto& content = *(m_ui->content);
    content.setHtml( makeHtml() );
    //////////

}

QString About::makeHtml() {
    QString content = QString("<p><a href=\"%1\">%2</a></p>"
                              "<p><b>%3:</b>").arg(m_url,m_url, tr("Authors"));
    content +=  "<br /> Massimiliano Culpo";
    return content;
}

About::~About()
{
    delete m_ui;
}
