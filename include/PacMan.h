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


class PacMan
{
    private:
        sf::Sprite* pacManSprite;
        sf::Texture pacManOpenTexture;
        sf::Texture pacManClosedTexture;

        float middleposX, middleposY;
        std::string currentOrientation;
        sf::FloatRect newPacmanBounds;

        float movementSpeed = 3;
        int score = 0;
        int health = 3;

        sf::Clock debounceClock; // Clock to measure close/open mouth
        sf::Clock healthDebounceClock; // Clock to measure ghost collisions

    public:
        
        PacMan();
        ~PacMan();
        void initSprite();

        sf::Sprite* getSpritePointer();
        int getScore();

        void move(const float& dt, float x_dir, float y_dir);
        bool checkForCollision(float newX, float newY, float deltaX, float deltaY, Map *map, float dir);
        void changeSide();
        void checkForPellet(Map *map);
        bool checkForGhost(vector<Ghost*> ghosts);
        bool checkAlive();
        void updateMouth(); 

        void update(const float& dt, Map *map, StatusBar &statusBar, vector<Ghost*> ghosts);
        void render(sf::RenderTarget* target);
};