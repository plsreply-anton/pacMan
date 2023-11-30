#pragma once

#include "Ghost.h"

using namespace std;

class Inky : public Ghost
{
private:

public:
    Inky(sf::Vector2f startPos);
    ~Inky();

    void initGhost();

    //Updates
    sf::Vector2f updateTargetPosition(Map *map, const sf::Vector2f& pacManPos);
    void update(const float& dt, Map *map, const sf::Vector2f& pacManPos, const GhostMode& mode);

};