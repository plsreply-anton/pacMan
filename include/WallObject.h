#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class WallObject
{
private:
    sf::RectangleShape rectangle;
public:
    WallObject(float startPosX, float startPosY, float width, float height);
    ~WallObject();

    void setColor(sf::Color color);
    sf::RectangleShape getRect() const;
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};
