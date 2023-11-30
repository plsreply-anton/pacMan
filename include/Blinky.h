#pragma once

#include "Ghost.h"

using namespace std;

class Blinky : public Ghost
{
private:

public:
    Blinky(sf::Vector2f startPos);
    ~Blinky() ;

    void initGhost();

    //Updates
    sf::Vector2f updateTargetPosition(Map *map, const sf::Vector2f& pacManPos);
    void update(const float& dt, Map *map, const sf::Vector2f& pacManPos, const GhostMode& mode);

};