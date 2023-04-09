
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

//TO TEMPLATE BELOW//

void ChessBoard::addKing(int row, int column){
    King* king = new King(row, column, this, parent_);
    king->fillMovements();

    // connect king to every box to detect valid positions
    for (int i{0}; i < grid_->rowCount(); ++i) {
        for (int j{0}; j <  grid_->columnCount(); ++j) {
            QWidget* widget =  grid_->itemAtPosition(i, j)->widget();
            if (i == row && j == column)
                king->possessBox(qobject_cast<Box*>(widget));
            QObject::connect(king, SIGNAL(released()), widget, SLOT(highlightColor()));
            QObject::connect(widget, SIGNAL(goTo()), king, SLOT(updatePosition()));
        }
    }
}

void ChessBoard::addKnight(int row, int column){
    Knight* knight = new Knight(row, column, this, parent_);
    knight->fillMovements();

    // connect knight to every box to detect valid positions
    for (int i{0}; i < grid_->rowCount(); ++i) {
        for (int j{0}; j <  grid_->columnCount(); ++j) {
            QWidget* widget =  grid_->itemAtPosition(i, j)->widget();
            if (i == row && j == column)
                knight->possessBox(qobject_cast<Box*>(widget));
            QObject::connect(knight, SIGNAL(released()), widget, SLOT(highlightColor()));
            QObject::connect(widget, SIGNAL(goTo()), knight, SLOT(updatePosition()));
        }
    }
}


//DEBUG ONLY//

