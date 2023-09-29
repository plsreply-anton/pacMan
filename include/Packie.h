#pragma once

#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "WallObject.h"
class Packie
{
    private:
        sf::Sprite* packieSprite;
        sf::Texture packieOpen;
        sf::Texture packieClosed;
        float movementSpeed = 3.f;
        float middleposX, middleposY;
        std::string currentOrientation;

        sf::Clock debounceClock; // Clock to measure close/open mouth

    public:
        Packie();
        ~Packie();

        sf::Sprite* getSprite();
        void actions();
        void move(const float& dt, float x_dir, float y_dir);

        bool checkForCollision(float newX, float newY, const std::vector<WallObject*>& wallObj);

        void updateMouth();    
        void update(const float& dt, const std::vector<WallObject*>& wallObj);
        void render(sf::RenderTarget* target);
};