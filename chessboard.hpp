
#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP


#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <list>

#include "box.hpp"

class ChessBoard : public QWidget
{
    Q_OBJECT



public:
    ChessBoard(QWidget* parent = nullptr);
    QGridLayout* board_;

    Box* getBoxPressed() { return boxPressed_; }
    Piece* getPiecePressed() { return piecePressed_; }
    void setPiecePressed(Piece* piece) { piecePressed_ = piece; }

private:
    Box* boxPressed_;
    Piece* piecePressed_;

    std::list<Box*> occupiedWhiteBoxes;

signals:
    void buttonTriggered();

private slots:
    void onButtonTrigger()
    {
        QObject* senderObject = QObject::sender();
        if (senderObject == nullptr)
            return;
        boxPressed_ = qobject_cast<Box*>(senderObject);
        emit buttonTriggered();
    }
};

#endif
