
#ifndef PIECES_HPP
#define PIECES_HPP


#include <QObject>
#include <QPushButton>
#include "point.hpp"
#include <list>

class Piece : public QPushButton
{
    Q_OBJECT

public:
    Piece(int row, int column,  QWidget *parent = nullptr);
    virtual ~Piece() = default;

    void changePosition(int row, int column);
    std::list<Point> movements;

    Point& getCoordinates();


    virtual void fillMovements() = 0;

protected:
    Point coordinates_;

};

class King : public Piece
{
    Q_OBJECT

public:
    King(int row,  int column,  QWidget* parent);
    void fillMovements() override;

};

#endif // PIECES_HPP
