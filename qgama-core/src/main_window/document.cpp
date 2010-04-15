#include <QtGui>

#include "document.h"
#include "../utils/utils.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
Document::Document(const QString &type) :
    mw(qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"))),
    docType(type)
{
    // makes Qt delete this widget when the widget has accepted the close event (see QWidget::closeEvent())
    setAttribute(Qt::WA_DeleteOnClose);
}


/* ===============================================================================================================*/
/**
  *
  */
Document::~Document()
{

}


/* ===============================================================================================================*/
/**
  *
  */
QString Document::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


void Document::modificationChanged(bool changed) {
    // add asterisk to window title
}
