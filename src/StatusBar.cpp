#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"
#include <iostream>
#include "StatusBar.h"

StatusBar::StatusBar(/* args */)
{   
    this->initWindow();
}

StatusBar::~StatusBar()
{
    for (sf::Sprite* sprite : this->heartSprites) {
        delete sprite;
    }
    heartSprites.clear();
    delete this->text;
}

void StatusBar::initWindow()
{
    this->postionX = 20;
    this->postionY = 850;
    this->font.loadFromFile("../util/SF Atarian System.ttf");
    this->font.setSmooth(true);
    this->string = "score: 0";
    this->text = new sf::Text(font, this->string, 20);

    this->heartTexture.loadFromFile("../util/heart.png");

    for (int i = 0; i < health; i++)
    {
        heartSprites.push_back(new sf::Sprite(this->heartTexture));
        heartSprites[i]->setScale(sf::Vector2f(0.1, 0.1));
        heartSprites[i]->setPosition(sf::Vector2f(600 + i * 10, 850));
    }
    
    
    
    this->text->setPosition(sf::Vector2f(postionX, postionY));
}

void StatusBar::update(const float& dt, int score, int health)
{
    this->health = health;
    this->string = "score: ";
    string += std::to_string(score);
    this->text->setString(string);



    
}

void StatusBar::render(sf::RenderTarget* target )
{
    target->draw(*this->text);
    for (int i = 0; i < health; i++)
    {
        target->draw(*this->heartSprites[i]);
    }
    
    // target->draw(*this->heartSprite);

}

#pragma GCC diagnostic pop
