
#ifndef ROOK_HPP
#define ROOK_HPP

#include "piece.hpp"

class Rook : public Piece
{
    Q_OBJECT

public:
    Rook(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    Rook(Piece* queen);
    void fillMovements() override;

private:
    bool isQueen_{false};
    Piece* queen_;
};
#endif // ROOK_HPP
