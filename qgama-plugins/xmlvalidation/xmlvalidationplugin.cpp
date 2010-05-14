#include <QtGui>
#include <QtXmlPatterns>

#include "xmlvalidationplugin.h"
#include "messagehandler.h"
#include <qgama-core/src/main_window/texteditor.h>


using namespace QGamaCore;
using namespace QGamaPlugins;


/**
  *
  */
XMLValidationPlugin::XMLValidationPlugin()
{
    // iniatialize the schema data
    QFile schemaFile(QString(":/xml/gama-local.xsd"));
    schemaFile.open(QIODevice::ReadOnly);
    const QString schemaText(QString::fromUtf8(schemaFile.readAll()));
    schemaData = schemaText.toAscii();
}


/**
  *
  */
XMLValidationPlugin::~XMLValidationPlugin()
{
}


/**
  *
  */
QIcon XMLValidationPlugin::icon() const
{
    QIcon icon(":/images/icons/standardbutton-apply-32.png");
    return icon;
}


/**
  *
  */
QString XMLValidationPlugin::name() const
{
    return tr("GNU Gama Network XML Validator.");
}


/**
  *
  */
QString XMLValidationPlugin::description() const
{
    return tr("Validator of the input XML format of GNU Gama against corresponding .xsd schema.");
}


/**
  *
  */
QStringList XMLValidationPlugin::authors() const
{
    return QStringList() << tr("Jiri Novak (jiri.novak.2@fsv.cvut.cz)");
}


/**
  *
  */
QStringList XMLValidationPlugin::items() const
{
    return QStringList() << tr("Va&lidate GNU Gama XML Input/Output|XML|1|validate()|Ctrl+L");
}


/**
  *
  */
void XMLValidationPlugin::validate()
{
    TextEditor *textEditor = acp->getActiveTextEditor();
    Q_ASSERT(textEditor!=0 && "textEditor pointer is 0!");

    instanceData = textEditor->getContent().toAscii();

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
        textEditor->setLabelValidationText(messageHandler.statusMessage());
        textEditor->moveCursor(messageHandler.line(), messageHandler.column());
    } else {
        textEditor->setLabelValidationText(tr("validation successful"));
        textEditor->clearHighlights();
    }

    const QString styleSheet = QString("QLabel {background: %1; padding: 3px}")
                                      .arg(errorOccurred ? QColor(Qt::red).lighter(160).name() :
                                                           QColor(Qt::green).lighter(160).name());
    textEditor->setLabelValidationStyleSheet(styleSheet);
}

Q_EXPORT_PLUGIN2(xmlvalidation_plugin, QGamaPlugins::XMLValidationPlugin)
