#include "consolemanager.h"

ConsoleManager::ConsoleManager()
{

}

void ConsoleManager::ParseComand(const QString &comand)
{
    auto keyWords = comand.split('-').toVector();
    if (keyWords.count() != 2)
        ConsoleManager::Write("Wrong keywords count!");
    if(keyWords[0].toLower() == "add" && keyWords[0].toLower() == "del")
    {
        ConsoleManager::Write("Wrong comand!");
        return;
    }
    if (keyWords[0].toLower() == "add")
    {
        DirectoryManager::AddFiles(QVector<QString>({keyWords[1]}));
    }
    else
    {
        DirectoryManager::DeleteFiles(QVector<QString>({keyWords[1]}));
    }
    qDebug() << "New files list:";
    DirectoryManager::PrintFiles();
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
    qDebug() << msg;
}
