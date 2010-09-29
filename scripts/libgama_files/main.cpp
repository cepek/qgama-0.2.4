#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QStringList>
#include <iostream>

const QString gamalibFiles = "../../../gama/lib/Makefile.am";
const QString libQGamaProjectFile = "../../libqgama/libqgama.pro";


int main(int argc, char *argv[])
{
    QFile file(gamalibFiles);
    QVector<QString> headers;
    QVector<QString> sources;
    QVector<QString> headersExpat;
    QVector<QString> sourcesExpat;

    // Open the file with the gamalib files
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;
        QString category;

        // Read it line by line and grep headers and sources
        while (!in.atEnd()) {
            line = in.readLine().trimmed();
            if (line.endsWith("\\")) {
                line = line.split("\\").value(0).trimmed();
            }
            if (line.endsWith("=")) {
                category = line.split("=").value(0).trimmed();
                continue;
            }
            if (line.endsWith(".h")) {
                if (category == "expat" || category == "expat_extra")
                    headersExpat.append("../../gama/lib/" + line);
                else
                    headers.append("../../gama/lib/" + line);
            }
            else if (line.endsWith(".c") || line.endsWith(".cpp")) {
                if (category == "expat" || category == "expat_extra")
                    sourcesExpat.append("../../gama/lib/" + line);
                else
                    sources.append("../../gama/lib/" + line);
            }
        }

        // Close the file
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << gamalibFiles.toStdString() << std::endl;
    }

    // Open the libQGamaProjectFile
    QFile file2(libQGamaProjectFile);
    QString output;
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file2);
        QString line;

        // Read it line by line and grep headers and sources
        while (!in.atEnd()) {
            line = in.readLine();
            if (line.trimmed() == "SOURCES += \\") {
                break;
            }
            else {
                output += line + "\n";
            }
        }

        // Close the file
        file2.close();
    }
    else {
        std::cout << "Unable to open file: " << libQGamaProjectFile.toStdString() << std::endl;
    }

    // Open the result file
    QFile file3(libQGamaProjectFile);
    if (file3.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file3);

        // Write to file
        out << output;

        out << "HEADERS += \\ \n";
        for (int i=0; i<headers.size(); i++) {
            out << headers.value(i);
            if (i!=headers.size()-1)
                out << " \\";
            out << "\n";
        }

        out << "\nSOURCES += \\ \n";
        for (int i=0; i<sources.size(); i++) {
            out << sources.value(i);
            if (i!=sources.size()-1)
                out << " \\";
            out << "\n";
        }

        // Close the file
        file2.close();
    }
    else {
        std::cout << "Unable to open file: " << libQGamaProjectFile.toStdString() << std::endl;
    }
}
