
#include "king.hpp"
#include "chessboard.hpp"

King::King(Color color, int row,  int column, ChessBoard* board, QWidget* parent)
    : Piece(color, row, column, board, parent)
{
    // WARNING: TWO DIFFERENT COLORS OF PIECE
//    color_ == Color::WHITE ? setText("♔") : setText("♚");
    if(color_ == Color::WHITE) {
        setText("♔");
        board->whiteKing = this;
    }
    else {
        setText("♚");
        board->blackKing = this;
    }

    changePosition(row, column);
}


// Error bound checking
void King::fillMovements(){ // to beautify :(
    movements.clear();

    int row{coordinates_.getRow()};
    int column{coordinates_.getColumn()};

    if ((row + 1) < 8)
        if(chessboard_->board_[row + 1][column] == nullptr || chessboard_->board_[row + 1][column]->color_ != color_) // or enemy
            movements.push_back(Point(row + 1, column));
    if ((row - 1) >= 0)
        if(chessboard_->board_[row - 1][column] == nullptr || chessboard_->board_[row - 1][column]->color_ != color_)
            movements.push_back(Point(row - 1, column));
    if ((column + 1) < 8)
        if(chessboard_->board_[row][column + 1] == nullptr || chessboard_->board_[row][column + 1]->color_ != color_)
            movements.push_back(Point(row, column + 1));
    if ((column - 1 ) >= 0)
        if(chessboard_->board_[row][column - 1] == nullptr || chessboard_->board_[row][column - 1]->color_ != color_)
            movements.push_back(Point(row, column - 1));
}
