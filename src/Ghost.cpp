#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Ghost.h"
#include <cmath>

using namespace std;

Ghost::Ghost(){}

Ghost::~Ghost(){}

void Ghost::setEnergized(bool energized)
{
    if (energized)
    {
        this->currentMode = Frightened;
        this->ghostSprite->setTexture(this->energizedTexture);
    }
    else {
        this->currentMode = Chase;
        this->ghostSprite->setTexture(this->ghostTexture);
    }
}

void Ghost::setDead(bool dead)
{
    if (this->currentMode == Frightened)
        this->dead = dead;
}

void Ghost::setMode(GhostMode mode)
{
    this->currentMode = mode;
}

GhostMode Ghost::getGhostMode()
{
    return this->currentMode;
}

void Ghost::move(const float& dt)
{
    if (!this->path.empty()) {
        // Get the next tile in the path
        Node nextTile = *this->path.front();
        
        // Calculate the direction towards the center of the next tile
        sf::Vector2f targetCenter(nextTile.x * 40 + 20, nextTile.y * 40 + 20);
        sf::Vector2f direction = targetCenter - this->ghostSprite->getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalize the direction
        if (length > 0.1) {
            direction /= length;

            // Calculate the movement amount based on speed and time
            float x = direction.x * movementSpeed;
            float y = direction.y * movementSpeed;

            // Check if the remaining distance is smaller than the movement amount
            if (length < movementSpeed) {
                x = direction.x * length;
                y = direction.y * length;
            }

            // Move the ghost
            this->ghostSprite->move(sf::Vector2f(x, y));

            // Check if the ghost has reached the next tile
            if (std::abs(this->ghostSprite->getPosition().x - targetCenter.x) < 0.1 &&
                std::abs(this->ghostSprite->getPosition().y - targetCenter.y) < 0.1) {
                // Remove the reached tile from the path
                this->path.erase(this->path.begin());
            }
        }
    }
}

 void Ghost::isTargetReached(sf::Vector2f currentPos)
 {  
    if (abs(currentPos.x/40-this->targetPosition.x) < 1 && abs(currentPos.y/40-this->targetPosition.y) < 1)
        this->targetPositionReached = true;
 }

sf::Sprite Ghost::getSprite()
{ 
    return *this->ghostSprite;
}

void Ghost::render(sf::RenderTarget* target)
{
    if (!this->dead)
        target->draw(*this->ghostSprite);
}

#pragma GCC diagnostic pop