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
#include "Pathfinding.h"

using namespace std;


class Ghost
{
private:
    sf::Sprite* ghostSprite;
    sf::Texture ghostTexture;
    float movementSpeed = 0.5;
    float middleposX, middleposY;
    sf::Vector2f newPos;
    bool goalReached_ = true;
    Pathfinding pathfinder = Pathfinding();
    vector<Node*> path;

    sf::Clock debounceClock; // Clock to measure close/open mouth
    float debounceThreshold = 5.0;

public:
    Ghost();
    ~Ghost();

    sf::Sprite* getSprite();
    void move(const float& dt);
    sf::Vector2f setNewPosition(Map *map);
    bool checkForCollision(float newX, float newY, float deltaX, float deltaY, Map *map, float dir);
    float calculateAngleError(int x, int y, float angle);
    float getDirection(sf::Vector2f currentPos);vector<Node*> findPath(vector<vector<int>>& map, sf::Vector2f start, sf::Vector2f goal);
    void goalReached(sf::Vector2f currentPos);

    void update(const float& dt, Map *map);
    void render(sf::RenderTarget* target);

};

