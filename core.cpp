
#include "core.hpp"
#include <QDebug>

ChessCore::ChessCore()
         : mainGame_{new ChessGame}
         , chessboard_{new Chessboard}
         , mainMenuLayout_{new QStackedLayout}
         , titleScreen_{new TitleScreen(this)}
         , creditsScreen_{new CreditsScreen(tr("Abdul-Wahab Chaarani & Hiba Chaarani, 2023"), this)}
         , endGamesScreen_{new EndGamesScreen(this)}

{
    // Defining a custom layout for MainMenu. This is the reason for the message in output

    mainGame_->connectBoard(chessboard_);

    mainMenuLayout_->addWidget(titleScreen_);
    mainMenuLayout_->addWidget(chessboard_);
    mainMenuLayout_->addWidget(creditsScreen_);
    mainMenuLayout_->addWidget(endGamesScreen_);
    mainMenuLayout_->setCurrentWidget(titleScreen_);

    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout(mainMenuLayout_);
    setCentralWidget(centralWidget);

    // connect main menu buttons to their proper functions
    connect(titleScreen_->newGameButton_, SIGNAL(clicked()), mainGame_, SLOT(startNewGame()));
    connect(titleScreen_->creditsButton_, SIGNAL(clicked()), this, SLOT(onCreditsPress()));
    connect(titleScreen_->endGameButton_, SIGNAL(clicked()), this, SLOT(onEndGamesPress()));
    connect(creditsScreen_->backButton_,  SIGNAL(clicked()), this, SLOT(onBackPress()));
    connect(mainGame_, SIGNAL(gameStarted()), this, SLOT(onGameStarted()));

    //connect end games buttons
    connect(endGamesScreen_->queenRookButton_, SIGNAL(clicked()), mainGame_, SLOT(startQueenVRook()));
    connect(endGamesScreen_->philidorButton_,  SIGNAL(clicked()), mainGame_, SLOT(startPhilidor()));
    connect(endGamesScreen_->gelfandButton_,   SIGNAL(clicked()), mainGame_, SLOT(startGelfandVSvidler()));
    connect(endGamesScreen_->ponzianiButton_,  SIGNAL(clicked()), mainGame_, SLOT(startPonziani()));
    connect(endGamesScreen_->endGameButton5_, SIGNAL(clicked()), mainGame_, SLOT(startTestGame()));
}

// Slot that switches the current screen to the titlescreen
void ChessCore::onBackPress()
{
    mainMenuLayout_->setCurrentWidget(titleScreen_);
}

// Slot that switches the current screen to credits screen
void ChessCore::onCreditsPress()
{
    mainMenuLayout_->setCurrentWidget(creditsScreen_);
}

void ChessCore::onEndGamesPress()
{
    mainMenuLayout_->setCurrentWidget(endGamesScreen_);
}

// Slot that switches to chessBoard screen.Sensitive to the gameStarted() signal defined in chessBoard
void ChessCore::onGameStarted()
{
    mainMenuLayout_->setCurrentWidget(chessboard_);
}


