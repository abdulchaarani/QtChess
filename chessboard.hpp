
#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP


#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

#include "layouts.hpp"
#include"box.hpp"

class Chessboard : public QWidget
{
    using Coordinates = std::pair<int, int>;
    Q_OBJECT

public:
    Chessboard(QWidget* parent = nullptr);
    QGridLayout* grid_;
    QVBoxLayout* lay_;
    QLabel*      label_;

private:
    QWidget* parent_;

    std::array<std::array<Box*, 8>, 8> boardBoxes_{};

    QTimer blinkTimer_;
    Box* blinkingPiece;
    const QString* originalFont;
    const QString* checkedFont;

private slots:
    void onBoxClicked();
    void setPieceColor(Coordinates coordinates, Color color);
    void setBoxText(Coordinates coordinates, QString text);
    void processHighlight(Coordinates coordinates, Highlight highlight);
    void moveViewPiece(Coordinates oldCoordinates, Coordinates newCoordinates);
    void toggleTurnLabel(Color nextTurn);
    void startTimer(Coordinates coordinates, int time);
    void toggleBlink();
    void rotateKing(Coordinates kingPosition);
    void displayWinner(Color winner);

signals:
    void sendClick(Coordinates coordinates);
};

#endif // CHESSBOARD_HPP
