#pragma once

#include "Ghost.h"

using namespace std;

class Clyde : public Ghost
{
private:

public:
    Clyde(sf::Vector2f startPos);
    ~Clyde();

    void initGhost();

    //Updates
    sf::Vector2f updateTargetPosition(Map *map, sf::Vector2f pacManPos);
    void update(const float& dt, Map *map, sf::Vector2f pacManPos, GhostMode mode);

};