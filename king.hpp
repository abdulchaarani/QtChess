
#ifndef KING_HPP
#define KING_HPP

#include "piece.hpp"

namespace model{

class King : public Piece
{
public:
    King(Color color, int row, int column);
    void fillMovements(BoardView board) override;
    bool isChecked_{false};
};

}
#endif // KING_HPP
