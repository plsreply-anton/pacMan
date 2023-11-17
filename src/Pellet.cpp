#include "Pellet.h"
#include <iostream>

Pellet::Pellet(int xPos, int yPos)
{
    this->initSprite(xPos, yPos);
    
}

Pellet::~Pellet(){}

bool Pellet::powerUp()
{
    return false;
}

void Pellet::initSprite(int xPos, int yPos)
{
    this->color = sf::Color(255,255,102);
    this->cicle.setFillColor(this->color);
    this->cicle.setRadius(this->radius);
    this->cicle.setPosition(sf::Vector2f(xPos, yPos));
    this->isEaten = false;
}

void Pellet::render(sf::RenderTarget* target)
{
    if (!isEaten)
    {
        target->draw(this->cicle);
    }
}