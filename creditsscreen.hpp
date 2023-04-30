
#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

/*CreditsScreen is the pop-up u get when u press the credits button. It will eventually contain better text*/

class CreditsScreen : public QWidget
{
    Q_OBJECT
public:
    explicit CreditsScreen(const QString& creditsText, QWidget* parent);

    friend class MainMenu;

private:
    QLabel*      const credits;
    QPushButton* const m_backButton;
    QVBoxLayout* const creditsScreenLayout; // Used because it can be resized, but i was lied to and its fixed size now...
};

#endif // CREDITSSCREEN_H
