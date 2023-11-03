#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Ghost.h"
#include <cmath>
using namespace std;

Ghost::Ghost()
{
    this->initGhost();
    debounceClock.restart();
    
}

Ghost::~Ghost()
{
    delete this->ghostSprite;

    for (Node* node : path) {
        delete node;
    }
}

void Ghost::initGhost()
{
    this->ghostTexture.loadFromFile("../util/Blinky.png");
    this->ghostSprite = new sf::Sprite(this->ghostTexture); 
    this->ghostSprite->setOrigin(sf::Vector2f(
                                this->ghostSprite->getGlobalBounds().width/2,
                                this->ghostSprite->getGlobalBounds().height/2));
    this->ghostSprite->setPosition(sf::Vector2f(160, 80)); 
}

void Ghost::update(const float& dt, Map *map)
{
    if (this->goalReached_)
    {
        this->newPos = this->setNewPosition(map); //txt-koord
        this->path = pathfinder.findPath(map->getintMap(), this->ghostSprite->getPosition(), this->newPos);
        this->path.erase(this->path.begin());

        cout << "STARTING POS: " << this->ghostSprite->getPosition().x/40 << " " << this->ghostSprite->getPosition().y/40 << endl;
        cout << "GOAL POS: " << this->newPos.x << " " << this->newPos.y << endl;
        cout << "Pathfinding done" << endl;
        for (auto tile : path)
        cout << tile->x << " " << tile->y << endl;
        cout << "--------" << endl;
        
        goalReached_=false;
        debounceClock.restart();
    } 
    else if (debounceClock.getElapsedTime().asSeconds() > debounceThreshold)  
    {
        // Ghost is considered stuck, reassign a new goal
        this->newPos = this->setNewPosition(map); //txt-koord
        this->path = pathfinder.findPath(map->getintMap(), this->ghostSprite->getPosition(), this->newPos);

        cout << "STARTING POS: " << this->ghostSprite->getPosition().x/40 << " " << this->ghostSprite->getPosition().y/40 << endl;
        cout << "GOAL POS: " << this->newPos.x << " " << this->newPos.y << endl;
        cout << "Pathfinding done" << endl;
        for (auto tile : path)
            cout << tile->x << " " << tile->y << endl;
        cout << "--------" << endl;
        
        goalReached_ = false;
        debounceClock.restart();
    }
 
    this->goalReached(this->ghostSprite->getPosition());
    //cout << this->ghostSprite->getPosition().x << " " <<this->ghostSprite->getPosition().y << endl;
    this->move(dt);

}

void Ghost::move(const float& dt)
{
    if (!this->path.empty()) {
        // Get the next tile in the path
        Node nextTile = *this->path.front();
        
        float x_dir = 0.0f;
        float y_dir = 0.0f;

        if (nextTile.x * 40 - this->ghostSprite->getPosition().x > 0.1) {
            x_dir = 1.0f;  // Move right
        } else if (nextTile.x * 40 - this->ghostSprite->getPosition().x < -0.1) {
            x_dir = -1.0f; // Move left
        }

        if (nextTile.y * 40 - this->ghostSprite->getPosition().y > 0.1) {
            y_dir = 1.0f;  // Move down
        } else if (nextTile.y * 40 - this->ghostSprite->getPosition().y < -0.1) {
            y_dir = -1.0f; // Move up
}
        // Calculate the movement amount based on speed and time
        float x = x_dir * movementSpeed;
        float y = y_dir * movementSpeed;
        
        // Move the ghost
        this->ghostSprite->move(sf::Vector2f(x, y));
        
        // Check if the ghost has reached the next tile
        if (std::abs(this->ghostSprite->getPosition().x - nextTile.x*40) < movementSpeed * dt &&
            std::abs(this->ghostSprite->getPosition().y - nextTile.y*40) < movementSpeed * dt) {
            // Remove the reached tile from the path
                this->path.erase(this->path.begin());
        }
    }
}

 void Ghost::goalReached(sf::Vector2f currentPos)
 {  
    if (abs(currentPos.x/40-this->newPos.x) < 5 && abs(currentPos.y/40-this->newPos.y) < 5 )
        this->goalReached_=true;
 }

sf::Vector2f Ghost::setNewPosition(Map *map) {
    // int maxRetries = 100; // Limit the number of retries
    // int retryCount = 0;

    // while (retryCount < maxRetries) {
    //     int randY = rand() % map->getTiles().size();
    //     int randX = rand() % map->getTiles()[randY].size();
    //     //cout << randY << " " << randX << endl;

    //     if (map->getTiles()[randY / 10][randX / 10]->gettileType() != 1) {
    //         //
    //         return sf::Vector2f(randX, randY); //Skickar i txt-koordinater
    //         //return sf::Vector2f(17, 2);
    //     }
        
    //     retryCount++;

        
    // }

    // // Handle the case where no walkable tile is found
    // std::cerr << "No walkable tile found after " << maxRetries << " retries." << std::endl;

    // // In this case, you might want to take specific action, e.g., terminate the ghost or reset the map.
    // // For now, just return a default position:
    // return sf::Vector2f(0, 0);

    return sf::Vector2f(17, 2);
}

void Ghost::render(sf::RenderTarget* target)
{
    target->draw(*this->ghostSprite);
}

#pragma GCC diagnostic pop