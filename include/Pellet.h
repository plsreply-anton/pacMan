#pragma once

#include <SFML/Graphics.hpp>

class Pellet 
{
    protected:
        sf::CircleShape cicle;
        sf::Color color;
        bool isEaten;
        int radius = 4;

    public:
        Pellet(int xPos, int yPos);
        virtual ~Pellet();
        virtual bool powerUp();
        virtual void initSprite(int xPos, int yPos);
        virtual void render(sf::RenderTarget* target = nullptr);

};