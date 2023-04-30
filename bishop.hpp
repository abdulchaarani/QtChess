
#ifndef BISHOP_HPP
#define BISHOP_HPP

#include "piece.hpp"

class Bishop : public Piece
{
    Q_OBJECT

public:
    Bishop(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    Bishop(Piece* queen);
    void fillMovements() override;

private:
    bool isQueen_{false};
    Piece* queen_;

};

#endif // BISHOP_HPP
