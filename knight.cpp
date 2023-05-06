/**
* Program that defines the movements of the Knight class.
* \file   Knight.cpp
* \author Abdul-Wahab et Hiba
* \date   5 mai 2023
* Créé le 9 avril 2023
*/

#include "knight.hpp"

namespace model{

Knight::Knight(Color color, int row, int column) : Piece(color, row, column)
{
    color_ == Color::white ? display_ = "♘" : display_ = "♞";
}

void Knight::fillMovements(BoardView board)
{
    movements_.clear();

    auto [row, column] = coordinates_;

    if (((row + 1) < 8) && ((column + 2) < 8))
        if(board[row + 1][column + 2] == nullptr || board[row + 1][column + 2]->color_ != color_)
            movements_.push_front({row + 1, column + 2});
    if (((row + 1) < 8) && ((column - 2) >= 0))
        if(board[row + 1][column - 2] == nullptr || board[row + 1][column - 2]->color_ != color_)
            movements_.push_front({row + 1, column - 2});
    if (((row - 1) >= 0) && ((column + 2) < 8))
        if(board[row - 1][column + 2] == nullptr || board[row - 1][column + 2]->color_ != color_)
            movements_.push_front({row - 1, column + 2});
    if (((row - 1) >= 0) && ((column - 2) >= 0))
        if(board[row - 1][column - 2] == nullptr || board[row - 1][column - 2]->color_ != color_)
            movements_.push_front({row - 1, column - 2});
    if (((row + 2) < 8) && ((column + 1) < 8))
        if(board[row + 2][column + 1] == nullptr || board[row + 2][column + 1]->color_ != color_)
            movements_.push_front({row + 2, column + 1});
    if (((row + 2) < 8) && ((column - 1) >= 0))
        if(board[row + 2][column - 1] == nullptr || board[row + 2][column - 1]->color_ != color_)
            movements_.push_front({row + 2, column - 1});
    if (((row - 2) >= 0) && ((column + 1) < 8))
        if(board[row - 2][column + 1] == nullptr || board[row - 2][column + 1]->color_ != color_)
            movements_.push_front({row - 2, column + 1});
    if (((row - 2) >= 0) && ((column - 1) >= 0))
        if(board[row - 2][column - 1] == nullptr || board[row - 2][column - 1]->color_ != color_)
            movements_.push_front({row - 2, column - 1});

}

}
