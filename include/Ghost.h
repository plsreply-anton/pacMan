#pragma once

#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <iostream>

#include <queue>
#include <limits>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Map.h"

class Ghost
{
private:
    sf::Sprite* ghostSprite;
    sf::Texture ghostTexture;
    float movementSpeed = 1;
    float middleposX, middleposY;
    sf::Vector2f newPos;
    bool goalReached_ = true;

    sf::Clock debounceClock; // Clock to measure close/open mouth

public:
    Ghost();
    ~Ghost();

    sf::Sprite* getSprite();
    void move(const float& dt, float angle, Map *map);
    sf::Vector2f setNewPosition(Map *map);
    bool checkForCollision(float newX, float newY, float deltaX, float deltaY, Map *map, float dir);
    float calculateAngleError(int x, int y, float angle);
    // int distance(const Tile& tile1, const Tile& tile2);
    // void dijkstra(Map *map, sf::Vector2f source, sf::Vector2f destination);
    float getDirection(sf::Vector2f currentPos);

    void goalReached(sf::Vector2f currentPos);

    void update(const float& dt, Map *map);
    void render(sf::RenderTarget* target);

};

