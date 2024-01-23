#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

namespace model{

class Pawn : public Piece{
public:
    Pawn(Color color, int row, int column);
    void fillMovements(BoardView board) override;
    Coordinates initialPosition_;
private:
    bool firstMove_{true};
};

}
#endif // PAWN_HPP
