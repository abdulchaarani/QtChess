
#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>


class CreditsScreen : public QWidget
{
    Q_OBJECT
public:
    explicit CreditsScreen(const QString& creditsText, QWidget* parent);

    friend class MainMenu;

private:
    QLabel*      const credits;
    QPushButton* const m_backButton;
    QVBoxLayout* const creditsScreenLayout;
};

#endif // CREDITSSCREEN_H
