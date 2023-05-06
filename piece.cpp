/**
* Program that defines the abstract class Piece
* which all the other pieces inherit from
* \file   Piece.cpp
* \author Abdul-Wahab Chaarani 1793305 and Hiba Chaarani 2205674
* \date   5/05/2023
* Created on 9/04/2023
*/

#include "Piece.hpp"

namespace model{

Piece::Piece(Color color, int row, int column)
    : color_{color}
    , coordinates_{std::make_pair(row, column)} {}

}

