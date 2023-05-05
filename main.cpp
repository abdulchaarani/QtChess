/**
* Main program. Displays the titlescreen.
* \file   chessboard.cpp
* \author Abdul-Wahab et Hiba
* \date   5 mai 2023
* Créé le 9 avril 2023
*/

#include <QApplication>

#include "core.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChessCore* game = new ChessCore();

    game->show();

    return app.exec();
}
