
#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "Bishop.hpp"
#include "Rook.hpp"

namespace model{

class Queen : public Bishop, public Rook
{
public:
    Queen(Color color, int row, int column);
    void fillMovements(BoardView board) override;
};

}
#endif // QUEEN_HPP
