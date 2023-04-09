#include <QApplication>
#include <QObject>
#include <QWidget>

#include "pieces.hpp"
#include "chessboard.hpp"

int main(int argc, char *argv[])
{
    // necessary or program wont run
    QApplication a(argc, argv);

    // create main UI window
    QWidget mainWindow;
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);
    mainWindow.setLayout(mainLayout);

    // create chessboard
    ChessBoard* chessboard = new ChessBoard(&mainWindow);

    // add pieces to chessboard
    chessboard->addPiece<King>(Color::WHITE, 0,2);
    chessboard->addPiece<King>(Color::WHITE,0,3);
    chessboard->addPiece<King>(Color::BLACK,4,4);

    chessboard->addPiece<Knight>(Color::WHITE, 5, 3);

    chessboard->addPiece<Pawn>(Color::WHITE, 6,1);

    chessboard->startGame();

    // add chessboard to UI and caliibrate size
    mainLayout->addWidget(chessboard);
    mainWindow.setFixedSize(1200,1200);
    mainWindow.adjustSize();
    mainWindow.show();
    return a.exec();
}
