
#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"

class Bishop : public Piece
{
    Q_OBJECT

public:
    Bishop(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

};

#endif // BISHOP_HPP
