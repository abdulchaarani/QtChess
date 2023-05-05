/**
* Main program. Displays the titlescreen.
* \file   core.cpp
* \author Abdul-Wahab Chaarani 1793305 et Hiba Chaarani 2205674
* \date   5 mai 2023
* Créé le 9 avril 2023
*/

#include <QApplication>

#include "core.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChessCore game;
    game.show();

    return app.exec();
}
