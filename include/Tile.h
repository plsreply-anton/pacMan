#pragma once

#include "Pellet.h"
#include "Energizer.h"


class Tile 
{
    private:
        sf::RectangleShape rect_;
        sf::Color color_;
        int tileType_;
        bool hasPellet_;
        const int width_ = 40;
        const int height_ = 40;
        int xPos_;
        int yPos_;
        std::unique_ptr<Pellet> pellet_;


    public:
        //Constructor
        Tile(int tileType, int xPos, int yPos, bool hasPellet = false, bool isEnergizer = false);  

        //Copy constructor
        Tile(const Tile& other);

        //Initializer
        void initSprite(const int& tileType, const int& xPos, const int& yPos);

        //Getters and setters
        int gettileType() const;
        sf::RectangleShape getRect() const;
        bool hasPellet()const ;
        std::unique_ptr<Pellet> getPellet();
        void changeHasPellet();
        void destroyPellet();

        void render(sf::RenderTarget* target = nullptr);
};