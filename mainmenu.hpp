
#ifndef MAINMENU_H
#define MAINMENU_H

#include "chessboard.hpp"
#include "creditsscreen.hpp"
#include "titlescreen.hpp"
#include "endgames.hpp"

#include <QWidget>
#include <QStackedLayout>
#include <qdebug.h>

/* MainMenu is a class that inherits from QMainWindow bc i wanted a container to all our widget classes
 * (TitleScreen, CreditsScreen and ChessBoard). It basically replaces the mainWindow you originally
 * defined in main. It contains all the widgets we need so no need to pollute main anymore. Its
 * a StackedLayout bc its a pile of widgets on top of eachother.*/

class MainMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainMenu(QMainWindow* parent = nullptr);

public slots:
    void onBackPress();
    void onCreditsPress();
    void onEndGamesPress();
    void onGameStarted();

private:
    QStackedLayout* mainMenuLayout;
    ChessBoard*     chessBoard;
    TitleScreen*    titleScreen;
    CreditsScreen*  creditsScreen;
    EndGamesScreen* endGamesScreen;

    QMainWindow *parent_;
};

#endif // MAINMENU_H
