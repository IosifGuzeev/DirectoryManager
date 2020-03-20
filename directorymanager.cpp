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
        //Будем отслеживать директории, где хранятся файлы,
        //Это позволит нам отследить как удаление наблюдаемоего файла, так и добавление.
        QString directory = path.left(path.lastIndexOf('\\'));
        watcher->addPath(directory);
        watcher->addPath(path);
        FilesInfo->insert(path, FileInfo(path));
    }
}

void DirectoryManager::DeleteFiles(const QVector<QString> &paths)
{
    for(auto &path: paths)
    {
        if (FilesInfo->find(path) == FilesInfo->end())
            ConsoleManager::Write("File with path " + path + " not found!");
        else
            FilesInfo->erase(FilesInfo->find(path));
    }
}

void DirectoryManager::PrintFiles()
{
    for(auto i = FilesInfo->begin(); i != FilesInfo->end(); i++)
    {
        ConsoleManager::Write(i.key());
    }
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

FileInfo::FileInfo(QString path)
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
