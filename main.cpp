#include <QApplication>

#include "core.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChessCore* game = new ChessCore();

    game->show();

    return app.exec();
}
