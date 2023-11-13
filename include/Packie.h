#pragma once

#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "StatusBar.h"
#include "Ghost.h"


class Packie
{
    private:
        sf::Sprite* packieSprite;
        sf::Texture packieOpen;
        sf::Texture packieClosed;
        float movementSpeed = 3;
        float middleposX, middleposY;
        std::string currentOrientation;
        sf::FloatRect newPacmanBounds;
        int score = 0;
        int health = 3;

        sf::Clock debounceClock; // Clock to measure close/open mouth
        sf::Clock debounceClockGhost; // Clock to measure ghost collisions

    public:
        
        //Constructor and Destructor
        Packie();
        ~Packie();

        sf::Sprite* getSprite();
        void move(const float& dt, float x_dir, float y_dir);
        bool checkForCollision(float newX, float newY, float deltaX, float deltaY, Map *map, float dir);
        void throwAround();
        void checkForPellet(Map *map);
        bool checkForGhost(Ghost &ghost);
        bool checkAlive();

        void updateMouth();    
        void update(const float& dt, Map *map, StatusBar &statusBar, Ghost &blinky);
        void render(sf::RenderTarget* target);
};