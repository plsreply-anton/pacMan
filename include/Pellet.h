#pragma once

#include <SFML/Graphics.hpp>

class Pellet 
{
    private:
        sf::CircleShape cicle;
        sf::Color color;
        bool isEaten;
        int radius = 4;

    public:
        Pellet(int xPos, int yPos);
        ~Pellet();
        void initSprite(int xPos, int yPos);
        bool isEatenCheck();
        void eaten();
        void render(sf::RenderTarget* target = nullptr);

};