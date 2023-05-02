
#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "piece.hpp"
#include "bishop.hpp"
#include "rook.hpp"

class Queen : public Piece
{
    Q_OBJECT

public:
    Queen(Color color, int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

    friend class Knight;
private:
/*
    Qt doesnt seem to support multiple heritage very well,
    composition will be used to avoid duplication of methods
*/

    Bishop* bishop_;
    Rook* rook_;
};

#endif // QUEEN_HPP
