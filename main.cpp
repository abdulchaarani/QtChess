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

    mainLayout->addWidget(chessboard);
    // create chessBoard


    // create king object
    King* king = new King(4,4, &mainWindow);
    king->fillMovements();

    // connect king to every box to detect avalid positions
    for (int i{0}; i < chessboard->board_->rowCount(); ++i) {
        for (int j{0}; j <  chessboard->board_->columnCount(); ++j) {
            QWidget* widget =  chessboard->board_->itemAtPosition(i, j)->widget();
            QObject::connect(king, SIGNAL(released()), widget, SLOT(highlightColor()));
        }
    }
    mainWindow.setFixedSize(1200,1200);
    mainWindow.adjustSize();
    mainWindow.show();
    return a.exec();
}
