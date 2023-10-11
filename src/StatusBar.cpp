#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "StatusBar.h"

StatusBar::StatusBar(/* args */)
{
    this->initWindow();
}

StatusBar::~StatusBar()
{
}

void StatusBar::initWindow()
{
    this->postionX = 20;
    this->postionY = 625;
    this->font.loadFromFile("../util/SF Atarian System.ttf");
    this->font.setSmooth(true);
    this->string = "score: 0";
    this->text = new sf::Text(font, this->string, 20);
    
    this->text->setPosition(sf::Vector2f(postionX, postionY));
}

void StatusBar::update(const float& dt, int score)
{
    this->string = "score: ";
    string += std::to_string(score);
    this->text->setString(string);
}

void StatusBar::render(sf::RenderTarget* target )
{
    target->draw(*this->text);
}

#pragma GCC diagnostic pop
