#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "box.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget mainWindow;

    QGridLayout* chessBoard = new QGridLayout;

    for (int i{0}; i < 8; ++i){
        for(int j{0}; j < 8; ++j){
            Box* box = new Box(j, i, &mainWindow);
            box->setFixedSize(150, 150);
            chessBoard->addWidget(box, i, j);
        }
    }
    mainWindow.setLayout(chessBoard);
    mainWindow.setFixedSize(1200,1200);
    mainWindow.adjustSize();
    mainWindow.show();
    return a.exec();
}
