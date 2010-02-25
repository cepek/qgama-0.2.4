#include "xmlvalidationplugin.h"
#include "xmlvalidationdialog.h"

#include <QString>
#include <QStringList>
#include <QIcon>
#include <QMessageBox>
#include <QAction>
#include <QApplication>
#include <iostream>
#include <QWidget>


XMLValidatePlugin::XMLValidatePlugin() : vd(new XMLValidationDialog())
{

}

XMLValidatePlugin::~XMLValidatePlugin()
{
    delete vd;
}


QIcon XMLValidatePlugin::icon() const
{
    QIcon icon(":/images/icons/standardbutton-apply-32.png");
    return icon;
}


QString XMLValidatePlugin::name() const
{
    return tr("GNU Gama Input/Output XML Validator.");
}


QString XMLValidatePlugin::description() const
{
    return tr("Validator of input and output XML format of GNU Gama against corresponding .xsd schemas.");
}


QStringList XMLValidatePlugin::authors() const
{
    return QStringList() <<
            tr("Jiri Novak (jiri.novak.2@fsv.cvut.cz)");
}


QStringList XMLValidatePlugin::items() const
{
    return QStringList() << 
            tr("Tools|Va&lidate GNU Gama XML Input/Output|XML|1|this->openDialog()|Ctrl+L");
}


QWidget* XMLValidatePlugin::configuration() const
{
    return 0;
}


void XMLValidatePlugin::openDialog()
{
    vd->exec();
}


Q_EXPORT_PLUGIN2(xmlvalidate_plugin, XMLValidatePlugin)
