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

    sf::Clock debounceClock; // For setting new goalpos.
    float debounceThreshold = 20;

public:
    Ghost();
    ~Ghost();

    void initGhost();

    void move(const float& dt);
    sf::Vector2f setNewPosition(Map *map);
    void goalReached(sf::Vector2f currentPos);
    sf::Sprite getSprite();

    void update(const float& dt, Map *map);
    void render(sf::RenderTarget* target);

};

