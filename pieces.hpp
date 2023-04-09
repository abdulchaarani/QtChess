
#ifndef PIECES_HPP
#define PIECES_HPP


#include <QObject>
#include <QPushButton>
#include "point.hpp"
#include <list>
#include <map>

class Box;
class ChessBoard;

class Piece : public QPushButton
{
    Q_OBJECT

public:
    Piece(int column, int row, ChessBoard* board, QWidget *parent = nullptr);
    virtual ~Piece() = default;

    void changePosition(int column, int row);
    std::list<Point> movements; //change to ptr

    static std::unordered_map<int, Piece*> friendlies;

    Point& getCoordinates();

    void possessBox(Box* box);

    virtual void fillMovements() = 0;

public slots:
    void updatePosition();
    void fillAllMovements();

protected:
    Point coordinates_;
    Box* possessedBox_{nullptr};
    ChessBoard* chessboard_;

private:
    int id_;
    inline static int idCount;

signals:
    void movedPiece();

};

class King : public Piece
{
    Q_OBJECT

public:
    King(int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

};

class Knight : public Piece
{
    Q_OBJECT

public:
    Knight(int column,  int row, ChessBoard* board, QWidget* parent);
    void fillMovements() override;

};


#endif // PIECES_HPP
