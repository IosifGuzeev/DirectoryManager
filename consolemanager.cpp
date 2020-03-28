#include "consolemanager.h"

ConsoleManager::ConsoleManager()
{

}

void ConsoleManager::ParseComand(const QString &input)
{
    auto keyWords = input.split('-').toVector();

    if(keyWords.count() == 0)
    {
        ConsoleManager::Write("Wrong comand");
        return;
    }
    for(auto &s: keyWords)
    {
        if (s.length() == 0)
        {
            ConsoleManager::Write("Wrong comand");
            return;
        }
    }

    auto comand = keyWords[0].toLower();
    switch (keyWords.count())
    {
    case 1:
    {
        if (comand == "ls")
        {
            DirectoryManager::PrintFiles(false);
        }
        else if(comand == "lsi")
        {
            DirectoryManager::PrintFiles(true);
        }
        else if (comand == "help")
        {
            ConsoleManager::Write("\'help\' - get list of comands");
            ConsoleManager::Write("\'ls\' - list of all tracked files");
            ConsoleManager::Write("\'lsi\' - ls with additional info about every tracked file");
            ConsoleManager::Write("\'add-%path%\' - add file with this path to the list of tracked files");
            ConsoleManager::Write("\'delete-%path%\' - delete file with this path from the list of tracked files");
        }
        else
        {
            ConsoleManager::Write("Wrong comand!");
            return;
        }
        break;
    }
    case 2:
    {
        auto path = keyWords[1];
        if (comand == "add")
        {
            DirectoryManager::AddFiles(QVector<QString>({path}));
        }
        else if (comand == "delete")
        {
            DirectoryManager::DeleteFiles(QVector<QString>({path}));
        }
        else
        {
            ConsoleManager::Write("Wrong comand!");
            return;
        }
        break;
    }
    default:
    {
        ConsoleManager::Write("Wrong comand!");
    }
    }
}

void ConsoleManager::Start()
{
    std::thread reader(ConsoleManager::ConsoleReader);
    reader.detach();
}

void ConsoleManager::ConsoleReader()
{
    std::string command;
    while (true)
    {
        std::cin >> command;
        ParseComand(command.c_str());
    }
}

void ConsoleManager::Write(const QString &msg)
{
    auto output = qDebug();
    output.noquote();
    output << msg;
}
