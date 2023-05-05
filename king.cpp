/**
* Program that defines the movement method and constructor of the King class.
* \file   king.cpp
* \author Abdul-Wahab et Hiba
* \date   5 mai 2023
* Créé le 4 mai 2023
*/

#include "king.hpp"

namespace model{

King::King(Color color, int row, int column) : Piece(color, row, column)
{
    color_ == Color::white ? display_ = "♔" : display_ = "♚";
}

void King::fillMovements(BoardView board)
{
    movements.clear();

    int row{coordinates_.first};
    int column{coordinates_.second};

    if ((row + 1) < 8)
        if(board[row + 1][column] == nullptr || board[row + 1][column]->color_ != color_) // or enemy
            movements.push_front({row + 1, column});
    if ((row - 1) >= 0)
        if(board[row - 1][column] == nullptr || board[row - 1][column]->color_ != color_)
            movements.push_front({row - 1, column});
    if ((column + 1) < 8)
        if(board[row][column + 1] == nullptr || board[row][column + 1]->color_ != color_)
            movements.push_front({row, column + 1});
    if ((column - 1 ) >= 0)
        if(board[row][column - 1] == nullptr || board[row][column - 1]->color_ != color_)
            movements.push_front({row, column - 1});

    if ((row + 1) < 8 && (column - 1) >= 0)
        if(board[row + 1][column - 1] == nullptr || board[row + 1][column - 1]->color_ != color_) // or enemy
            movements.push_front({row + 1, column - 1});
    if ((row + 1) < 8 && (column + 1) < 8)
        if(board[row + 1][column + 1] == nullptr || board[row + 1][column + 1]->color_ != color_) // or enemy
            movements.push_front({row + 1, column + 1});
    if ((row - 1) >= 0 && (column - 1) >= 0)
        if(board[row - 1][column - 1] == nullptr || board[row - 1][column - 1]->color_ != color_) // or enemy
            movements.push_front({row - 1, column - 1});
    if ((row - 1) >= 0 && (column + 1) < 8)
        if(board[row - 1][column + 1] == nullptr || board[row - 1][column + 1]->color_ != color_) // or enemy
            movements.push_front({row - 1, column + 1});

}

}
