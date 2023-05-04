#include <QApplication>

#include "core.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChessCore* game = new ChessCore();

    game->setFixedSize(820,850);
    game->show();

    return a.exec();
}
