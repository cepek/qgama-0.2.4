/****************************************************************************
**
**    QGamaCore GUI C++ Library (QGamaCoreLib)
**    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>
**
**    This file is part of the QGamaCore GUI C++ Library.
**
**    This library is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 3 of the License, or
**    (at your option) any later version.
**
**    This library is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this library; if not, write to the Free Software
**    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
****************************************************************************/


#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <iostream>

#include "main_window/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // load qt translator
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    // load QGamaCore application translator
    QTranslator myappTranslator;
    myappTranslator.load(":/translations/qgamacore_"+QLocale::system().name()+".qm");
    app.installTranslator(&myappTranslator);

    // create application's main window and show it
    QGamaCore::MainWindow w;
    w.show();

    // start the event loop
    return app.exec();
}
