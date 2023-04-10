
#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "piece.hpp"

class Knight : public Piece
{
    Q_OBJECT

public:
    Knight(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

};
#endif // KNIGHT_HPP
