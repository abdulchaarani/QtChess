
#include "pawn.hpp"
#include "chessboard.hpp"

Pawn::Pawn(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
    : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::WHITE ? setText("♙") : setText("♟");
    changePosition(row, column);
    connect(this, SIGNAL(playedFirstMove()), this, SLOT(playFirstMove()));
}

// Error bound checking
void Pawn::fillMovements(){ // to beautify :(
    movements.clear();

    int row{coordinates_.getRow()};
    int column{coordinates_.getColumn()};

    // check above

    if (color_ == Color::WHITE){

        // check above
        if ((row - 1) >= 0)
            if(chessboard_->board_[row - 1][column] == nullptr)
                movements.push_back(Point(row - 1, column));

        if (firstMove_)
            if ((row - 2) >= 0)
                if(chessboard_->board_[row - 2][column] == nullptr) // or enemy
                    movements.push_back(Point(row - 2, column));

        // check diagonal right if ennemy
        if ((row - 1) >= 0 && (column + 1) < 8)
            if(chessboard_->board_[row - 1][column + 1] != nullptr && chessboard_->board_[row - 1][column + 1]->color_ != color_)
                movements.push_back(Point(row - 1, column + 1));

        // check diagonal left if ennemy
        if ((row - 1) >= 0 && (column - 1) >= 0)
            if(chessboard_->board_[row + 1][column - 1] != nullptr && chessboard_->board_[row + 1][column - 1]->color_ != color_)
                movements.push_back(Point(row - 1, column - 1));
    }


    if (color_ == Color::BLACK){

        if ((row + 1) < 8)
            if(chessboard_->board_[row + 1][column] == nullptr)
                movements.push_back(Point(row + 1, column));

        if (firstMove_)
            if ((row + 2) < 8)
                if(chessboard_->board_[row + 2][column] == nullptr) // or enemy
                    movements.push_back(Point(row + 2, column));

        // check diagonal right if ennemy
        if ((row + 1) < 8 && (column + 1) < 8)
            if(chessboard_->board_[row + 1][column + 1] != nullptr && chessboard_->board_[row + 1][column + 1]->color_ != color_)
                movements.push_back(Point(row + 1, column + 1));

        // check diagonal left if ennemy
        if ((row + 1) < 8 && (column - 1) >= 0)
            if(chessboard_->board_[row + 1][column - 1] != nullptr && chessboard_->board_[row + 1][column - 1]->color_ != color_)
                movements.push_back(Point(row + 1, column - 1));
    }


}
