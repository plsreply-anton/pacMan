#pragma once

#include "Pellet.h"


class Tile 
{
    private:
        sf::RectangleShape rect_;
        sf::Color color_;
        int tileType_;
        bool hasPellet_;
        int width_ = 40;
        int height_ = 40;
        int xPos_;
        int yPos_;
        std::unique_ptr<Pellet> pellet_;

    public:
        Tile(int tileType, int xPos, int yPos, bool hasPellet = false);      
        Tile(const Tile& other);
        void initSprite(int tileType, int xPos, int yPos);
        int gettileType();
        void destroyPellet();
        bool hasPellet();
        void changeHasPellet();
        sf::RectangleShape getRect();
        void render(sf::RenderTarget* target = nullptr);

};