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
    ConsoleManager::Write("Type \'help\' to get a list of all supported comands.");

    return a.exec();
}
