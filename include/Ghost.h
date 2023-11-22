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

enum GhostMode {
    Chase,
    Scatter,
    Frightened
};


class Ghost
{
protected:
    sf::Sprite* ghostSprite;
    sf::Texture ghostTexture;
    sf::Texture energizedTexture;
    sf::Vector2f startPos;

    float movementSpeed = 1;
    float middleposX, middleposY;

    sf::Vector2f targetPosition;
    bool targetPositionReached = true;
    Pathfinding pathfinder = Pathfinding();
    vector<Node*> path;
    sf::Clock debounceClock; // For setting new goalpos.
    float debounceThreshold = 3;

    bool dead = false;
    GhostMode currentMode = Chase;
    sf::Clock updateChaseClock;
    int chaseThreshold;
    sf::Clock modeClock;

public:
    Ghost();
    //virtual Ghost(sf::Vector2f startPos);
    virtual ~Ghost() = 0;

    virtual void initGhost() = 0;

    //Getters and setters
    sf::Sprite getSprite();
    void setEnergized(bool energized);
    void setDead(bool dead);
    void setGhostMode(GhostMode mode);
    GhostMode getGhostMode();

    void isTargetReached(sf::Vector2f currentPos);

    //Updates and render
    void move(const float& dt);
    virtual sf::Vector2f updateTargetPosition(Map *map, sf::Vector2f pacManPos) = 0;
    virtual void update(const float& dt, Map *map, sf::Vector2f pacManPos) = 0;
    void render(sf::RenderTarget* target);

};

