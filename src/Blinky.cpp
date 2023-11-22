#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Blinky.h"
#include <cmath>
using namespace std;

Blinky::Blinky(sf::Vector2f startPos)
{
    this->startPos = startPos;
    this->initGhost();
    debounceClock.restart();
    this->chaseThreshold = 2;
    this->movementSpeed = 1.5;
}

Blinky::~Blinky()
{
    delete this->ghostSprite;
    for (Node* node : this->path)
        delete node;
    this->path.clear();
    cout << "Blinky deleted" << endl;
}

void Blinky::initGhost()
{
    this->ghostTexture.loadFromFile("../util/Blinky.png");
    this->energizedTexture.loadFromFile("../util/Energized_Ghost.png");
    this->ghostSprite = new sf::Sprite(this->ghostTexture); 
    this->ghostSprite->setOrigin(sf::Vector2f(
                                this->ghostSprite->getGlobalBounds().width/2,
                                this->ghostSprite->getGlobalBounds().height/2));
    this->ghostSprite->setPosition(this->startPos); 
}

void Blinky::update(const float& dt, Map *map, sf::Vector2f pacManPos)
{
    switch (this->currentMode)
    {
    case Chase:
        if (this->targetPositionReached || this->path.empty() || updateChaseClock.getElapsedTime().asSeconds() < chaseThreshold) {
            this->targetPosition = this->updateTargetPosition(map, pacManPos);
            cout << "TargetPosition: " << targetPosition.x << " " << targetPosition.y << endl;
            this->path = *pathfinder.findPath(map->getintMap(), this->ghostSprite->getPosition(), this->targetPosition);
            targetPositionReached = false;
            updateChaseClock.restart();
        }
        break;
    
    case Scatter:
    case Frightened:
        if (this->targetPositionReached or debounceClock.getElapsedTime().asSeconds() > debounceThreshold)
        {
            this->targetPosition = this->updateTargetPosition(map, pacManPos); 
            this->path = *pathfinder.findPath(map->getintMap(), this->ghostSprite->getPosition(), this->targetPosition);
            targetPositionReached = false;
            debounceClock.restart();
        } 
        break;
    }
 
    if (!this->path.empty())
    {
        this->isTargetReached(this->ghostSprite->getPosition());
        this->move(dt);
    }

    if (this->dead)
        this->ghostSprite->setPosition(sf::Vector2f(0,0));
}

sf::Vector2f Blinky::updateTargetPosition(Map *map, sf::Vector2f pacManPos) {
    int maxRetries = 100;
    int retryCount = 0;

    switch (this->currentMode) {
        case Chase:
            if (map->getTiles()[static_cast<int>(pacManPos.y/40)][static_cast<int>(pacManPos.x/40)]->gettileType() != TileType::Wall) {
                return sf::Vector2f(static_cast<int>(pacManPos.x/40), static_cast<int>(pacManPos.y/40));
            }
            break;

        case Scatter:
        case Frightened:
            while (retryCount < maxRetries) {
                int randY = rand() % map->getTiles().size();
                int randX = rand() % map->getTiles()[randY].size();

                if (map->getTiles()[randY][randX]->gettileType() != TileType::Wall) {
                    return sf::Vector2f(randX, randY);
                }

                retryCount++;
            }
            break;
    }

    std::cerr << "No walkable tile found after " << maxRetries << " retries." << std::endl;
    return sf::Vector2f(17, 1);
}

#pragma GCC diagnostic pop