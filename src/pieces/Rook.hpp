
#ifndef ROOK_HPP
#define ROOK_HPP

#include "Piece.hpp"

namespace model{

class Rook : virtual public Piece
{
public:
    Rook(Color color, int row, int column);
    Rook() = default;
    void fillMovements(BoardView board) override;
};

}

#endif // ROOK_HPP
