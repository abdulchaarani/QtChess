
#include "creditsscreen.hpp"

CreditsScreen::CreditsScreen(const QString& creditsText, QWidget* parent) :
    QWidget(parent),
    credits(new QLabel(creditsText, this)),
    m_backButton(new QPushButton(tr("take me back to main menu"), this )),
    creditsScreenLayout(new QVBoxLayout(this))
{
    // Setup credits page UI
    creditsScreenLayout->addWidget(credits, 0, Qt::AlignHCenter);
    creditsScreenLayout->addWidget(m_backButton);
}
