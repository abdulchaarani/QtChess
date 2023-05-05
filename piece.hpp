
#ifndef PIECE_HPP
#define PIECE_HPP

#include "layouts.hpp"
#include <forward_list>
#include <span>

namespace model{

class Piece
{
public:
    Piece(Color color, int row, int column);
    Piece() = default;
    virtual ~Piece() = default;

    Color color_;
    QString display_;
    std::pair<int, int> coordinates_;

    using Coordinates = std::pair<int, int>;
    std::forward_list<Coordinates> movements;

    using BoardView =std::array<std::array<std::shared_ptr<Piece>, 8>, 8>&;
    virtual void fillMovements(BoardView board) = 0;
};

}
#endif // PIECE_HPP
