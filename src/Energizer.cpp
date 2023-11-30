#include "Energizer.h"

using namespace std;

Energizer::Energizer(int xPos, int yPos)
    : Pellet(xPos, yPos) 
    {
        this->initSprite(xPos, yPos);
    }

bool Energizer::powerUp() const
{
    return true;   
}


void Energizer::initSprite(const int& xPos, const int& yPos)
{
    this->color = sf::Color(255,255,102);
    this->cicle.setFillColor(this->color);
    this->cicle.setRadius(this->radius);
    this->cicle.setPosition(sf::Vector2f(xPos, yPos));
    this->isEaten = false;
}

void Energizer::render(sf::RenderTarget* target)
{
    if (!isEaten)
        target->draw(this->cicle);
}