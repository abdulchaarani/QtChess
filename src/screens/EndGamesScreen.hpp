
#ifndef ENDGAMES_HPP
#define ENDGAMES_HPP

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

namespace view{

class EndGamesScreen : public QWidget
{
    Q_OBJECT
public:
    explicit EndGamesScreen(QWidget* parent = nullptr);

    QPushButton* queenRookButton_;
    QPushButton* philidorButton_;
    QPushButton* gelfandButton_;
    QPushButton* ponzianiButton_;
    QPushButton* endGameButton5_;

private:
    QVBoxLayout* verticalButtonLayout_;

    inline static const int buttonSize_{100};
};

}
#endif // ENDGAMES_HPP
