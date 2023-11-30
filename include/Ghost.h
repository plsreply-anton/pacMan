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
#include "PathfindingStrategy.h"

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
    PathfindingStrategy* strategy;
    Pathfinding* pathfinder;
    vector<Node*> path;
    sf::Clock debounceClock; // For setting new goalpos.
    float debounceThreshold = 3;
    bool useAstar = false;

    bool dead = false;
    GhostMode currentMode = Scatter;
    sf::Clock updateChaseClock;
    int chaseThreshold;
    sf::Clock modeClock;
    vector<sf::Vector2f> deadPos{sf::Vector2f(400,420),sf::Vector2f(420,420),sf::Vector2f(440,420)}; 

public:
    Ghost();
    Ghost(sf::Vector2f startPos);
    virtual ~Ghost() = 0;

    virtual void initGhost() = 0;
    void readSettingsFromFile(const string& filePath);

    //Getters and setters
    sf::Sprite getSprite() const;
    void changeTexture();
    void setDead(const bool& dead);

    void isTargetReached(const sf::Vector2f& currentPos);

    //Updates and render
    void move(const float& dt);
    virtual sf::Vector2f updateTargetPosition(Map *map, const sf::Vector2f& pacManPos) = 0;
    virtual void update(const float& dt, Map *map, const sf::Vector2f& pacManPo, const GhostMode& modes) = 0;
    void render(sf::RenderTarget* target);

};

