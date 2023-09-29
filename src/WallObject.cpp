#include "../include/WallObject.h"

WallObject::WallObject(float startPosX, float startPosY, float width, float height)
{
    this->rectangle.setPosition(sf::Vector2f(startPosX, startPosY));
    this->rectangle.setSize(sf::Vector2f(width, height));
    this->rectangle.setFillColor(sf::Color::Red);
}

WallObject::~WallObject()
{

}

void WallObject::update(const float& dt)
{

}

sf::RectangleShape WallObject::getRect()const
{
    return this->rectangle;
}

void WallObject::setColor(sf::Color color)
{
     this->rectangle.setFillColor(color);
}

void WallObject::render(sf::RenderTarget* target)
{
    target->draw(this->rectangle);
}