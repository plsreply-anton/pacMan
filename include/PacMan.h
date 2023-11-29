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

        float movementSpeed = 2;
        int score = 0;
        int health = 4;
        float deltaX = 0.f;
        float deltaY = 0.f;
        float rotation = 0;
        bool energized = false;
        sf::Clock energizedClock;
        

        sf::Clock debounceClock; // Clock to measure close/open mouth
        sf::Clock coolDown; // Clock to measure ghost collisions

    public:
        
        PacMan();
        ~PacMan();

        void initSprite();
        void readSettingsFromFile(string filePath);

        //Getters and setters
        sf::Sprite* getSpritePointer();
        int getScore();
        float getRotation();
        int getHealth();
        sf::Clock getEnergizerClock();
        bool getEnergized();
        sf::Clock getCoolDownClock();
        void setValues(float deltaX, float deltaY, float rotation);
        
        //Checkers
        bool checkForCollision(float newX, float newY, float deltaX, float deltaY, Map *map, float dir);
        void checkForPellet(Map *map);
        bool checkForGhost(vector<Ghost*> ghosts);
        bool checkAlive();

        //Updates and render
        void move(const float& dt, float x_dir, float y_dir);
        void changeSide();
        void updateMouth(); 
        void update(const float& dt, Map *map, vector<Ghost*> ghosts);
        void render(sf::RenderTarget* target);
};