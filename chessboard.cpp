
#include "chessboard.hpp"

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent)
{

    board_ = new QGridLayout(this);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Box* box = new Box(col, row, this); // !!
            box->setFixedSize(150, 150);
            board_->addWidget(box, row, col);
            connect(box, SIGNAL(released()), this, SLOT(onButtonTrigger()));
            connect(this, SIGNAL(buttonTriggered()), box, SLOT(handleClick()));
        }
    }
}
