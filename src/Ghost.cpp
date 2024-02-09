#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Ghost.h"
#include <cmath>

using namespace std;

Ghost::Ghost(){}

Ghost::Ghost(sf::Vector2f startPos) : startPos(startPos) {}

Ghost::~Ghost(){}

void Ghost::readSettingsFromFile(const string& filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    std::string line;
    float multiplier;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string identifier;
            
        if (std::getline(iss, identifier, ' ')) {
            if (identifier == "useAstar") {
                iss >> std::boolalpha >> this->useAstar;
            } else if (identifier == "ghostSpeedMultiplier") {
                iss >> multiplier;
            }
        }
    }
    this->movementSpeed = this->movementSpeed*multiplier;
}   

void Ghost::changeTexture()
{
    if (this->currentMode == Frightened)
        this->ghostSprite->setTexture(this->energizedTexture);
    else
        this->ghostSprite->setTexture(this->ghostTexture);
}

void Ghost::setDead(const bool& dead)
{
    if (this->currentMode == Frightened)
    {
        this->dead = dead;
        // this->ghostSprite->setPosition(this->startPos);
    }
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

 void Ghost::isTargetReached(const sf::Vector2f& currentPos)
 {  
    if (abs(currentPos.x/40-this->targetPosition.x) < 1 && abs(currentPos.y/40-this->targetPosition.y) < 1)
        this->targetPositionReached = true;
 }

sf::Sprite Ghost::getSprite() const
{ 
    return *this->ghostSprite;
}

void Ghost::render(sf::RenderTarget* target)
{
    //if (!this->dead)
        target->draw(*this->ghostSprite);
}

#pragma GCC diagnostic pop