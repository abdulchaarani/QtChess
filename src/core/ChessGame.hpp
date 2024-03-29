
#ifndef CHESSGAME_HPP
#define CHESSGAME_HPP

#include <QObject>
#include <array>
#include <memory>

#include "Piece.hpp"
#include "King.hpp"

namespace model{

class ChessGame : public QObject
{
    using Coordinates = std::pair<int, int>;

    Q_OBJECT
public:

    static const int boardDim{8};

    std::array<std::array<std::shared_ptr<Piece>, boardDim>, boardDim> boardPieces_{};

    template <typename T>
    void addPiece(Color color, int row, int column)
    {
        auto piece = std::make_shared<T>(color, row, column);
        boardPieces_[row][column] = piece;

        if (piece->display_== "♔")
            whiteKing_ = dynamic_cast<King*>(piece.get());


        if (piece->display_== "♚")
            blackKing_ = dynamic_cast<King*>(piece.get());

        emit initialiseColor({row, column}, color);
        emit initialiseDisplay({row, column}, piece->display_);
    }

    void generateMovements();

    Color currentPlayer_{Color::white};

    void movePiece(Coordinates newCoordinates);
    void changeTurn();

    Piece* lastPiecePressed_{ nullptr };

    bool isValidMove(Coordinates position);
    bool isGameStarted_{ false };
private:

    void highlightMoves(Piece* piece);
    void revertHighlight();

    void startGame();

    King* whiteKing_;
    King* blackKing_;

    King* getFriendlyKing();
    King* getOpponentKing();

    bool isChecked();
    void verifyCheck();
    void verifyCheckmate();
    void gameOver();

signals:
   void initialiseColor(Coordinates cordinates, Color color);
   void initialiseDisplay(Coordinates coordinates, QString display);
   void highlight(Coordinates coordinates, Highlight highlight);
   void updateCoordinates(Coordinates oldCoordinates, Coordinates newCoordinates);
   void turnChanged(Color nextTurn);
   void blinkCheckedKing(Coordinates kingPosition, int period);
   void killKing(Coordinates kingPosition);
   void crownWinner(Color winner);
   void gameStarted();

public slots:
   void validateClick(Coordinates coordinates);
   void startNewGame();
   void startQueenVRook();
   void startPhilidor();
   void startGelfandVSvidler();
   void startPonziani();
   void startTestGame();
};

}
#endif // CHESSGAME_HPP
