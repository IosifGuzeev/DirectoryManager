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

struct FileInfo
{
    bool isExist;
    qint64 size;

    FileInfo(QString path)
    {
        QFileInfo qFileInfo(path);
        if (qFileInfo.exists())
        {
            isExist = true;
            size = qFileInfo.size();
        }
        else
        {
            isExist = false;
            size = 0;
        }
    }
};

class DirectoryManager : public QObject
{
    static QFileSystemWatcher *watcher;
    static QMap<QString, FileInfo> *FilesInfo;
    Q_OBJECT

public:
    static const DirectoryManager* GetManager();

    static void AddFiles(const QVector<QString> &paths);

    static void DeleteFiles(const QVector<QString> &paths)
    {
        for(auto &path: paths)
        {
            if (FilesInfo->find(path) == FilesInfo->end())
                ConsoleManager::Write("File with path " + path + " not found!");
            FilesInfo->erase(FilesInfo->find(path));
        }
    }
signals:
private slots:
    static void PrintDirectoryChanges(const QString &path);

private:
    DirectoryManager(){}
};



#endif // DIRECTORYMANAGER_H
