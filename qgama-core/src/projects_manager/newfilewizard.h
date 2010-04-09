#ifndef NEWFILEWIZARD_H
#define NEWFILEWIZARD_H

#include <QWizard>


namespace QGamaCore {

    /**
      *
      */
    class NewFileWizard : public QWizard
    {
        Q_OBJECT

        public:
            enum { Page_Select_File_Type, Page_Select_Name_And_Location };

            NewFileWizard(QWidget *parent = 0);

        private slots:
            void showHelp();
    };

} // namespace QGamaCore

#endif // NEWFILEWIZARD_H
