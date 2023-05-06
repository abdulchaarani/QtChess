/**
* Program that defines the CreditsScreen class (UI configurations).
* Part of the View
* \file   CreditsScreen.cpp
* \author Abdul-Wahab Chaarani 1793305 and Hiba Chaarani 2205674
* \date   5/05/2023
* Created on 9/04/2023
*/

#include "CreditsScreen.hpp"
#include "layouts.hpp"

namespace view{

CreditsScreen::CreditsScreen(QWidget* parent) :
    QWidget(parent),
    credits_(new QLabel(this)),
    backButton_(new QPushButton("take me back to main menu", this )),
    creditsScreenLayout_(new QVBoxLayout(this))
{
    // Setup credits page UI
    credits_->setText(creditsText_);
    credits_->setFont(layouts::creditsFont);
    creditsScreenLayout_->addWidget(credits_, 0, Qt::AlignHCenter);
    creditsScreenLayout_->addWidget(backButton_);
    backButton_->setStyleSheet(layouts::menuButtonFont);
}

}
