/**
* Program that defines the constructor of the Piece class.
* \file   piece.cpp
* \author Abdul-Wahab et Hiba
* \date   4 mai 2023
* Créé le 9 avril 2023
*/

#include "piece.hpp"

namespace model{

Piece::Piece(Color color, int row, int column)
    : color_{color}
    , coordinates_{std::make_pair(row, column)} {}

}

