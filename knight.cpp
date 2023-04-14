
#include "knight.hpp"
#include "chessboard.hpp"

Knight::Knight(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
    : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
    color_ == Color::WHITE ? setText("♘") : setText("♞");
    changePosition(row, column);
}

// Error bound checking
void Knight::fillMovements(){// to beautify :(
    movements.clear();

    int row{coordinates_.getRow()};
    int column{coordinates_.getColumn()};

    if (((row + 1) < 8) && ((column + 2) < 8))
        if(chessboard_->board_[row + 1][column + 2] == nullptr || chessboard_->board_[row + 1][column + 2]->color_ != color_)
            movements.push_back(Point(row + 1, column + 2));
    if (((row + 1) < 8) && ((column - 2) >= 0))
        if(chessboard_->board_[row + 1][column - 2] == nullptr || chessboard_->board_[row + 1][column - 2]->color_ != color_)
            movements.push_back(Point(row + 1, column - 2));
    if (((row - 1) >= 0) && ((column + 2) < 8))
        if(chessboard_->board_[row - 1][column + 2] == nullptr || chessboard_->board_[row - 1][column + 2]->color_ != color_)
            movements.push_back(Point(row - 1, column + 2));
    if (((row - 1) >= 0) && ((column - 2) >= 0))
        if(chessboard_->board_[row - 1][column - 2] == nullptr || chessboard_->board_[row - 1][column - 2]->color_ != color_)
            movements.push_back(Point(row - 1, column - 2));
    if (((row + 2) < 8) && ((column + 1) < 8))
        if(chessboard_->board_[row + 2][column + 1] == nullptr || chessboard_->board_[row + 2][column + 1]->color_ != color_)
            movements.push_back(Point(row + 2, column + 1));
    if (((row + 2) < 8) && ((column - 1) >= 0))
        if(chessboard_->board_[row + 2][column - 1] == nullptr || chessboard_->board_[row + 2][column - 1]->color_ != color_)
            movements.push_back(Point(row + 2, column - 1));
    if (((row - 2) >= 0) && ((column + 1) < 8))
        if(chessboard_->board_[row - 2][column + 1] == nullptr || chessboard_->board_[row - 2][column + 1]->color_ != color_)
            movements.push_back(Point(row - 2, column + 1));
    if (((row - 2) >= 0) && ((column - 1) >= 0))
        if(chessboard_->board_[row - 2][column - 1] == nullptr || chessboard_->board_[row - 2][column - 1]->color_ != color_)
            movements.push_back(Point(row - 2, column - 1));
}

