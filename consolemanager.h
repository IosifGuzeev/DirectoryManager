#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <iostream>
#include <string>
#include <thread>
#include "directorymanager.h"

class ConsoleManager
{
private:
    ConsoleManager();
public:
    void static Start()
    {
        std::thread reader(ConsoleManager::ConsoleReader);
        reader.detach();
    }

    static void ConsoleReader()
    {
        std::string command;
        while (true)
        {
            std::cin >> command;
            qDebug() << QString(command.c_str());
        }
    }

    void static Write(const QString &msg)
    {
        qDebug() << msg;
    }

};

#endif // CONSOLEMANAGER_H
