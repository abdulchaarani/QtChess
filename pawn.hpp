
#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece{
public:
    Pawn(Color color, int row, int column);
    void fillMovements(BoardView board) override;
    Coordinates initialPosition_;
private:
    bool firstMove_{true};
};

#endif // PAWN_HPP
