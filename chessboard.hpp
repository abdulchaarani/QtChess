
#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP


#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <list>
#include <array>

#include "box.hpp"

class ChessBoard : public QWidget
{
    Q_OBJECT



public:
    ChessBoard(QWidget* parent = nullptr);
    QGridLayout* grid_;

    Box* getBoxPressed() { return boxPressed_; }
    Piece* getPiecePressed() { return piecePressed_; }
    void setPiecePressed(Piece* piece) { piecePressed_ = piece; }

    void addKing(int row, int column);
    void addKnight(int row, int column);

    std::array<std::array<Piece*, 8>, 8> board_{}; //overload[]
private:
    Box* boxPressed_;
    Piece* piecePressed_;

    std::list<Box*> occupiedWhiteBoxes;

    QWidget* parent_;

signals:
    void buttonTriggered();
    void updateMovements();

private slots:
    void onButtonTrigger()
    {
        QObject* senderObject = QObject::sender();
        if (senderObject == nullptr)
            return;
        boxPressed_ = qobject_cast<Box*>(senderObject);
        emit buttonTriggered();
    }

    void validateMovements(){
        emit updateMovements();
    }

};



#endif
