
#ifndef MAINMENU_H
#define MAINMENU_H

#include "chessboard.hpp"
#include "chessgame.hpp"
#include "titlescreen.hpp"
#include "creditsscreen.hpp"
#include "endgamesScreen.hpp"

#include <QWidget>
#include <QStackedLayout>
#include <qdebug.h>

class ChessCore : public QMainWindow
{
    Q_OBJECT
public:
    ChessCore();

public slots:
    void onBackPress();
    void onCreditsPress();
    void onEndGamesPress();
    void onGameStarted();

private:
    ChessGame*      mainGame_;
    Chessboard*     chessboard_;
    QStackedLayout* mainMenuLayout_;
    TitleScreen*    titleScreen_;
    CreditsScreen*  creditsScreen_;
    EndGamesScreen* endGamesScreen_;

    void connectSignals();
};

#endif // MAINMENU_H
