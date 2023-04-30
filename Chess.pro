QT = core

CONFIG += c++20 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        bishop.cpp \
        box.cpp \
        chessboard.cpp \
        creditsscreen.cpp \
        endgames.cpp \
        king.cpp \
        knight.cpp \
        layouts.cpp \
        main.cpp \
        mainmenu.cpp \
        pawn.cpp \
        piece.cpp \
        point.cpp \
        queen.cpp \
        rook.cpp \
        titlescreen.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    bishop.hpp \
    box.hpp \
    chessboard.hpp \
    creditsscreen.hpp \
    endgames.hpp \
    king.hpp \
    knight.hpp \
    layouts.hpp \
    mainmenu.hpp \
    pawn.hpp \
    piece.hpp \
    point.hpp \
    queen.hpp \
    rook.hpp \
    titlescreen.hpp

QT += widgets
