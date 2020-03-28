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
    return a.exec();
}
