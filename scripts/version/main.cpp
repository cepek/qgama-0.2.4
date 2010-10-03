#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QStringList>
#include <iostream>

const QString gama="../../../gama/configure.ac";
const QString qgama="../../qgama-core/src/qgama-core.pro";
const QString configHeader="../../config.h";

int main(int argc, char *argv[])
{
    QString gamaVersion;
    QString qGamaVersion;

    // Open the file with the gama version information
    QFile file(gama);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;

        // Read it line by line and find line with the version info
        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            if (line.startsWith("AC_INIT"))
                break;
        }

        // Close the file
        file.close();

        // Get the Gama version from line
        gamaVersion = line.split(",").value(1).trimmed();
        gamaVersion = gamaVersion.mid(1,gamaVersion.length()-2);
    }
    else {
        std::cout << "Unable to open file: " << gama.toStdString() << std::endl;
    }

    // Open the file with the QGama version information
    QFile file2(qgama);
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file2);
        QString line;

        // Read it line by line and find line with the version info
        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            if (line.startsWith("QGAMA_VERSION"))
                break;
        }

        // Close the file
        file2.close();

        // Get the Gama version from line
        qGamaVersion = line.split("=").value(1).trimmed();
    }
    else {
        std::cout << "Unable to open file: " << qgama.toStdString() << std::endl;
    }

    // Open the result file
    QFile file3(configHeader);
    if (file3.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file3);

        // Write to file
        out << "#define VERSION \"" << gamaVersion << "\"\n";
        out << "#define GAMA_VERSION \"" << gamaVersion << "\"\n";
        out << "#define QGAMA_VERSION \"" << qGamaVersion << "\"\n";

        // Close the file
        file3.close();
    }
    else {
        std::cout << "Unable to open file: " << configHeader.toStdString() << std::endl;
    }
}
