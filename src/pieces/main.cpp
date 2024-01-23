/**
* Main program to start playing Chess.
* Options to select new game or predetermined end games
* En passant and other advanced moves not implemented
* \file   main.cpp
* \author Abdul-Wahab Chaarani 1793305 et Hiba Chaarani 2205674
* \date   5 mai 2023
* Créé le 9 avril 2023
*/

#include <QApplication>

#include "ChessCore.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChessCore game;
    game.show();

    return app.exec();
}
