
#ifndef ENDGAMES_HPP
#define ENDGAMES_HPP

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

class EndGamesScreen : public QWidget
{
    Q_OBJECT
public:
    explicit EndGamesScreen(QWidget* parent = nullptr);

    friend class ChessCore;

private:
    QVBoxLayout* verticalButtonLayout_;

    QPushButton* queenRookButton_;
    QPushButton* philidorButton_;
    QPushButton* gelfandButton_;
    QPushButton* ponzianiButton_;
    QPushButton* endGameButton5_;

    inline static const int buttonSize_{100};

};

#endif // ENDGAMES_HPP
