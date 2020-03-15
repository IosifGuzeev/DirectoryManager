#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <iostream>
#include <string>

class ConsoleManager
{
private:
    ConsoleManager();
public:
    ConsoleManager &GetInstange()
    {
        auto manager = ConsoleManager();
        return manager;
    }
    static void ConsoleReader()
    {
        while (true)
        {
            std::string value;
            std::cin >> value;
            qDebug() << QString(value.c_str());
        }
    }

};

#endif // CONSOLEMANAGER_H
