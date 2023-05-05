#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"
namespace model{

class Bishop : virtual public Piece
{
public:
    Bishop(Color color, int row, int column);
    Bishop() = default;
    void fillMovements(BoardView board) override;
};

}
#endif // BISHOP_HPP
