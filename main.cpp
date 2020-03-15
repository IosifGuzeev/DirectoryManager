#include <QCoreApplication>
#include "consolemanager.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    ConsoleManager::Start();
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        qDebug() << 'test';
    }
}
