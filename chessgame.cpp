#include "cppitertools/itertools.hpp"

#include "chessgame.hpp"
#include "QDebug"
#include "pawn.hpp"
#include "knight.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "queen.hpp"

using namespace iter;

namespace model{


void ChessGame::generateMovements()
{
    for (int row : range(boardDim))
        for (int column : range(boardDim))
            if (boardPieces_[row][column] != nullptr)
                boardPieces_[row][column]->fillMovements(boardPieces_);
}

void ChessGame::validateClick(Coordinates coordinates)
{
    if (!isGameStarted_)
        return;

    this->revertHighlight();
    auto [row,column] = coordinates;

    Piece* clickedPiece = boardPieces_[row][column].get();

    //check if right player turn
    if(lastPiecePressed_ == nullptr) {
        if (clickedPiece == nullptr)
            return;
        if (clickedPiece->color_ != currentPlayer_)
            return;
        }

    // if click in movements
        if(lastPiecePressed_ != nullptr){

        if (clickedPiece != nullptr)
            if (clickedPiece->color_ == currentPlayer_){
                lastPiecePressed_ = clickedPiece;
                highlightMoves(clickedPiece);
                return;
            }

        for (auto&& move : lastPiecePressed_->movements){
            if (move == coordinates){
                if (isValidMove(move))
                    movePiece(coordinates);
                lastPiecePressed_ = nullptr;
                return;
            }
        }

        lastPiecePressed_ = nullptr;
        return;

    }

    highlightMoves(clickedPiece);

    lastPiecePressed_ = clickedPiece;
}

void ChessGame::movePiece(Coordinates newCoordinates)
{
    Piece* piece = lastPiecePressed_;

    auto oldCoordinates = lastPiecePressed_->coordinates_;
    auto [oldRow, oldColumn] = oldCoordinates;
    auto [newRow, newColumn] = newCoordinates;

    piece->coordinates_ = newCoordinates;

    boardPieces_[newRow][newColumn] = std::move(boardPieces_[oldRow][oldColumn]);

    generateMovements();
    emit updateCoordinates(oldCoordinates, newCoordinates);

    verifyCheck();
    changeTurn();
}

void ChessGame::revertHighlight()
{
    for (int row : range(boardDim))
        for (int column : range(boardDim))
            emit highlight({row, column}, Highlight::revert);
}

void ChessGame::highlightMoves(Piece* piece)
{
    for (auto&& move : piece->movements){
        auto [row,column] = move;
        if (boardPieces_[row][column] != nullptr){
            if (boardPieces_[row][column]->color_ != piece->color_){
                emit highlight(move, Highlight::kill);
            }
        }
        else{
            emit highlight(move, Highlight::move);
        }

    }
}

void ChessGame::changeTurn()
{

    if (currentPlayer_ == Color::white) {
        currentPlayer_ = Color::black;

    } else {
        currentPlayer_ = Color::white;
    }
    emit turnChanged(currentPlayer_);

    if (getFriendlyKing()->isChecked_ || getOpponentKing()->isChecked_)
        verifyCheckmate();

}
King* ChessGame::getFriendlyKing()
{
    return currentPlayer_ == Color::white ? whiteKing_ : blackKing_;
}
King* ChessGame::getOpponentKing()
{
     return currentPlayer_ == Color::white ? blackKing_ : whiteKing_;
}


bool ChessGame::isChecked()
{
    King* king{getFriendlyKing()};
    // verify if any enemy piece has the king in their sights
    for (int row : range(boardDim))
        for (int column : range(boardDim))
            if (boardPieces_[row][column] != nullptr)
                if (boardPieces_[row][column]->color_ != currentPlayer_)
                    for (auto&& move : boardPieces_[row][column]->movements)
                        if (move == king->coordinates_){
                            return true;
                        }

    return false;
}

void ChessGame::verifyCheck()
{
    Piece* attacker = lastPiecePressed_;

    King* king{getOpponentKing()};

    if (isGameStarted_)
        for (auto&& move : attacker->movements){
            if (move == king->coordinates_){
                king->isChecked_ = true;
                emit blinkCheckedKing(king->coordinates_, 500);
                qDebug() << "CHECK";
                return;
            }
        }
}

bool ChessGame::isValidMove(Coordinates position)
{
    Piece* piecePressed = lastPiecePressed_;

    Coordinates oldPosition = piecePressed->coordinates_;
    auto [newRow, newColumn] = position;
    auto [oldRow, oldColumn] = oldPosition;

    // to validate if enemy's death would cause a self-check
    std::shared_ptr<Piece> potentialVictim{nullptr};
    if (boardPieces_[newRow][newColumn] != nullptr){
        potentialVictim = std::move(boardPieces_[newRow][newColumn]);
    }

    // temporarily move clicked piece into future position to validate if king is checked
    boardPieces_[newRow][newColumn] = std::move(boardPieces_[oldRow][oldColumn]);
    boardPieces_[oldRow][oldColumn].reset();
    piecePressed->coordinates_ = position;
    generateMovements();
    if (potentialVictim != nullptr)
        potentialVictim->movements.clear();

    // would the king be in check in new position
    bool isValid = !isChecked();

    // replace all the moved pieces back to original positions
    piecePressed->coordinates_ = oldPosition;
    boardPieces_[oldRow][oldColumn] = std::move(boardPieces_[newRow][newColumn]);

    if (potentialVictim != nullptr){
        potentialVictim->coordinates_ = position;
        boardPieces_[newRow][newColumn] = std::move(potentialVictim);
    }
    else{
        boardPieces_[newRow][newColumn].reset();
    }

    generateMovements();

    if(!isValid)
        emit blinkCheckedKing(getFriendlyKing()->coordinates_, 150);

    return isValid;
}


void ChessGame::verifyCheckmate(){

    for (int row : range(boardDim))
        for (int column : range(boardDim))
            if (boardPieces_[row][column] != nullptr)
                if (boardPieces_[row][column]->color_ == currentPlayer_){
                    std::forward_list<Coordinates> pieceMovements{boardPieces_[row][column]->movements};
                    for (auto&& move : pieceMovements){
                        lastPiecePressed_ = boardPieces_[row][column].get();
                        if (isValidMove(move))
                            return;
                    }
                }
    qDebug() << "CHECKMATE";
    gameOver();
    return;
}

void ChessGame::gameOver(){
    isGameStarted_ = false;
    for (int row : range(boardDim))
        for (int column : range(boardDim))
            if (boardPieces_[row][column] != nullptr)
                boardPieces_[row][column]->movements.clear();

    emit killKing(getFriendlyKing()->coordinates_);
    emit crownWinner(getOpponentKing()->color_);
}

void ChessGame::startGame()
{
    isGameStarted_ = true;
    currentPlayer_ = Color::white;
    generateMovements();
    emit gameStarted();
}

void ChessGame::startNewGame()
{
    addPiece<King>(Color::white, 7, 4);
    addPiece<King>(Color::black, 0, 4);

    addPiece<Knight>(Color::white, 7, 1);
    addPiece<Knight>(Color::white, 7, 6);
    addPiece<Knight>(Color::black, 0, 1);
    addPiece<Knight>(Color::black, 0, 6);

    addPiece<Rook>(Color::white, 7, 0);
    addPiece<Rook>(Color::white, 7, 7);
    addPiece<Rook>(Color::black, 0, 0);
    addPiece<Rook>(Color::black, 0, 7);

    addPiece<Bishop>(Color::white, 7, 2);
    addPiece<Bishop>(Color::white, 7, 5);
    addPiece<Bishop>(Color::black, 0, 2);
    addPiece<Bishop>(Color::black, 0, 5);

    addPiece<Queen>(Color::white, 7, 3);
    addPiece<Queen>(Color::black, 0, 3);

    for (int i : range(boardDim)){
        addPiece<Pawn>(Color::white, 6, i);
        addPiece<Pawn>(Color::black, 1, i);
    }

    startGame();
}

void ChessGame::startQueenVRook()
{
    addPiece<King>(Color::white,3,3);
    addPiece<Queen>(Color::white, 1,5);

    addPiece<King>(Color::black,0,3);
    addPiece<Rook>(Color::black, 2,1);

    startGame();
}


void ChessGame::startPhilidor()
{
    addPiece<King>(Color::white, 2, 2);
    addPiece<Queen>(Color::white, 3, 0);

    addPiece<King>(Color::black, 0, 1);
    addPiece<Rook>(Color::black, 1, 1);

    startGame();
}


void ChessGame::startGelfandVSvidler()
{
    addPiece<King>(Color::white, 1 ,6);
    addPiece<Rook>(Color::white, 1, 7);

    addPiece<King>(Color::black, 3, 6);
    addPiece<Queen>(Color::black, 0, 4);

    startGame();
}

void ChessGame::startPonziani()
{
    addPiece<King>(Color::white, 7 ,0);
    addPiece<Queen>(Color::white, 1, 5);

    addPiece<King>(Color::black, 4, 1);
    addPiece<Bishop>(Color::black, 5, 0);
    addPiece<Knight>(Color::black, 5, 2);

    startGame();
}

void ChessGame::startTestGame()
{
    addPiece<King>(Color::white, 0, 3);
    addPiece<King>(Color::black, 7, 5);

    addPiece<Knight>(Color::white, 5, 3);
    addPiece<Knight>(Color::black, 3, 5);

    addPiece<Pawn>(Color::white, 6, 2);
    addPiece<Pawn>(Color::black, 1, 1);

    addPiece<Rook>(Color::black, 6, 7);
    addPiece<Rook>(Color::white, 0, 0);

    addPiece<Bishop>(Color::black, 3, 4);
    addPiece<Bishop>(Color::white, 2, 5);

    addPiece<Queen>(Color::white, 2, 2);
    addPiece<Queen>(Color::black, 1, 6);

    startGame();
}
}
