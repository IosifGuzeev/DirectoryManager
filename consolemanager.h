#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H
#include <QObject>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <directorymanager.h>

class DirectoryManager;
class ConsoleManager
{
private:
    ConsoleManager();

    static void ParseComand(const QString&comand);

public:


    void static Start();

    static void ConsoleReader();

    void static Write(const QString &msg);

};

#endif // CONSOLEMANAGER_H
