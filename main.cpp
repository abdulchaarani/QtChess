#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include "box.hpp"
#include "pieces.hpp"
#include "chessboard.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget mainWindow;
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);
    mainWindow.setLayout(mainLayout);

    ChessBoard* chessboard = new ChessBoard(&mainWindow);

    chessboard->addKing(0,2);
    chessboard->addKing(0,3);
    chessboard->addKing(4,4);
    chessboard->addKnight(5,3);

    mainLayout->addWidget(chessboard);
    mainWindow.setFixedSize(1200,1200);
    mainWindow.adjustSize();
    mainWindow.show();
    return a.exec();
}
