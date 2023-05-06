/**
* Program that defines the movements of the King class.
* \file   King.cpp
* \author Abdul-Wahab Chaarani 1793305 and Hiba Chaarani 2205674
* \date   5/05/2023
* Created on 9/04/2023
*/

#include "King.hpp"

namespace model{

King::King(Color color, int row, int column) : Piece(color, row, column)
{
    color_ == Color::white ? display_ = "♔" : display_ = "♚";
}

void King::fillMovements(BoardView board)
{
    movements_.clear();

    int row{coordinates_.first};
    int column{coordinates_.second};

    if ((row + 1) < 8)
        if(board[row + 1][column] == nullptr || board[row + 1][column]->color_ != color_) // or enemy
            movements_.push_front({row + 1, column});
    if ((row - 1) >= 0)
        if(board[row - 1][column] == nullptr || board[row - 1][column]->color_ != color_)
            movements_.push_front({row - 1, column});
    if ((column + 1) < 8)
        if(board[row][column + 1] == nullptr || board[row][column + 1]->color_ != color_)
            movements_.push_front({row, column + 1});
    if ((column - 1 ) >= 0)
        if(board[row][column - 1] == nullptr || board[row][column - 1]->color_ != color_)
            movements_.push_front({row, column - 1});

    if ((row + 1) < 8 && (column - 1) >= 0)
        if(board[row + 1][column - 1] == nullptr || board[row + 1][column - 1]->color_ != color_) // or enemy
            movements_.push_front({row + 1, column - 1});
    if ((row + 1) < 8 && (column + 1) < 8)
        if(board[row + 1][column + 1] == nullptr || board[row + 1][column + 1]->color_ != color_) // or enemy
            movements_.push_front({row + 1, column + 1});
    if ((row - 1) >= 0 && (column - 1) >= 0)
        if(board[row - 1][column - 1] == nullptr || board[row - 1][column - 1]->color_ != color_) // or enemy
            movements_.push_front({row - 1, column - 1});
    if ((row - 1) >= 0 && (column + 1) < 8)
        if(board[row - 1][column + 1] == nullptr || board[row - 1][column + 1]->color_ != color_) // or enemy
            movements_.push_front({row - 1, column + 1});

}

}
