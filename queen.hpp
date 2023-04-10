
#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"
#include "rook.hpp"
#include "bishop.hpp"

class Queen : public Rook, public Bishop
{
    Q_OBJECT

public:
    Queen(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

};

#endif // QUEEN_HPP
