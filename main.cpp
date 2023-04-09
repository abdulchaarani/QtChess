#include <QApplication>
#include <QObject>
#include <QWidget>

#include "pieces.hpp"
#include "chessboard.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget mainWindow;
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);
    mainWindow.setLayout(mainLayout);

    ChessBoard* chessboard = new ChessBoard(&mainWindow);

    chessboard->addPiece<King>(0,2);
    chessboard->addPiece<King>(0,3);
    chessboard->addPiece<King>(4,4);

    chessboard->addPiece<Knight>(5, 3);

    chessboard->addPiece<Pawn>(6,1);

    chessboard->startGame();

    mainLayout->addWidget(chessboard);
    mainWindow.setFixedSize(1200,1200);
    mainWindow.adjustSize();
    mainWindow.show();
    return a.exec();
}
