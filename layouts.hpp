
#ifndef LAYOUTS_H
#define LAYOUTS_H

#include <QObject>
#include <QFont>
namespace layouts{

// main menu layouts
extern const QString menuButtonFont;

// piece layouts
extern const double  offset;
extern const int     marginX;
extern const int     marginY;
extern const int     pieceSize;
extern const int     buttonSize;
extern const QFont   pieceFont;
extern const QString pieceStyle;
extern const QString checkedFont;

// box layouts
extern const int boxSize;
extern const QString whiteBoxFont;
extern const QString blackBoxFont;
extern const QString highlightKillFont;
extern const QString highlightMoveFont;

// chesesboard layouts
extern const int labelSize;
extern const QString whiteTurnFont;
extern const QString blackTurnFont;


}

#endif // LAYOUTS_H
