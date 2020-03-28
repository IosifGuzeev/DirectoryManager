#include "consolemanager.h"

const QVector<QString> ConsoleManager::comands = {
        "\'help\' - get list of comands",
        "\'ls\' - list of all tracked files",
        "\'lsi\' - ls with additional info about every tracked file",
        "\'add-%path%\' - add file with this path to the list of tracked files",
        "\'delete-%path%\' - delete file with this path from the list of tracked files",
        "\'test-%path%-&count%\' - creates given count of test files in folder with given path",
        "\'remove\' - removes all files created with test comand"
    };

QVector<QString> ConsoleManager::testFiles = {};

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
            for(auto com: comands)
            {
                ConsoleManager::Write(com);
            }
        }
        else if (comand == "remove")
        {
            if (testFiles.count() != 0)
            {
                for(auto &path: testFiles)
                {
                    QFile file(path);
                    file.remove();
                }
                ConsoleManager::Write("All test files is removed");
            }
            else
            {
                ConsoleManager::Write("No test files created yet");
            }
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
    case 3:
    {
        auto path = keyWords[1];
        auto params = keyWords[2];
        if(comand == "test")
        {
            int filesCount;
            try {
                filesCount = params.toInt();
            } catch (...) {
                ConsoleManager::Write("Expected integer as files count parameter!");
            }
            QDir(QDir::homePath()).mkpath(path);
            for(int i = 0; i < filesCount; i++)
            {
                QString filePath = path + "\\" + QString::number(i) + ".txt";
                ConsoleManager::Write(filePath);
                testFiles.append(filePath);
                QFile file(filePath);
                file.open(QIODevice::WriteOnly);
                file.write("This is test file");
                file.close();
            }
            return;
        }
        break;
    }
    default:
    {
        ConsoleManager::Write("Wrong comand!");
        break;
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
    std::terminate();
}

void ConsoleManager::Write(const QString &msg)
{
    auto output = qDebug();
    output.noquote();
    output << msg;
}
