/**
* Program that defines the movements of the Pawn class.
* \file   Pawn.cpp
* \author Abdul-Wahab Chaarani 1793305 and Hiba Chaarani 2205674
* \date   5/05/2023
* Created on 9/04/2023
*/

#include "Pawn.hpp"

namespace model{

Pawn::Pawn(Color color, int row, int column) : Piece(color, row, column)
{
    color_ == Color::white ? display_ = "♙" : display_ = "♟";
    initialPosition_ = {row, column};
}

void Pawn::fillMovements(BoardView board)
{
    movements_.clear();

    auto [row, column] = coordinates_;

    if (firstMove_)
        if (coordinates_ != initialPosition_)
            firstMove_ = false;
    // check above

    if (color_ == Color::white){

        // check above
        if ((row - 1) >= 0)
            if(board[row - 1][column] == nullptr)
                movements_.push_front({row - 1, column});

        if (firstMove_)
            if ((row - 2) >= 0)
                if(board[row - 2][column] == nullptr) // or enemy
                    movements_.push_front({row - 2, column});

        // check diagonal right if ennemy
        if ((row - 1) >= 0 && (column + 1) < 8)
            if(board[row - 1][column + 1] != nullptr && board[row - 1][column + 1]->color_ != color_)
                movements_.push_front({row - 1, column + 1});

        // check diagonal left if ennemy
        if ((row - 1) >= 0 && (column - 1) >= 0)
            if(board[row - 1][column - 1] != nullptr && board[row - 1][column - 1]->color_ != color_)
                movements_.push_front({row - 1, column - 1});
    }


    if (color_ == Color::black){

        if ((row + 1) < 8)
            if(board[row + 1][column] == nullptr)
                movements_.push_front({row + 1, column});

        if (firstMove_)
            if ((row + 2) < 8)
                if(board[row + 2][column] == nullptr) // or enemy
                    movements_.push_front({row + 2, column});

        // check diagonal right if ennemy
        if ((row + 1) < 8 && (column + 1) < 8)
            if(board[row + 1][column + 1] != nullptr && board[row + 1][column + 1]->color_ != color_)
                movements_.push_front({row + 1, column + 1});

        // check diagonal left if ennemy
        if ((row + 1) < 8 && (column - 1) >= 0)
            if(board[row + 1][column - 1] != nullptr && board[row + 1][column - 1]->color_ != color_)
                movements_.push_front({row + 1, column - 1});
    }


}

}
