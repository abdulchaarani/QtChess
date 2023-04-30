#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QGuiApplication>
#include "chessboard.hpp"
#include "creditsscreen.hpp"
#include "mainmenu.hpp"

#include "titlescreen.hpp"

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
