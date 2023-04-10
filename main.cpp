#include <QApplication>
#include <QObject>
#include <QWidget>

#include "chessboard.hpp"
#include "piece.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "pawn.hpp"

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
    // TODO: UNIT TEST: NO TWO PIECES ON SAME BOX
    chessboard->addPiece<King>(Color::WHITE,0,3);
    chessboard->addPiece<King>(Color::BLACK,4,4);

    chessboard->addPiece<Knight>(Color::WHITE, 5, 3);
    chessboard->addPiece<Knight>(Color::BLACK, 3, 5);

    chessboard->addPiece<Pawn>(Color::WHITE, 6,1);
    chessboard->addPiece<Pawn>(Color::BLACK, 1,1);

    chessboard->addPiece<Rook>(Color::BLACK, 6,7);
    chessboard->addPiece<Rook>(Color::WHITE, 0,0);

    chessboard->addPiece<Bishop>(Color::BLACK, 3,4);
    chessboard->addPiece<Bishop>(Color::WHITE, 2,5);

    chessboard->addPiece<Queen>(Color::WHITE, 2,2);
    chessboard->addPiece<Queen>(Color::BLACK, 1,6);

    chessboard->startGame();

    // add chessboard to UI and caliibrate size
    mainLayout->addWidget(chessboard);
    mainWindow.setFixedSize(1200,1200);
    mainWindow.adjustSize();
    mainWindow.show();
    return a.exec();
}
