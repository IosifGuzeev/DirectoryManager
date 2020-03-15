#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDebug>
#include <QVector>
#include <QMap>
#include <QDateTime>
#include <QFileInfo>
#include "consolemanager.h"

class ConsoleManager;
struct FileInfo
{
    bool isExist;
    qint64 size;

    FileInfo(QString path);
};

class DirectoryManager : public QObject
{
    static QFileSystemWatcher *watcher;
    static QMap<QString, FileInfo> *FilesInfo;
    Q_OBJECT

public:
    static const DirectoryManager* GetManager();

    static void AddFiles(const QVector<QString> &paths);

    static void DeleteFiles(const QVector<QString> &paths);

    static void PrintFiles();
signals:
private slots:
    static void PrintDirectoryChanges(const QString &path);

private:
    DirectoryManager(){}
};



#endif // DIRECTORYMANAGER_H
