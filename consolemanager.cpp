#include "consolemanager.h"

ConsoleManager::ConsoleManager()
{

}

void ConsoleManager::ParseComand(const QString &comand)
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
        ConsoleManager::Write("\'add-%path%\' - add file with this path to the list of tracked files");
        ConsoleManager::Write("\'delete-%path%\' - delete file with this path from the list of tracked files");
    }
    else
    {
        auto keyWords = comand.split('-').toVector();
        if (keyWords.count() != 2)
        {
            ConsoleManager::Write("Wrong keywords count!");
            return;
        }
        if (keyWords[0].toLower() == "add")
        {
            DirectoryManager::AddFiles(QVector<QString>({keyWords[1]}));
        }
        else if (keyWords[0].toLower() == "delete")
        {
            DirectoryManager::DeleteFiles(QVector<QString>({keyWords[1]}));
        }
        else
        {
            ConsoleManager::Write("Wrong comand!");
            return;
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
