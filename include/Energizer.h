#pragma once

#include <SFML/Graphics.hpp>
#include "Pellet.h"

class Energizer : public Pellet
{
    private:
        int radius = 16;

    public:
        Energizer(int xPos, int yPos);

        bool powerUp();
        void initSprite(int xPos, int yPos);
        void render(sf::RenderTarget* target = nullptr);

};