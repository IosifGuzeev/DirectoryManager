#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDebug>
#include <QVector>
#include <QMap>
#include <QDateTime>
#include <QFileInfo>
#include <stdlib.h>
#include "consolemanager.h"


class ConsoleManager;
struct FileInfo //Вспомогательная структура, представляющая собой пакет информации о конкретном файле.
{
    bool isExist;
    qint64 size;

    FileInfo(QString path);
};


///
/// Основной класс, отвечающий за работу с файлами.
/// Отслеживает удаление, добавление и изменение файлов из списка FilesInfo
///
class DirectoryManager : public QObject
{
    static QFileSystemWatcher *watcher;
    static QMap<QString, FileInfo> *FilesInfo;
    Q_OBJECT

public:
    static void Start()
    {
        std::system("CLS");
        connect(DirectoryManager::GetManager()->watcher, &QFileSystemWatcher::directoryChanged, DirectoryManager::GetManager(), DirectoryManager::PrintDirectoryChanges);
    }

    static const DirectoryManager* GetManager();

    static void AddFiles(const QVector<QString> &paths); //Добавить все файлы с заданными адресами.

    static void DeleteFiles(const QVector<QString> &paths); //Удалить все файлы с заданными адресами.

    static void PrintFiles(bool);   //Вывести все отслеживаемые файлы.
signals:
private slots:
    ///
    /// \brief DirectoryManager::PrintDirectoryChanges
    /// \param path Адрес директории, в которой было совершено изменение.
    /// При получении сигнала производится проверка всех отслеживаемых файлов.
    /// При наличии у них каких-либо изменений будет выведенно соответствующее сообщение в консоль.
    static void PrintDirectoryChanges(const QString &path);

private:
    DirectoryManager(){}
};



#endif // DIRECTORYMANAGER_H
