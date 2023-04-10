QT = core

CONFIG += c++20 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        box.cpp \
        chessboard.cpp \
        king.cpp \
        knight.cpp \
        main.cpp \
        pieces.cpp \
        point.cpp \
        rook.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    box.hpp \
    chessboard.hpp \
    king.hpp \
    knight.hpp \
    pieces.hpp \
    point.hpp \
    rook.hpp

QT += widgets
