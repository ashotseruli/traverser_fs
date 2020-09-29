#include "traverser.h"
#include <QDateTime>

Traverser::Traverser()
{
}

bool Traverser::traverse(const QString &path, algorythmType algorythm)
{
    bool result = true;
    QDir rootDir(path);
    if (DirHelper::isDirectoryOk(path))
    {
        switch (algorythm) {
            case algorythmType::inDepth:
            {
                traverseInDepth(path);
                break;
            }
            case algorythmType::inWidth:
            {
                traverseInWidth(path);
                break;
            }
            case algorythmType::byDate:
            {
                traverseByDate(path);
                break;
            }
            default:
            {
                qWarning("Unknown algorythm! Will traverse in depth");
                traverseInDepth(path);
            }
        }
    }
    else
    {
        result = false;
    }
    return result;
}

void Traverser::traverseInDepth(const QString &path)
{
    QDir dir(path);
    if (!dir.isEmpty())
    {
        DirHelper::printFilesInDir(dir);
        QStringList subdirsList = dir.entryList(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for(const QString &subdirName: subdirsList)
        {
            traverseInDepth(dir.absoluteFilePath(subdirName));
        }
    }
}

int Traverser::traverseInWidth(const QString &path, const QDateTime& from, const QDateTime& to)
{
    int filesPrintedNumber = 0;
    m_dirsQueue.push_back(path);
    while(!m_dirsQueue.empty())
    {
        QDir dir(m_dirsQueue.dequeue());
        filesPrintedNumber += DirHelper::printFilesInDir(dir, from, to);
        QStringList subdirsList = dir.entryList(QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for(const QString &subdirName: subdirsList)
        {
            QString fullName = dir.absoluteFilePath(subdirName);
            QFileInfo info(fullName);
            if (DirHelper::isDateTimeInBounds(info.birthTime(), from, to))
            {
                m_dirsQueue.enqueue(fullName);
            }
        }
    }
    return filesPrintedNumber;
}

void Traverser::traverseByDate(const QString &path)
{
    QDateTime now = QDateTime::currentDateTime();
    const int MONTHS_IN_YEAR = 12;
    QDateTime periodBegin, periodEnd;

    periodBegin = now;
    periodEnd = now.addMonths(1);

    std::cout << "newer than 1 month:" << std::endl;
    int numberOfFiles = traverseInWidth(path, periodBegin, periodEnd);
    if (numberOfFiles == 0)
       std::cout << "no such files!" << std::endl;

    for(int i = 1; i < MONTHS_IN_YEAR; ++i)
    {
        periodBegin = now.addMonths(i);
        periodEnd = now.addMonths(i+1);

        std::cout << "older than " << i << "months:" << std::endl;
        numberOfFiles = traverseInWidth(path, periodBegin, periodEnd);
        if (numberOfFiles == 0)
           std::cout << "no such files!" << std::endl;
    }
    periodBegin = QDateTime();
    periodEnd = now.addYears(1);
    std::cout << "older than a year:" << std::endl;
    numberOfFiles = traverseInWidth(path, periodBegin, periodEnd);
    if (numberOfFiles == 0)
       std::cout << "no such files!";
}
