
#ifndef LAYOUTS_H
#define LAYOUTS_H

#include <QObject>
#include <QFont>

enum class Color {white, black};
enum class Highlight {move, kill, revert};

namespace layouts{

// main menu layouts
extern const int screenWidth;
extern const int screenHeight;
extern const QString menuButtonFont;
extern const QFont   creditsFont;

// piece layouts
extern const double  offset;
extern const int     marginX;
extern const int     marginY;
extern const int     pieceSize;
extern const int     buttonSize;
extern const QFont   pieceFont;
extern const QString pieceStyle;

// box layouts
extern const int boxSize;
extern const QString whiteBoxFont;
extern const QString blackBoxFont;
extern const QString whiteCheckedFont;
extern const QString blackCheckedFont;
extern const QString highlightKillFont;
extern const QString highlightMoveFont;
extern const QString whiteLostFont;
extern const QString blackLostFont;

// chesesboard layouts
extern const int labelSize;
extern const QString whiteTurnFont;
extern const QString blackTurnFont;

}

#endif // LAYOUTS_H
