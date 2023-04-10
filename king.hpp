
#ifndef KING_HPP
#define KING_HPP

#include "pieces.hpp"

class King : public Piece
{
    Q_OBJECT

public:
    King(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

};

#endif // KING_HPP
