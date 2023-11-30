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
        //Constructor and destructor
        Pellet(int xPos, int yPos);
        virtual ~Pellet();

        //Initializer
        virtual void initSprite(const int& xPos, const int& yPos);

        virtual bool powerUp() const;
        virtual void render(sf::RenderTarget* target = nullptr);
};