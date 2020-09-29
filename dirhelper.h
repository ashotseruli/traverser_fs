#ifndef DIRHELPER_H
#define DIRHELPER_H

#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <iostream>
#include <QCryptographicHash>

class DirHelper
{
public:   
    static QString fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm = QCryptographicHash::Md5)
    {
        QFile file(fileName);
        qint64 fileSize = file.size();
        const qint64 bufferSize = 1024 * 1024;

        if (file.open(QIODevice::ReadOnly))
        {
            char buffer[bufferSize];
            int bytesRead;
            int readSize = qMin(fileSize, bufferSize);

            QCryptographicHash hash(hashAlgorithm);
            while (readSize > 0 && (bytesRead = file.read(buffer, readSize)) > 0)
            {
                fileSize -= bytesRead;
                hash.addData(buffer, bytesRead);
                readSize = qMin(fileSize, bufferSize);
            }

            file.close();
            return QString(hash.result().toHex());
        }
        return QString();
    }


    /*
     * can be used for small files
     * static std::string fileMd5(const QString &fileName)
    {
       QFile f(fileName);
       if (f.open(QFile::ReadOnly)) {
           QCryptographicHash hash(QCryptographicHash::Md5);
           if (hash.addData(&f)) {
               return hash.result().toHex().toStdString();
           }
       }
       return "";
    }*/

    static bool isDateTimeInBounds(const QDateTime &dt, const QDateTime& from, const QDateTime& to)
    {
        bool result = true;
        if ( (!dt.isValid()) ||
             (from.isValid() && dt < from) ||
             (to.isValid() && dt > to) )
        {
            result = false;
        }
        return result;
    }

    static int printFilesInDir(const QDir &dir, const QDateTime& from = QDateTime(), const QDateTime& to = QDateTime())
    {
        int filesPrinted = 0;
        QFileInfoList filesInfoList = dir.entryInfoList(QDir::Files | QDir::NoSymLinks);
        for(const QFileInfo &fileInfo: filesInfoList)
        {
            QDateTime birthDateTime = fileInfo.birthTime();
            if (!isDateTimeInBounds(birthDateTime, from, to))
                continue;

            QString format = "yyyy-MM-dd hh:mm:ss";
            QString dtString = birthDateTime.toString(format);
            std::cout << fileChecksum(fileInfo.absoluteFilePath()).toStdString() << "\t"
                      << fileInfo.size() << "\t"
                      << dtString.toStdString() << "\t"
                      << fileInfo.absoluteFilePath().toStdString()
                      << std::endl;
            ++filesPrinted;
        }
        return filesPrinted;
    }
    static bool isDirectoryOk(const QString &path)
    {
        QDir dir(path);
        bool result = true;
        if (!dir.exists())
        {
            qWarning("path to directory is not correct!");
            result = false;
        }
        return result;
    }

private:
    DirHelper();
    DirHelper(const DirHelper&) = delete;
    DirHelper& operator=(const DirHelper&) = delete;

};

#endif // DIRHELPER_H
