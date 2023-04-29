#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QGuiApplication>
#include "chessboard.hpp"
#include "creditsscreen.h"
#include "mainmenu.h"

#include "titlescreen.h"

int main(int argc, char *argv[])
{
    // necessary or program wont run
    QApplication a(argc, argv);

    // create main UI window
    MainMenu* mainMenu = new MainMenu();
    mainMenu->setFixedSize(820,850);
    mainMenu->show();
    return a.exec();
}
