#pragma once

#include "Ghost.h"

using namespace std;

class Pinky : public Ghost
{
private:

public:
    Pinky(sf::Vector2f startPos);
    ~Pinky();

    void initGhost();

    //Updates
    sf::Vector2f updateTargetPosition(Map *map, const sf::Vector2f& pacManPos);
    void update(const float& dt, Map *map, const sf::Vector2f& pacManPos, const GhostMode& mode);

};