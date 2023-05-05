/**
* Program that defines the movements method and constructor of the Queen class.
* \file   queen.cpp
* \author Abdul-Wahab et Hiba
* \date   4 mai 2023
* Créé le 9 avril 2023
*/

#include "queen.hpp"
namespace model{
Queen::Queen(Color color, int row, int column)
    :Piece(color, row, column)

{
    color_ == Color::white ? display_ = "♕" : display_ = "♛";
}

void Queen::fillMovements(BoardView board){
    movements.clear();
    Bishop::fillMovements(board);
    Rook::fillMovements(board);
}
}
