
#ifndef CHESSGAME_HPP
#define CHESSGAME_HPP

#include <QObject>
#include <array>
#include <memory>

#include "chessboard.hpp"
#include "piece.hpp"
#include "king.hpp"
#include "box.hpp"

class ChessGame : public QObject
{
    using Coordinates = std::pair<int, int>;

    Q_OBJECT
public:

    void connectBoard(Chessboard* chessboard);

    std::array<std::array<std::shared_ptr<Piece>, 8>, 8> boardPieces_{};
    std::array<std::array<Box*, 8>, 8> boardBoxes_{};

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

private:
    Piece* lastPiecePressed_{nullptr};
    void movePiece(Coordinates newCoordinates);

    void highlightMoves(Piece* piece);
    void revertHighlight();

    void startGame();
    bool isGameStarted_{false};
    void changeTurn();

    bool isValidMove(Coordinates position);

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

private slots:
   void validateClick(Coordinates coordinates);
   void startNewGame();
   void startQueenVRook();
   void startPhilidor();
   void startGelfandVSvidler();
   void startPonziani();
   void startTestGame();
};


#endif // CHESSGAME_HPP
