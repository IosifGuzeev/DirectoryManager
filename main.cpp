#include <QCoreApplication>
#include "consolemanager.h"
#include <thread>
#include <QDebug>


int main(int argc, char *argv[])
{
    std::thread reader(ConsoleManager::ConsoleReader);
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        qDebug() << 'test';
    }
    QCoreApplication a(argc, argv);
    return a.exec();
}
