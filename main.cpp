#include <QCoreApplication>
#include "consolemanager.h"
#include <QDebug>
#include <QVector>
#include "directorymanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConsoleManager::Start();
    DirectoryManager::Start();

    QVector<QString> paths = {
        "C:\\test\\1.txt",
        "C:\\test\\2.txt",
        "C:\\test\\3.txt",
        "C:\\test\\4.txt",
        "C:\\test\\5.txt"
    };
    DirectoryManager::AddFiles(paths);
    return a.exec();
}
