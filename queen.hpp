
#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "bishop.hpp"
#include "rook.hpp"

namespace model{

class Queen : public Bishop, public Rook
{
public:
    Queen(Color color, int row, int column);
    void fillMovements(BoardView board) override;
};

}
#endif // QUEEN_HPP
