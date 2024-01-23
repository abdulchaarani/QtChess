/**
* Tests for Model ChessGame of QtChess.
* Based on TestCalc by Francois-R.Boyer@PolyMtl.ca
* \file   chessgame.cpp
* \author Abdul-Wahab Chaarani 1793305 and Hiba Chaarani 2205674
* \date   5 mai 2023
* Créé le 3 mai 2023
*/
#include "chessgame.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include <iostream>
#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

using namespace model;
using Coordinates = std::pair<int, int>;

// add piece
TEST(ChessGame, basicMove) {
	ChessGame game;
	game.addPiece<King>(Color::white, 0, 0);
	game.addPiece<King>(Color::black, 7, 7);
	auto piece = game.boardPieces_[0][0];
	EXPECT_EQ(piece->coordinates_, std::pair(0,0));
	game.lastPiecePressed_ = piece.get();
	game.movePiece({ 1,1 });
	EXPECT_EQ(game.boardPieces_[1][1], piece);
	EXPECT_EQ(piece->coordinates_, std::pair(1, 1));
	EXPECT_EQ(game.boardPieces_[0][0], nullptr);
}

TEST(ChessGame, movePawn) {
	ChessGame game;
	game.addPiece<King>(Color::white, 0, 0);
	game.addPiece<King>(Color::black, 7, 7);
	game.addPiece<Pawn>(Color::black, 1, 1);
	game.addPiece<Pawn>(Color::black, 2, 1);
	game.addPiece<Pawn>(Color::white, 2, 2);
	game.generateMovements();
	auto pawn = game.boardPieces_[1][1];
	bool moveForward { false };
	bool doubleForward{ false };
	bool moveKill{ false };
	bool moveBackward{ false };
	for (auto&& m : pawn->movements) {
		if (m == std::pair(2, 1))
			moveForward = true;
		if (m == std::pair(3, 1))
			doubleForward = true;
		if (m == std::pair(2, 2))
			moveKill = true;
		if (m == std::pair(0, 1))
			moveBackward = true;
	}
	EXPECT_FALSE(moveForward);
	EXPECT_TRUE(doubleForward);
	EXPECT_TRUE(moveKill);
	EXPECT_FALSE(moveBackward);
}

TEST(ChessGame, validMove) {
	ChessGame game;
	game.addPiece<King>(Color::white, 0, 0);
	game.addPiece<King>(Color::black, 7, 7);
	game.addPiece<Queen>(Color::black, 1, 1);
	bool isValid{ false };
	auto king = game.boardPieces_[0][0];
	auto queen = game.boardPieces_[1][1];
	game.lastPiecePressed_ = king.get();
	isValid = game.isValidMove({ 0, 1 });
	EXPECT_FALSE(isValid);
}

TEST(ChessGame, generateGames) {
	ChessGame game;
	game.startNewGame();
	EXPECT_TRUE(game.isGameStarted_);
}

TEST(ChessGame, checkMate) {
	ChessGame game;
	game.startTestGame();
	auto queen = game.boardPieces_[2][2];
	game.lastPiecePressed_ = queen.get();
	game.movePiece({ 2, 0 });
	auto rook = game.boardPieces_[6][7];
	game.lastPiecePressed_ = rook.get();
	game.movePiece({ 0, 7 });
	game.generateMovements();
	game.changeTurn();
	EXPECT_FALSE(game.isGameStarted_);
}

#endif
