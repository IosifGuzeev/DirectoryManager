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
///
/// Класс, отвечающий на работу с консолью (вывод информации и считывание команд).
/// Поддерживает команды:
/// 1) add-%path%
/// 2) del-%path%
class DirectoryManager;
class ConsoleManager
{
private:
    ConsoleManager();
    static void ConsoleReader();   //Простейшие считывание с консоли.
    static void ParseComand(const QString&comand); //Принимает строку и, исходя из её вида, производит какие-либо действия и выводит информацию.

public:


    void static Start();    //Основная функция, запускает работу класса в отдельном потоке.

    void static Write(const QString &msg);  //Вывод msg на консоль.

};

#endif // CONSOLEMANAGER_H
