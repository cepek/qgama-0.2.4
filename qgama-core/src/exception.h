#ifndef QGAMACORE__EXCEPTION_H
#define QGAMACORE__EXCEPTION_H

#include <QString>

namespace QGamaCore {

    /**
      *
      */
    class Exception {

        public:
           const QString text;
           Exception(const QString &t) : text(t) {}
    }; // class Exception

} // namespace QGamaCore

#endif // QGAMACORE__EXCEPTION_H
