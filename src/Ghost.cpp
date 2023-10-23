#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Ghost.h"
#include <cmath>
using namespace std;

Ghost::Ghost()
{
    this->ghostTexture.loadFromFile("../util/Blinky.png");

    this->ghostSprite = new sf::Sprite(this->ghostTexture); 
    this->ghostSprite->setOrigin(sf::Vector2f(
                                this->ghostSprite->getGlobalBounds().width/2,
                                this->ghostSprite->getGlobalBounds().height/2));
    this->ghostSprite->setPosition(sf::Vector2f(100, 50)); 
    debounceClock.restart();
    
}

Ghost::~Ghost()
{
    delete this->ghostSprite;

    for (Node* node : path) {
        delete node;
    }
}

void Ghost::update(const float& dt, Map *map)
{
    if (this->goalReached_)
    {
        this-> newPos = this->setNewPosition(map); //txt-koord.
        this->path = pathfinder.findPath(map->getintMap(), this->ghostSprite->getPosition(), this->newPos);
        cout << "pathfinding done" << endl;
        goalReached_=false;
        debounceClock.restart();
    } else {
        // Check if the debounce clock has exceeded the threshold
        if (debounceClock.getElapsedTime().asSeconds() > debounceThreshold) {
            // Ghost is considered stuck, reassign a new goal
            this->newPos = this->setNewPosition(map); //txt-koord.
            this->path = pathfinder.findPath(map->getintMap(), this->ghostSprite->getPosition(), this->newPos);
            goalReached_ = false;

            // Reset the debounce clock
            debounceClock.restart();
        }
    }
 
    this->goalReached(this->ghostSprite->getPosition());

    this->move(dt);

}


void Ghost::move(const float& dt)
{
    if (!this->path.empty()) {
        // Get the next tile in the path
        Node nextTile = *this->path.front();
        
        // Calculate the direction to move
        float x_dir = (nextTile.y*10 - this->ghostSprite->getPosition().x > 0) ? 1.0f : -1.0f;
        float y_dir = (nextTile.x*10 - this->ghostSprite->getPosition().y > 0) ? 1.0f : -1.0f;
        
        // Calculate the movement amount based on speed and time
        float x = x_dir * movementSpeed * dt;
        float y = y_dir * movementSpeed * dt;
        
        // Move the ghost
        this->ghostSprite->move(sf::Vector2f(x, y));
        
        // Check if the ghost has reached the next tile
        if (std::abs(this->ghostSprite->getPosition().x - nextTile.y*10) < movementSpeed * dt &&
            std::abs(this->ghostSprite->getPosition().y - nextTile.x*10) < movementSpeed * dt) {
            // Remove the reached tile from the path
                this->path.erase(this->path.begin());
        }
    }
}

 void Ghost::goalReached(sf::Vector2f currentPos)
 {  
    if (abs(currentPos.x/10-this->newPos.x) < 5 && abs(currentPos.y/10-this->newPos.y) < 5 )
    {
        this->goalReached_=true;
    }
    
 }

sf::Vector2f Ghost::setNewPosition(Map *map) {
    int maxRetries = 100; // Limit the number of retries
    int retryCount = 0;

    while (retryCount < maxRetries) {
        int randY = rand() % map->getTiles().size();
        int randX = rand() % map->getTiles()[randY].size();
        //cout << randY << " " << randX << endl;

        if (map->getTiles()[randY / 10][randX / 10]->gettileType() != 1) {
            // return sf::Vector2f(randX, randY); //Skickar i txt-koordinater
            return sf::Vector2f(75, 61);
        }
        
        retryCount++;
    }

    // Handle the case where no walkable tile is found
    std::cerr << "No walkable tile found after " << maxRetries << " retries." << std::endl;

    // In this case, you might want to take specific action, e.g., terminate the ghost or reset the map.
    // For now, just return a default position:
    return sf::Vector2f(0, 0);
}

void Ghost::render(sf::RenderTarget* target)
{
    target->draw(*this->ghostSprite);
}

#pragma GCC diagnostic pop