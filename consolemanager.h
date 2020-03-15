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


class ConsoleManager
{
private:
    ConsoleManager();

    static void ParseComand(const QString&comand)
    {
        auto keyWords = comand.split('-').toVector();
        if (keyWords.count() != 2)
            ConsoleManager::Write("Wrong keywords count!");
        if (keyWords[1].toLower() == "add")
        {

        }
    }

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
            ParseComand(command.c_str());
        }
    }

    void static Write(const QString &msg)
    {
        qDebug() << msg;
    }

};

#endif // CONSOLEMANAGER_H
