#include "../include/Packie.h"


Packie::Packie()
{
    this->packieOpen.loadFromFile("../util/pacMan_open.png");
    this->packieClosed.loadFromFile("../util/pacMan_closed.png");
    this->packieSprite = new sf::Sprite(this->packieClosed);
    //this->packieSprite->setScale(sf::Vector2f(0.05,0.05));    
    this->packieSprite->setOrigin(sf::Vector2f(this->packieSprite->getGlobalBounds().width/2,this->packieSprite->getGlobalBounds().height/2));
    this->packieSprite->setPosition(sf::Vector2f(400, 300)); 
    std::cout << this->packieSprite->getOrigin().x << std::endl;
}

Packie::~Packie()
{
    delete this->packieSprite;
}

void Packie::actions()
{
    
}

sf::Sprite* Packie::getSprite()
{
    return this->packieSprite;
}

void Packie::move(const float& dt, float x_dir, float y_dir)
{   
    float x = x_dir*this->movementSpeed;
    float y = y_dir*this->movementSpeed;
    this->packieSprite->move(sf::Vector2(x, y));
    this->updateMouth();
}

void Packie::updateMouth()
{
    if (this->debounceClock.getElapsedTime().asMilliseconds() < 200)
    {
        this->packieSprite->setTexture(this->packieOpen);
    }
    else
    {
        this->packieSprite->setTexture(this->packieClosed);
    }
    
    
    if (this->debounceClock.getElapsedTime().asMilliseconds() > 400)
    {
        this->debounceClock.restart();
    }
}

void Packie::update(const float& dt, const std::vector<WallObject*>& wallObj)
{   
    float deltaX = 0.f;
    float deltaY = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        deltaY = 1.f;
        this->packieSprite->setRotation(sf::degrees(90));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        deltaY = -1.f;
        this->packieSprite->setRotation(sf::degrees(270));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        deltaX = -1.f;
        this->packieSprite->setRotation(sf::degrees(180));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        deltaX = 1.f;
        this->packieSprite->setRotation(sf::degrees(0));
    }
    else
    {
        this->packieSprite->setTexture(this->packieOpen);
    }

    // Calculate the new position Pacman wants to move to
    float newX = this->packieSprite->getPosition().x + deltaX * dt * movementSpeed;
    float newY = this->packieSprite->getPosition().y + deltaY * dt * movementSpeed;

    // Check for collisions here
    if (!checkForCollision(newX, newY, wallObj))
    {
        // If there's no collision, update Pacman's position
        this->move(dt, deltaX, deltaY);
    }

}

bool Packie::checkForCollision(float newX, float newY, const std::vector<WallObject*>& wallObj)
{
    // Loop through all wall objects
    for (const WallObject* wall : wallObj) {
        sf::FloatRect pacmanBounds = this->packieSprite->getGlobalBounds();
        sf::FloatRect wallBounds = wall->getRect().getGlobalBounds();

        // Create a new FloatRect representing Pacman's new position
        sf::FloatRect newPacmanBounds(sf::Vector2f(newX, newY), sf::Vector2f(pacmanBounds.width, pacmanBounds.height));

        // Check for collision between Pacman's new position and the wall
        if (newPacmanBounds.findIntersection(wallBounds)) {
            std::cout << "HIT" << std::endl;
            return true; // Collision detected
        }
    }

    // No collision detected
    return false;
}

void Packie::render(sf::RenderTarget* target)
{
    target->draw(*this->packieSprite);
    
}