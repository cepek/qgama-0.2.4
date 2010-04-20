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


XMLValidatePlugin::XMLValidatePlugin()
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
            tr("Tools|Va&lidate GNU Gama XML Input/Output|XML|1|this->onValidate()|Ctrl+L");
}


QWidget* XMLValidatePlugin::configuration() const
{
    return 0;
}


void XMLValidatePlugin::openDialog()
{
    vd->exec();
}


void XMLValidatePlugin::validate()
{
    const QByteArray schemaData = schemaView->toPlainText().toUtf8();
    const QByteArray instanceData = instanceEdit->toPlainText().toUtf8();

    MessageHandler messageHandler;

    QXmlSchema schema;
    schema.setMessageHandler(&messageHandler);

    schema.load(schemaData);

    bool errorOccurred = false;
    if (!schema.isValid()) {
        errorOccurred = true;
    } else {
        QXmlSchemaValidator validator(schema);
        if (!validator.validate(instanceData))
            errorOccurred = true;
    }

    if (errorOccurred) {
        validationStatus->setText(messageHandler.statusMessage());
        moveCursor(messageHandler.line(), messageHandler.column());
    } else {
        validationStatus->setText(tr("validation successful"));
    }

    const QString styleSheet = QString("QLabel {background: %1; padding: 3px}")
                                      .arg(errorOccurred ? QColor(Qt::red).lighter(160).name() :
                                                           QColor(Qt::green).lighter(160).name());
    validationStatus->setStyleSheet(styleSheet);
}


Q_EXPORT_PLUGIN2(xmlvalidate_plugin, XMLValidatePlugin)
