#ifndef XMLValidationPlugin_H
#define XMLValidationPlugin_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QIcon>
#include <QList>
#include <QMenu>
#include <QAction>
#include <qgama-core/src/plugins_manager/plugininterface.h>
#include "xmlvalidationdialog.h"

class QWidget;

class XMLValidatePlugin : public QGamaCore::PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(QGamaCore::PluginInterface)

public:
    XMLValidatePlugin();
    ~XMLValidatePlugin();

    QIcon icon() const;
    QString name() const;
    QString description() const;
    QStringList authors() const;
    QStringList items() const;
    QWidget* configuration() const;

private:
    void validate();

private slots:
    void openDialog();
};

#endif
