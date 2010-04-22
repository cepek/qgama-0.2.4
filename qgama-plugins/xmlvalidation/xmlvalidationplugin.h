#ifndef QGAMAPLUGINS__XMLVALIDATIONPLUGIN_H
#define QGAMAPLUGINS__XMLVALIDATIONPLUGIN_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QIcon>
#include <QList>
#include <QMenu>
#include <QAction>

#include <qgama-core/src/plugins_manager/plugininterface.h>


namespace QGamaPlugins {

    /**
      *
      */
    class XMLValidationPlugin : public QGamaCore::PluginInterface
    {
            Q_OBJECT
            Q_INTERFACES(QGamaCore::PluginInterface)

        public:
            XMLValidationPlugin();
            ~XMLValidationPlugin();

            QIcon icon() const;
            QString name() const;
            QString description() const;
            QStringList authors() const;
            QStringList items() const;

        private:
            QByteArray schemaData;
            QByteArray instanceData;

        private slots:
            void validate();
    }; // class XMLValidationPlugin

} // namespace QGamaPlugins


#endif // QGAMAPLUGINS__XMLVALIDATIONPLUGIN_H
