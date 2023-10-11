#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Packie.h"

Packie::Packie()
{
    this->packieOpen.loadFromFile("../util/pacMan_open.png");
    this->packieClosed.loadFromFile("../util/pacMan_closed.png");

    this->packieSprite = new sf::Sprite(this->packieClosed); 
    this->packieSprite->setOrigin(sf::Vector2f(
                                this->packieSprite->getGlobalBounds().width/2,
                                this->packieSprite->getGlobalBounds().height/2));
    this->packieSprite->setPosition(sf::Vector2f(400, 250)); 
}

Packie::~Packie()
{
    delete this->packieSprite;
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
    this->throwAround();
}

void Packie::throwAround()
{
    if (this->packieSprite->getPosition().x < 10 && 
        this->packieSprite->getPosition().y > 270 &&
        this->packieSprite->getPosition().y < 330 )
    {
       this->packieSprite->setPosition(sf::Vector2f(785,300));
    }
    if (this->packieSprite->getPosition().x > 790 && 
        this->packieSprite->getPosition().y > 270 &&
        this->packieSprite->getPosition().y < 330 )
    {
       this->packieSprite->setPosition(sf::Vector2f(15,300));
    }
    
}

void Packie::updateMouth()
{
    if (this->debounceClock.getElapsedTime().asMilliseconds() < 200)
        this->packieSprite->setTexture(this->packieOpen);
    else
        this->packieSprite->setTexture(this->packieClosed);
    
    if (this->debounceClock.getElapsedTime().asMilliseconds() > 400)
        this->debounceClock.restart();
}

void Packie::update(const float& dt, Map map)
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
    float newX = this->packieSprite->getPosition().x + deltaX*this->movementSpeed;
    float newY = this->packieSprite->getPosition().y + deltaY*this->movementSpeed;
    
    // Check for collisions here
    if (!checkForCollision(newX+20*deltaX, newY+20*deltaY, deltaX, deltaY, map, deltaX))
    {
        
        this->move(dt, deltaX, deltaY);
        this->checkForPellet(map);
    }

   
}

bool Packie::checkForCollision(float newX, float newY, float deltaX, float deltaY, Map map, float dir)
{
    int tileX = newX/10;
    int tileY = newY/10;
    int dirX = 0;
    int dirY = 0;

    if (dir != 0)
        dirY=2;
    else
        dirX=2;

    

    sf::FloatRect tileBound = map.getTiles()[tileY][tileX].getRect().getGlobalBounds();
    sf::FloatRect tileBoundNeg = map.getTiles()[tileY-dirY][tileX-dirX].getRect().getGlobalBounds();
    sf::FloatRect tileBoundPos = map.getTiles()[tileY+dirY][tileX+dirX].getRect().getGlobalBounds();

    sf::FloatRect pacmanBounds = this->packieSprite->getGlobalBounds();
    sf::FloatRect newPacmanBounds = sf::FloatRect(sf::Vector2f(newX-21, newY-21), sf::Vector2f(pacmanBounds.width, pacmanBounds.height));

    // if ((newPacmanBounds.findIntersection(tileBound) 
    //     && map.getTiles()[tileY][tileX].getRect().getFillColor() == sf::Color::Red)) 
    //     {
    //         return true; // Collision detected
    //     }
    
    if ((newPacmanBounds.findIntersection(tileBoundNeg) 
        && map.getTiles()[tileY-dirY][tileX-dirX].getRect().getFillColor() == sf::Color::Red)) 
        {
            return true; // Collision detected
        }
    
    else if ((newPacmanBounds.findIntersection(tileBoundPos) 
        && map.getTiles()[tileY+dirY][tileX+dirX].getRect().getFillColor() == sf::Color::Red)) 
        {
            return true; // Collision detected
            
        }
    
    return false;
}

void Packie::checkForPellet(Map map)
{
    int tileX = this->packieSprite->getPosition().x/10;
    int tileY = this->packieSprite->getPosition().y/10;

    if (map.getTiles()[tileY][tileX].hasPellet())
    {
        std::cout << "Pellet Eaten" << std::endl;
        map.getTiles()[tileY][tileX].destroyPellet();
    }

}


void Packie::render(sf::RenderTarget* target)
{
    target->draw(*this->packieSprite);
    
}

#pragma GCC diagnostic pop