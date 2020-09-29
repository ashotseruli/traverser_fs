#ifndef TRAVERSER_H
#define TRAVERSER_H

#include <QString>
#include <QFileInfo>
#include <QQueue>
#include <QDateTime>

#include "algorythmType.h"
#include "dirhelper.h"

class Traverser
{
public:
    Traverser();
    bool traverse(const QString &path, algorythmType algorythm = algorythmType::inDepth);

private:
    void traverseInDepth(const QString &path);
    int traverseInWidth(const QString &path, const QDateTime &from = QDateTime(), const QDateTime &to = QDateTime());
    void traverseByDate(const QString &path);

    QQueue<QString> m_dirsQueue;
};

#endif // TRAVERSER_H
