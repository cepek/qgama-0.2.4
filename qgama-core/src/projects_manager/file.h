#ifndef FILE_H
#define FILE_H

#include <QString>


namespace QGamaCore {

    /**
      *
      */
    class File
    {
        private:
            QString name;
            QString path;
            QString opened;
            QString format;
            int settingsId;
            int id;
            bool displayed;

        public:
            File() { displayed=false; }
            ~File() {}

            // setters
            void setName(const QString &name)       { this->name=name; }
            void setPath(const QString &path)       { this->path=path; }
            void setOpened(const QString &opened)   { this->opened=opened; }
            void setFormat(const QString &format)   { this->format=format; }
            void setSettingsId(int settingsId)      { this->settingsId=settingsId; }
            void setId(int id)                      { this->id=id; }
            void setDisplayed(bool displayed)       { this->displayed=displayed; }

            // getters
            QString getName() const     { return name; }
            QString getPath() const     { return path; }
            QString getOpened() const   { return opened; }
            QString getFormat() const   { return format; }
            int getSettingsId() const   { return settingsId; }
            int getId() const           { return id; }
            bool isDisplayed() const    { return displayed; }
    }; // class File

} // namespace QGamaCore


#endif // FILE_H
