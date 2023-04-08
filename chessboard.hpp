
#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP


#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

#include "box.hpp"

class ChessBoard : public QWidget
{
    Q_OBJECT



public:
    ChessBoard(QWidget* parent = nullptr);
    QGridLayout* board_;

    Box* getWhoWasPressed() { return whoWasPressed_; }

private:
    Box* whoWasPressed_;

signals:
    void buttonTriggered();

private slots:
    void onButtonTrigger()
    {
        QObject* senderObject = QObject::sender();
        if (senderObject == nullptr)
            return;
        whoWasPressed_ = qobject_cast<Box*>(senderObject);
        emit buttonTriggered();
    }
};

#endif
