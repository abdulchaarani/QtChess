
#ifndef PAWN_HPP
#define PAWN_HPP

#include "piece.hpp"

class Pawn : public Piece
{
    Q_OBJECT

public:
    Pawn(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

private:
    bool firstMove_{true};

private slots:
    void playFirstMove() {firstMove_ = false; }
};

#endif // PAWN_HPP
