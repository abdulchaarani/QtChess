QT = core

CONFIG += c++20 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bishop.cpp \
    Chessboard.cpp \
    ChessGame.cpp \
    ChessCore.cpp \
    CreditsScreen.cpp \
    EndGamesScreen.cpp \
    King.cpp \
    Knight.cpp \
    layouts.cpp \
        main.cpp \
        Box.cpp \
    Pawn.cpp \
    Piece.cpp \
    Queen.cpp \
    Rook.cpp \
    TitleScreen.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Bishop.hpp \
    Box.hpp \
    Chessboard.hpp \
    ChessGame.hpp \
    ChessCore.hpp \
    CreditsScreen.hpp \
    EndGamesScreen.hpp \
    King.hpp \
    Knight.hpp \
    layouts.hpp \
    Pawn.hpp \
    Piece.hpp \
    Queen.hpp \
    Rook.hpp \
    TitleScreen.hpp


QT += widgets
