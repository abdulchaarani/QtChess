
#ifndef PIECES_HPP
#define PIECES_HPP


#include <QObject>
#include <QPushButton>
#include "point.hpp"
#include <list>

class Box;

class Piece : public QPushButton
{
    Q_OBJECT

public:
    Piece(int column, int row,  QWidget *parent = nullptr);
    virtual ~Piece() = default;

    void changePosition(int column, int row);
    std::list<Point> movements;

    Point& getCoordinates();

    void possessBox(Box* box);

    virtual void fillMovements() = 0;

public slots:
    void updatePosition();

protected:
    Point coordinates_;
    Box* possessedBox_{nullptr};

};

class King : public Piece
{
    Q_OBJECT

public:
    King(int column,  int row,  QWidget* parent);
    void fillMovements() override;

};

class Knight : public Piece
{
    Q_OBJECT

public:
    Knight(int column,  int row,  QWidget* parent);
    void fillMovements() override;

};


#endif // PIECES_HPP
