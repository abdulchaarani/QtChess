
#include "chessboard.hpp"

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent)
{

    board_ = new QGridLayout(this);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Box* box = new Box(j, i, this); // !!
            box->setFixedSize(150, 150);
            board_->addWidget(box, i, j);
            connect(box, SIGNAL(released()), this, SLOT(onButtonTrigger()));
            connect(this, SIGNAL(buttonTriggered()), box, SLOT(handleClick()));
        }
    }
}
