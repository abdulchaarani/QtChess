
#ifndef PIECE_H
#define PIECE_H


#include <QObject>
#include <QPushButton>

#include <list>
#include <map>

#include "point.hpp"

class Box;
class ChessBoard;
enum class Color;

// ABSTRACT piece class

class Piece : public QPushButton
{
    Q_OBJECT

public:
    Piece(Color color, int column, int row, ChessBoard* board, QWidget *parent = nullptr);
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

    Color color_;

    void killPiece(Piece* victim);

    void check();

    bool isChecked{false};

protected:
    Point coordinates_;
    ChessBoard* chessboard_;

private:
    // UNUSED
    int id_;
    inline static int idCount;
    void revertCheck();


signals:
    // fires everytime a piece is moved
    void movedPiece();

    void playedFirstMove();

private slots:
    void updatePosition();

    // to call correct overloaded function (#operator<<)
    void fillAllMovements();

};
#endif // PIECE_H
