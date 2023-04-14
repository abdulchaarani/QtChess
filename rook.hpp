
#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook : public Piece
{
    Q_OBJECT

public:
    Rook(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

};
#endif // ROOK_HPP
