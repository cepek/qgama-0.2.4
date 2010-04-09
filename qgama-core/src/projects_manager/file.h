#ifndef FILE_H
#define FILE_H

class QString;

class File
{
    private:
        QString name;
        QString category;
        QString type;
        QString path;
        bool opened;
        bool active;

    public:
        File() {}

        // setters
        void setName(const QString &name) { this->name = name; }
        void setCategory(const QString &category) { this->category = category; }
        void setType(const QString &type) { this->type = type; }
        void setPath(const QString &path) { this->path = path; }
        void setActive(bool active) { this->active = active; }
        void setOpened(bool opened) { this->opened = opened; }

        // getters
        QString name() { return name; }
        QString category() { return category; }
        QString type() { return type; }
        QString path() { return path; }
        bool isActive() { return active; }
        bool isOpened() { return opened; }
};

#endif // FILE_H
