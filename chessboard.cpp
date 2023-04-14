
#include "chessboard.hpp"

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent), parent_(parent)
{

    // creates a 8x8 grid of boxes and connects correct signals

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



void ChessBoard::check() {
    int whiteCount{0};
    int blackCount{0};
    if(currentPlayer == Color::WHITE) {
        // For every black piece
        for(auto&& piece : blackPieces)
            // For every possible black piece move
            for(auto&& move : piece->movements)
                // Check if white king is in future possible black moves
                if(move == whiteKing->getCoordinates())
                {
//                    emit whiteKing->isChecked(true);
                    whiteCount++;
                }
                else
                    emit whiteKing->isChecked(false);
        if(whiteCount > 0) { emit whiteKing->isChecked(true);}
        connect(whiteKing, &King::isChecked, this, &ChessBoard::onKingChecked);
    }
    else if(currentPlayer == Color::BLACK) {
        for(auto&& piece : whitePieces)
            for(auto&& move : piece->movements)
                if(move == blackKing->getCoordinates())
                {
//                    emit blackKing->isChecked(true);
                    blackCount++;
                }
                else
                    emit blackKing->isChecked(false);
        // Placeholder solution. Will find something better soon...
        if(blackCount > 0) { emit blackKing->isChecked(true);}
        connect(blackKing, &King::isChecked, this, &ChessBoard::onKingChecked);
        }
}

 // to alternate playes every move
void ChessBoard::changePlayer(){
    if (currentPlayer == Color::WHITE) {
        currentPlayer = Color::BLACK;
        qDebug() << "BLACK";
    } else {
        currentPlayer = Color::WHITE;
        qDebug() << "WHITE";
    }
}

void ChessBoard::onKingChecked(bool checked)
{
    if (checked) {
        QPushButton* button = dynamic_cast<QPushButton*>(sender());
        if (button) {
            qDebug() << "trying to change yellow";
            button->setStyleSheet("QPushButton{"
                                  "  color: yellow;"
                                  "  background-color: none;"
                                  "  border-style: inset;"
                                  "  }"
                                  "QPushButton:pressed {"
                                  "   border-style: inset;"
                                  "}");
        }
    } else {
        QPushButton* button = dynamic_cast<QPushButton*>(sender());
        if (button) {
            qDebug() << "Im switching back";
            button->setStyleSheet("QPushButton{"
                                  "  background-color: none;"
                                  "  border-style: inset;"
                                  "  }"
                                  "QPushButton:pressed {"
                                  "   border-style: inset;"
                                  "}");
        }
    }
}


void ChessBoard::startGame(){
    currentPlayer = Color::WHITE;
}
