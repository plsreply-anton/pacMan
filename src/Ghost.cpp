#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Ghost.h"

#include <cmath>

Ghost::Ghost()
{
    this->ghostTexture.loadFromFile("../util/Blinky.png");

    this->ghostSprite = new sf::Sprite(this->ghostTexture); 
    this->ghostSprite->setOrigin(sf::Vector2f(
                                this->ghostSprite->getGlobalBounds().width/2,
                                this->ghostSprite->getGlobalBounds().height/2));
    this->ghostSprite->setPosition(sf::Vector2f(390, 270)); 
}

Ghost::~Ghost()
{
    delete this->ghostSprite;
}


void Ghost::update(const float& dt, Map *map)
{
    if (this->goalReached_)
    {
        this-> newPos = this->setNewPosition(map);
        goalReached_=false;
    }

    this->goalReached(this->ghostSprite->getPosition());
    
     
    sf::Vector2f currentPos = this->ghostSprite->getPosition();

    float angle = this->getDirection(currentPos);
    //std::cout << angle << std::endl;

    this->move(dt, angle, map);

}

float Ghost::calculateAngleError(int x, int y, float angle)
{
    // Calculate the vector from the current position (x, y) to the goal position (newPos)
    sf::Vector2f directionVector = this->newPos - sf::Vector2f(x, y);

    // Calculate the angle of the direction vector relative to the positive x-axis
    float directionAngle = std::atan2(directionVector.y, directionVector.x);

    // Calculate the error angle by finding the difference between the direction angle and the reference angle
    float errorAngle = directionAngle - angle;

    // Normalize the error angle to be within the range of [-π, π]
    while (errorAngle > M_PI)
    {
        errorAngle -= 2 * M_PI;
    }
    while (errorAngle < -M_PI)
    {
        errorAngle += 2 * M_PI;
    }

    return errorAngle;
}

void Ghost::move(const float& dt, float angle, Map* map)
{
    // Calculate the movement speed based on dt
    float movementSpeed = this->movementSpeed;


    // Calculate the current position
    sf::Vector2f currentPosition = this->ghostSprite->getPosition();

    std::vector<std::pair<std::pair<int, int>, double>> directions = {
        {{0, -movementSpeed}, calculateAngleError(0, -movementSpeed, angle)},  // Up
        {{-movementSpeed, 0}, calculateAngleError(-movementSpeed, 0, angle)},  // Left
        {{0, movementSpeed}, calculateAngleError(0, movementSpeed, angle)},    // Down
        {{movementSpeed, 0}, calculateAngleError(movementSpeed, 0, angle)}     // Right
    };

    // Sort the directions based on angle error (ascending order)
    std::sort(directions.begin(), directions.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Iterate through sorted directions and choose the first walkable one
    for (const auto& direction : directions) {
        // Calculate the new position based on the angle and movement speed
        float angleInRadians = angle * (M_PI / 180.0);  // Convert angle to radians if it's in degrees
        float new_x = currentPosition.x + movementSpeed * cos(angleInRadians);
        float new_y = currentPosition.y + movementSpeed * sin(angleInRadians);
        std::cout<< new_x << " " << new_y << std::endl;

        const float tolerance = 0.1f; // Adjust this value as needed

        // Check if the tile in this direction is walkable within a tolerance range
        if (map->getTiles()[new_y / 10][new_x / 10]->gettileType() != 1 ||
            (std::abs((new_x / 10) - 5) < tolerance && std::abs((new_y / 10) - 5) < tolerance)) {
            // Move to the walkable tile in this direction
            this->ghostSprite->setPosition(sf::Vector2f(new_x, new_y));
            break;  // Exit the loop
}
    }
}

float Ghost::getDirection(sf::Vector2f currentPos)
{
    return atan2(currentPos.y-this->newPos.y, this->newPos.x-currentPos.x);
}

 void Ghost::goalReached(sf::Vector2f currentPos)
 {
    if (abs(currentPos.x-this->newPos.x) < 50 && abs(currentPos.y-this->newPos.y) < 50 )
    {
        this->goalReached_=true;
    }
    
 }

sf::Vector2f Ghost::setNewPosition(Map *map)
{
    int randY = rand() % map->getTiles().size();
    int randX = rand() % map->getTiles()[randY].size();

    while (map->getTiles()[randY/10][randX/10]->gettileType() == 1)
    {
        std::cout << randX/10 << " " << randY/10 << std::endl;
        randY = rand() % map->getTiles().size(); // Update randY
        randX = rand() % map->getTiles()[randY].size(); // Update randX
    }

    if (map->getTiles()[randY/10][randX/10]->gettileType() != 1)
    {
        std::cout << randX << " " << randY << std::endl;
        return sf::Vector2f(randX, randY);
    }
    else
    {
        std::cout << "Something wrong" << std::endl;
        return sf::Vector2f(randX, randY);
    }
}
void Ghost::render(sf::RenderTarget* target)
{
    target->draw(*this->ghostSprite);
}

#pragma GCC diagnostic pop