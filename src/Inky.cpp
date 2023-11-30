#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Inky.h"
#include <cmath>
using namespace std;

Inky::Inky(sf::Vector2f startPos) : Ghost(startPos)
{
    this->initGhost();
    this->chaseThreshold = 3;
    this->movementSpeed = 0.7;
    this->readSettingsFromFile("../src/config/gameSettings.ini");
    
    if (this->useAstar)
        this->strategy =new AStarStrategy();
    else
        this->strategy = new DijkstraStrategy();
    
    this->pathfinder = new Pathfinding(this->strategy);
}

Inky::~Inky()
{
    delete this->ghostSprite;
    for (Node* node : this->path)
        delete node;
    this->path.clear();
    delete this->strategy;
    delete this->pathfinder;
}

void Inky::initGhost()
{
    this->ghostTexture.loadFromFile("../util/sprites/inky.png");
    this->energizedTexture.loadFromFile("../util/sprites/energized_Ghost.png");
    this->ghostSprite = new sf::Sprite(this->ghostTexture); 
    this->ghostSprite->setOrigin(sf::Vector2f(
                                this->ghostSprite->getGlobalBounds().width/2,
                                this->ghostSprite->getGlobalBounds().height/2));
    this->ghostSprite->setPosition(this->startPos); 
}

void Inky::update(const float& dt, Map *map, const sf::Vector2f& pacManPos, const GhostMode& mode)
{
    this->currentMode = mode;
    this->changeTexture();
    switch (this->currentMode)
    {
    case Chase:
        if (this->targetPositionReached || this->path.empty() || updateChaseClock.getElapsedTime().asSeconds() < chaseThreshold) {
            this->targetPosition = this->updateTargetPosition(map, pacManPos);
            this->path = *pathfinder->findPath(map->getintMap(), this->ghostSprite->getPosition(), this->targetPosition);
            targetPositionReached = false;
            updateChaseClock.restart();
        }
        break;
    
    case Scatter:
    case Frightened:
        if (this->targetPositionReached or debounceClock.getElapsedTime().asSeconds() > debounceThreshold)
        {
            this->targetPosition = this->updateTargetPosition(map, pacManPos); 
            this->path = *pathfinder->findPath(map->getintMap(), this->ghostSprite->getPosition(), this->targetPosition);
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

sf::Vector2f Inky::updateTargetPosition(Map *map, const sf::Vector2f& pacManPos) {
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