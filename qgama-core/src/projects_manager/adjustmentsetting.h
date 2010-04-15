#ifndef ADJUSTMENTSETTING_H
#define ADJUSTMENTSETTING_H

#include <QString>


namespace QGamaCore {

    /**
      *
      */
    class AdjustmentSetting
    {
        private:
            int id;
            QString algorithm;
            QString output;
            QString encoding;
            QString ellipsoid;
            QString language;
            QString covband;
            QString name;
            QString angles;
            QString latitude;
            bool displayed;

        public:
            AdjustmentSetting() { displayed=false; }
            ~AdjustmentSetting() {}

            // setters
            void setAlgorithm(const QString &algorithm) { this->algorithm=algorithm; }
            void setOutput(const QString &output)       { this->output=output; }
            void setEncoding(const QString &encoding)   { this->encoding=encoding; }
            void setEllipsoid(const QString &ellipsoid) { this->ellipsoid=ellipsoid; }
            void setLanguage(const QString &language)   { this->language=language; }
            void setCovband(const QString &covband)     { this->covband=covband; }
            void setName(const QString &name)           { this->name=name; }
            void setAngles(const QString &angles)       { this->angles=angles; }
            void setLatitude(const QString &latitude)   { this->latitude=latitude; }
            void setDisplayed(bool displayed)           { this->displayed=displayed; }
            void setId(int id)                          { this->id=id; }

            // getters
            QString getAlgorithm() const  { return algorithm; }
            QString getOutput() const     { return output; }
            QString getEncoding() const   { return encoding; }
            QString getEllipsoid() const  { return ellipsoid; }
            QString getLanguage() const   { return language; }
            QString getCovband() const    { return covband; }
            QString getName() const       { return name; }
            QString getAngles() const     { return angles; }
            QString getLatitude() const   { return latitude; }
            bool isDisplayed() const      { return displayed; }
            int getId() const             { return id; }
    }; // class AdjustmentSetting

} // namespace QGamaCore

#endif // ADJUSTMENTSETTING_H
