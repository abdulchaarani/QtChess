
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

/* MainMenu is a class that inherits from QMainWindow bc i wanted a container to all our widget classes
 * (TitleScreen, CreditsScreen and ChessBoard). It basically replaces the mainWindow you originally
 * defined in main. It contains all the widgets we need so no need to pollute main anymore. Its
 * a StackedLayout bc its a pile of widgets on top of eachother.*/

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
};

#endif // MAINMENU_H
