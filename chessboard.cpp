
#include "chessboard.hpp"

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), parent_(parent)
{

    grid_ = new QGridLayout(this);

    for (int row = 0; row < 8; ++row) {
        for (int column = 0; column < 8; ++column) {
            Box* box = new Box(row, column, this); // !!
            box->setFixedSize(150, 150);
            grid_->addWidget(box, row, column);
            connect(box, SIGNAL(released()), this, SLOT(onButtonTrigger()));
            connect(this, SIGNAL(buttonTriggered()), box, SLOT(handleClick()));
        }
    }
}


void ChessBoard::changePlayer(){
    if (currentPlayer == WHITE) {
        currentPlayer = BLACK;
        qDebug() << "BLACK";
    } else {
        currentPlayer = WHITE;
        qDebug() << "WHITE";
    }
}

void ChessBoard::startGame(){
    currentPlayer = WHITE;
}
