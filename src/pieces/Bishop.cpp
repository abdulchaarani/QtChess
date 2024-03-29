/**
* Program that defines the movements of a Bishop.
* Queen inherits from bishop
* \file   Bishop.cpp
* \author Abdul-Wahab Chaarani 1793305 and Hiba Chaarani 2205674
* \date   5/05/2023
* Created on 9/04/2023
*/

#include "Bishop.hpp"

namespace model{

Bishop::Bishop(Color color, int row, int column) : Piece(color, row, column)
{
    color_ == Color::white ? display_ = "♗" : display_ = "♝";
}


void Bishop::fillMovements(BoardView board)
{
    // if not a queen, since queens inherit from bishop
    // and shares same instance of movements
    if (display_ != "♕" && display_ != "♛")
        movements_.clear();

    auto [row, column] = coordinates_;
    // check south-east
    for (int nextRow{row + 1}, nextColumn{column + 1}; nextRow < 8 && nextColumn < 8; ++nextRow, ++nextColumn){

        if (board[nextRow][nextColumn] == nullptr) // if no one, add
            movements_.push_front({nextRow, nextColumn});

        else // if somone
            if (board[nextRow][nextColumn]->color_ != color_){ // enemy in sight?
                movements_.push_front({nextRow, nextColumn}); // add enemy to list
                break; // stop adding
            }
            else if (board[nextRow][nextColumn]->color_ == color_) // if friendly
                break; // stop adding
    }

    // check south-west
    for (int nextRow{row + 1}, nextColumn{column - 1}; nextRow < 8 && nextColumn >= 0; ++nextRow, --nextColumn){

        if (board[nextRow][nextColumn] == nullptr) // if no one, add
            movements_.push_front({nextRow, nextColumn});

        else // if somone
            if (board[nextRow][nextColumn]->color_ != color_){ // enemy in sight?
                movements_.push_front({nextRow, nextColumn}); // add enemy to list
                break; // stop adding
            }
            else if (board[nextRow][nextColumn]->color_ == color_) // if friendly
                break; // stop adding
    }

    // check north-west
    for (int nextRow{row - 1}, nextColumn{column - 1}; nextRow >= 0 && nextColumn >= 0; --nextRow, --nextColumn){

        if (board[nextRow][nextColumn] == nullptr) // if no one, add
            movements_.push_front({nextRow, nextColumn});

        else // if somone
            if (board[nextRow][nextColumn]->color_ != color_){ // enemy in sight?
                movements_.push_front({nextRow, nextColumn}); // add enemy to list
                break; // stop adding
            }
            else if (board[nextRow][nextColumn]->color_ == color_) // if friendly
                break; // stop adding
    }

    // check north-east
    for (int nextRow{row - 1}, nextColumn{column + 1}; nextRow >= 0 && nextColumn < 8; --nextRow, ++nextColumn){

        if (board[nextRow][nextColumn] == nullptr) // if no one, add
            movements_.push_front({nextRow, nextColumn});

        else // if somone
            if (board[nextRow][nextColumn]->color_ != color_){ // enemy in sight?
                movements_.push_front({nextRow, nextColumn}); // add enemy to list
                break; // stop adding
            }
            else if (board[nextRow][nextColumn]->color_ == color_) // if friendly
                break; // stop adding
    }

}
}
