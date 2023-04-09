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

void createKing(int x, int y, ChessBoard* chessboard, QWidget& mainWindow){
    King* king = new King(x, y, &mainWindow);
    king->fillMovements();

    // connect king to every box to detect valid positions
    for (int i{0}; i < chessboard->board_->rowCount(); ++i) {
        for (int j{0}; j <  chessboard->board_->columnCount(); ++j) {
            QWidget* widget =  chessboard->board_->itemAtPosition(i, j)->widget();
            if (i == x && j == y)
                king->possessBox(qobject_cast<Box*>(widget));
            QObject::connect(king, SIGNAL(released()), widget, SLOT(highlightColor()));
            QObject::connect(widget, SIGNAL(goTo()), king, SLOT(updatePosition()));
        }
    }
}

void createKnight(int x, int y, ChessBoard* chessboard, QWidget& mainWindow){
    Knight* knight = new Knight(x, y, &mainWindow);
    knight->fillMovements();

    // connect king to every box to detect valid positions
    for (int i{0}; i < chessboard->board_->rowCount(); ++i) {
        for (int j{0}; j <  chessboard->board_->columnCount(); ++j) {
            QWidget* widget =  chessboard->board_->itemAtPosition(i, j)->widget();
            if (i == x && j == y)
                knight->possessBox(qobject_cast<Box*>(widget));
            QObject::connect(knight, SIGNAL(released()), widget, SLOT(highlightColor()));
            QObject::connect(widget, SIGNAL(goTo()), knight, SLOT(updatePosition()));
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget mainWindow;
    QVBoxLayout *mainLayout = new QVBoxLayout(&mainWindow);
    mainWindow.setLayout(mainLayout);

    ChessBoard* chessboard = new ChessBoard(&mainWindow);

    mainLayout->addWidget(chessboard);

    createKing(0, 2, chessboard, mainWindow);
    createKing(0, 3, chessboard, mainWindow);
    createKing(4, 4, chessboard, mainWindow);
    createKnight(3,5, chessboard, mainWindow);

    mainWindow.setFixedSize(1200,1200);
    mainWindow.adjustSize();
    mainWindow.show();
    return a.exec();
}
