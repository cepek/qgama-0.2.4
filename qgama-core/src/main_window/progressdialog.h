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

#ifndef QGAMACORE__PROGRESSDIALOG_H
#define QGAMACORE__PROGRESSDIALOG_H

#include <QProgressDialog>
#include <QWidget>


namespace QGamaCore {

    /**
      *
      */
    class ProgressDialog : public QProgressDialog
    {
        Q_OBJECT

        public:
            ProgressDialog(QWidget *parent, const QString &title, int minimum, int maximum) : QProgressDialog(parent) {
                setRange(minimum, maximum);
                setCancelButton(0);
                setAttribute(Qt::WA_DeleteOnClose);
                setWindowTitle(title);
                show();
            }

        private slots:
            void setLabel(int value, const QString &text) { setValue(value); setLabelText(text); }
    }; // class ProgressDialog

} // namespace QGamaCore


#endif // QGAMACORE__PROGRESSDIALOG_H
