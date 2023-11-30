#pragma once

#include <SFML/Graphics.hpp>
#include "Pellet.h"

class Energizer : public Pellet
{
    private:
        const int radius = 16;

    public:
        Energizer(int xPos, int yPos);

        bool powerUp() const;
        void initSprite(const int& xPos, const int& yPos);
        void render(sf::RenderTarget* target = nullptr);

};