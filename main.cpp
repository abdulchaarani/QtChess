#include <QApplication>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QObject>
#include <QWidget>

#include "chessboard.hpp"

int main(int argc, char *argv[]) {
    // necessary or program wont run
    QApplication a(argc, argv);

    QMainWindow mainWindow;
    QWidget *mainLayout = new QWidget(&mainWindow);
    mainWindow.setCentralWidget(mainLayout);

    // ChessBoard* chessboard = new ChessBoard(mainLayout);

    QMenuBar *menuBar = new QMenuBar(&mainWindow);
    mainWindow.setMenuBar(menuBar);

    QMenu *gameMenu = menuBar->addMenu("&Games");

    QAction *newGameAction = new QAction("&New game", &mainWindow);
    gameMenu->addAction(newGameAction);

    QAction *quitAction = new QAction("&Quit", &mainWindow);
    gameMenu->addAction(quitAction);

    QObject::connect(quitAction, &QAction::triggered, &mainWindow, &QMainWindow::close);

    QObject::connect(newGameAction, &QAction::triggered, &ChessBoard::getInstance);

    ChessBoard::setParent(mainLayout);
    // ChessBoard::getInstance();
    //  create chessboard
    // chessboard->testGame();
    // QVBoxLayout* mainLayout = new QVBoxLayout(&mainWindow);
    // mainLayout.addLayout(chessboard);

    // add pieces to chessboard

    // add chessboard to UI and caliibrate size

    mainWindow.setFixedSize(820, 840);
    mainWindow.adjustSize();
    mainWindow.show();
    return a.exec();
}
