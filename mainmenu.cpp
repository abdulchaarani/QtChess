
#include "mainmenu.hpp"
#include <QDebug>

MainMenu::MainMenu(QMainWindow* parent)
    :
    mainMenuLayout{new QStackedLayout()},
    chessBoard{new ChessBoard(this)},
    titleScreen{new TitleScreen(this)},
    creditsScreen{new CreditsScreen(tr("Abdul-Wahab Chaarani & Hiba Chaarani, 2023"), this)},
    endGamesScreen{new EndGamesScreen(this)},
    parent_{parent}

{
    // Defining a custom layout for MainMenu. This is the reason for the message in output
    mainMenuLayout->addWidget(titleScreen);
    mainMenuLayout->addWidget(chessBoard);
    mainMenuLayout->addWidget(creditsScreen);
    mainMenuLayout->addWidget(endGamesScreen);
    mainMenuLayout->setCurrentWidget(titleScreen);

    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(mainMenuLayout);
    setCentralWidget(centralWidget);

    // connect main menu buttons to their proper functions
    connect(titleScreen->m_newGameButton, SIGNAL(clicked()), chessBoard, SLOT(startGame()));
    connect(titleScreen->m_creditsButton, SIGNAL(clicked()), this, SLOT(onCreditsPress()));
    connect(titleScreen->m_endGameButton, SIGNAL(clicked()), this, SLOT(onEndGamesPress()));
    connect(creditsScreen->m_backButton,  SIGNAL(clicked()), this, SLOT(onBackPress()));
    connect(chessBoard, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));

    //connect end games buttons
    connect(endGamesScreen->queenRookButton_, SIGNAL(clicked()), chessBoard, SLOT(startQueenVRook()));
    connect(endGamesScreen->philidorButton_,  SIGNAL(clicked()), chessBoard, SLOT(startPhilidor()));
    connect(endGamesScreen->gelfandButton_,   SIGNAL(clicked()), chessBoard, SLOT(startGelfandVSvidler()));
    connect(endGamesScreen->ponzianiButton_,  SIGNAL(clicked()), chessBoard, SLOT(startPonziani()));
}

// Slot that switches the current screen to the titlescreen
void MainMenu::onBackPress()
{
    mainMenuLayout->setCurrentWidget(titleScreen);
}

// Slot that switches the current screen to credits screen
void MainMenu::onCreditsPress()
{
    mainMenuLayout->setCurrentWidget(creditsScreen);
}

void MainMenu::onEndGamesPress()
{
    mainMenuLayout->setCurrentWidget(endGamesScreen);
}

// Slot that switches to chessBoard screen.Sensitive to the gameStarted() signal defined in chessBoard
void MainMenu::onGameStarted()
{
    mainMenuLayout->setCurrentWidget(chessBoard);
}


