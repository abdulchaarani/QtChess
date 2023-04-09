
#ifndef PIECES_HPP
#define PIECES_HPP


#include <QObject>
#include <QPushButton>
#include "point.hpp"
#include <list>
#include <map>

class Box;
class ChessBoard;


// ABSTRACT piece class

class Piece : public QPushButton
{
    Q_OBJECT

public:
    Piece(int column, int row, ChessBoard* board, QWidget *parent = nullptr);
    virtual ~Piece() = default;

    void changePosition(int column, int row);

    // List of valid moves
    std::list<Point> movements; // TODO change to Point* eventually

    // UNUSED
    static std::unordered_map<int, Piece*> friendlies;

    // old getter
    Point& getCoordinates();

    // function that fills list of valid moves
    virtual void fillMovements() = 0;

    enum Colour
    {
        WHITE,
        BLACK,
    };


protected:
    Point coordinates_;
    ChessBoard* chessboard_;
    Colour colour_;

private:
    // UNUSED
    int id_;
    inline static int idCount;

signals:
    // fires everytime a piece is moved
    void movedPiece();

private slots:
    void updatePosition();

    // to call correct overloaded function (#operator<<)
    void fillAllMovements();

};


// Concrete pieces classes

class King : public Piece
{
    Q_OBJECT

public:
    King(int column,  int row, ChessBoard* board, QWidget* parent, Colour colour);
    void fillMovements() override;
    void check();

};

class Knight : public Piece
{
    Q_OBJECT

public:
    Knight(int row,  int column, ChessBoard* board, QWidget* parent, Colour colour);
    void fillMovements() override;

};

class Pawn : public Piece
{
    Q_OBJECT

public:
    Pawn(int column,  int row, ChessBoard* board, QWidget* parent, Colour colour);
    void fillMovements() override;

private:
    bool firstMove_{false};
};

#endif // PIECES_HPP
