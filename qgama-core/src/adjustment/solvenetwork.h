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

#ifndef QGAMACORE__SOLVENETWORK_H
#define QGAMACORE__SOLVENETWORK_H

#include "../projects_manager/adjustmentsetting.h"
#include "../main_window/document.h"
#include <string>
#include <QThread>


namespace QGamaCore {

    /**
      *
      */
    class SolveNetwork : public QThread
    {
        Q_OBJECT

        signals:
            void solved(const QString outputXmlStream, const QString outputTxtStream, const QString outputHtmlStream, Document *document, AdjustmentSetting *as);
            void solvingFailed(const QString errorMessage);
            void label(int value, const QString &text);

        public:
            SolveNetwork(const QString &stream, AdjustmentSetting *setting, Document *doc);

        protected:
            virtual void run();

        private slots:
            void onTerminate();

        private:
            void solveNetwork_(QString &xmlStream, QString &txtStream, QString &htmlStream);

            QString inputXmlStream;
            QGamaCore::AdjustmentSetting *as;
            QGamaCore::Document *document;
    }; // class GamaLocal

} // namespace QGamaCore


#endif // QGAMACORE__SOLVENETWORK_H
