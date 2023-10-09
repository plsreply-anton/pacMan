#include "../include/Pellet.h"
#include <iostream>

Pellet::Pellet(int xPos, int yPos)
{
    this->initSprite(xPos, yPos);
}

Pellet::~Pellet()
{

}

void Pellet::initSprite(int xPos, int yPos)
{
    this->color = sf::Color::White;
    this->cicle.setFillColor(this->color);
    this->cicle.setRadius(this->radius);
    this->cicle.setPosition(sf::Vector2f(xPos, yPos));
    this->isEaten = false;
}

bool Pellet::isEatenCheck()
{
    if (this->isEaten)
    {
        return false;
    }
    return true;
}

void Pellet::eaten()
{
    this->isEaten = true;
}

void Pellet::render(sf::RenderTarget* target)
{
    if (!isEaten)
    {
        target->draw(this->cicle);
    }
    
    
}