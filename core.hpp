
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
    model::ChessGame*      mainGame_;
    view::Chessboard*     chessboard_;
    QStackedLayout* mainMenuLayout_;
    view::TitleScreen*    titleScreen_;
    view::CreditsScreen*  creditsScreen_;
    view::EndGamesScreen* endGamesScreen_;

    void connectSignals();
};

#endif // MAINMENU_H
