#include "directorymanager.h"


QFileSystemWatcher *DirectoryManager::watcher =new QFileSystemWatcher();
QMap<QString, FileInfo> *DirectoryManager::FilesInfo = new QMap<QString, FileInfo>();

const DirectoryManager *DirectoryManager::GetManager()
{
    return new DirectoryManager();
}

void DirectoryManager::AddFiles(const QVector<QString> &paths)
{
    for (auto &path:paths)
    {
        QString directory = path.left(path.lastIndexOf('\\'));
        watcher->addPath(directory);
        watcher->addPath(path);
        FilesInfo->insert(path, FileInfo(path));
    }
    ConsoleManager::Write("List of files:");
    for(auto &file: watcher->files())
    {
        ConsoleManager::Write(file);
    }

    ConsoleManager::Write("End of list");
    connect(DirectoryManager::GetManager()->watcher, &QFileSystemWatcher::directoryChanged, DirectoryManager::GetManager(), DirectoryManager::PrintDirectoryChanges);
}

void DirectoryManager::PrintDirectoryChanges(const QString &path)
{
    for (auto const &key: FilesInfo->keys())
    {
        if(key.contains(path))
        {
            FileInfo oldState = FilesInfo->find(key).value();
            FileInfo newState = FileInfo(key);

            if (oldState.isExist != newState.isExist)
            {
                if(newState.isExist)
                {
                    ConsoleManager::Write(key + " has been created!");
                }
                else
                    ConsoleManager::Write(key + " has been deleted!");
                FilesInfo->find(key).operator->()->isExist = newState.isExist;
            }

            if (newState.isExist && oldState.size != newState.size)
            {
                ConsoleManager::Write(key + " got new size: " + QString::number(newState.size));
                FilesInfo->find(key).operator->()->size = newState.size;
            }


        }
    }
}
