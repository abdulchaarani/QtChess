
#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

namespace model{

class Knight : public Piece
{
public:
    Knight(Color color, int row, int column);
    void fillMovements(BoardView board) override;
};

}
#endif // KNIGHT_HPP
