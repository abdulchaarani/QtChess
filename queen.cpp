/**
* Program that defines the movements of the Queen class.
* Queen inherits both from Bishop and Rook
* \file   Queen.cpp
* \author Abdul-Wahab Chaarani 1793305 and Hiba Chaarani 2205674
* \date   5/05/2023
* Created on 9/04/2023
*/

#include "Queen.hpp"

namespace model{
Queen::Queen(Color color, int row, int column)
    :Piece(color, row, column)

{
    color_ == Color::white ? display_ = "♕" : display_ = "♛";
}

void Queen::fillMovements(BoardView board){
    movements_.clear();
    Bishop::fillMovements(board);
    Rook::fillMovements(board);
}
}
