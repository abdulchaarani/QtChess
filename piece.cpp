
#include "piece.hpp"

namespace model{

Piece::Piece(Color color, int row, int column)
    : color_{color}
    , coordinates_{std::make_pair(row, column)} {}

}

