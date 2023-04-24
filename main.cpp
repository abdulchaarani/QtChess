#include <QApplication>
#include <QObject>
#include <QWidget>

#include "chessboard.hpp"
#include "creditsscreen.h"
#include "mainmenu.h"
#include "titlescreen.h"

int main(int argc, char* argv[]) {
    // necessary or program wont run
    QApplication a(argc, argv);

    // create main UI window
    QMainWindow mainWindow;
    MainMenu* mainMenu = new MainMenu(&mainWindow);
    mainMenu->setFixedSize(800, 800);
    mainMenu->show();
    //    QVBoxLayout* mainLayout = new QVBoxLayout(&mainWindow);

    //    mainWindow.setLayout(mainLayout);

    //    auto screens = QGuiApplication::screens;

    // create chessboard
    //    ChessBoard* chessboard = new ChessBoard(&mainWindow);

    //    TitleScreen* titleScreen = new TitleScreen(&mainWindow);
    //    QString test = "Hibooboo & Abdoodoo";
    //    CreditsScreen* creditsScreen = new CreditsScreen(test, &mainWindow);

    // add pieces to chessboard
    // TODO: UNIT TEST: NO TWO PIECES ON SAME BOX
    //    chessboard->addPiece<King>(Color::WHITE,0,3);
    //    chessboard->addPiece<King>(Color::BLACK,7,5);

    //    chessboard->addPiece<Knight>(Color::WHITE, 5, 3);
    //    chessboard->addPiece<Knight>(Color::BLACK, 3, 5);

    //    chessboard->addPiece<Pawn>(Color::WHITE, 6,2);
    //    chessboard->addPiece<Pawn>(Color::BLACK, 1,1);

    //    chessboard->addPiece<Rook>(Color::BLACK, 6,7);
    //    chessboard->addPiece<Rook>(Color::WHITE, 0,0);

    //    chessboard->addPiece<Bishop>(Color::BLACK, 3,4);
    //    chessboard->addPiece<Bishop>(Color::WHITE, 2,5);

    //    chessboard->addPiece<Queen>(Color::WHITE, 2,2);
    //    chessboard->addPiece<Queen>(Color::BLACK, 1,6);

    //    chessboard->startGame();

    // add chessboard to UI and caliibrate size
    //    mainLayout->addWidget(creditsScreen);
    //    mainWindow/*.setFixedSize(800,800);*/
    //    mainWindow.adjustSize();
    //    mainWindow.show();
    //    titleScreen->show();
    //    creditsScreen->show();
    return a.exec();
}
