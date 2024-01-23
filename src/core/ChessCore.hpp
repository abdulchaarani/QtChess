
#ifndef MAINMENU_H
#define MAINMENU_H

#include "Chessboard.hpp"
#include "ChessGame.hpp"
#include "TitleScreen.hpp"
#include "Creditsscreen.hpp"
#include "EndGamesScreen.hpp"
#include <memory>

#include <QWidget>
#include <QStackedLayout>

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
    std::unique_ptr<model::ChessGame>       chessGame_;
    view::Chessboard*                       chessboard_;
    QStackedLayout*                         mainMenuLayout_;
    view::TitleScreen*                      titleScreen_;
    view::CreditsScreen*                    creditsScreen_;
    view::EndGamesScreen*                   endGamesScreen_;

    void connectSignals();
};

#endif // MAINMENU_H
