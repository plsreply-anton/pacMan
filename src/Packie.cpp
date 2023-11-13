#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Packie.h"

Packie::Packie()
{
    this->packieOpen.loadFromFile("../util/pacMan_35_open.png");
    this->packieClosed.loadFromFile("../util/pacMan_35_closed.png");

    this->packieSprite = new sf::Sprite(this->packieClosed); 
    this->packieSprite->setOrigin(sf::Vector2f(
                                this->packieSprite->getGlobalBounds().width/2,
                                this->packieSprite->getGlobalBounds().height/2));
    this->packieSprite->setPosition(sf::Vector2f(320, 480)); 
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
    if (this->packieSprite->getPosition().x < 40 && 
        this->packieSprite->getPosition().y > 400 &&
        this->packieSprite->getPosition().y < 480 )
    {
       this->packieSprite->setPosition(sf::Vector2f(800,420));
    }
    if (this->packieSprite->getPosition().x > 810 && 
        this->packieSprite->getPosition().y > 400 &&
        this->packieSprite->getPosition().y < 480 )
    {
       this->packieSprite->setPosition(sf::Vector2f(50,420));
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

void Packie::update(const float& dt, Map *map, StatusBar &statusBar, Ghost &blinky)
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

    if (checkForGhost(blinky) && this->debounceClockGhost.getElapsedTime().asMilliseconds() > 2000)
    {
        cout << "FUCKING HIT A GHOST" << endl;
        this->health -= 1;
        this->debounceClockGhost.restart();
    }
    


    statusBar.update(dt, this->score, this->health);
}

bool Packie::checkAlive()
{
    if (this->health < 1)
    {
        return false;
    }
    return true;
    
}

bool Packie::checkForCollision(float newX, float newY, float deltaX, float deltaY, Map* map, float dir)
{
    int tileX = newX/40;
    int tileY = newY/40;
    int dirX = 0;
    int dirY = 0;

    if (dir != 0)
        dirY=1;
    else
        dirX=1;

    sf::FloatRect tileBound = map->getTiles()[tileY][tileX]->getRect().getGlobalBounds();
    // sf::FloatRect tileBoundNeg = map->getTiles()[tileY-dirY][tileX-dirX]->getRect().getGlobalBounds();
    // sf::FloatRect tileBoundPos = map->getTiles()[tileY+dirY][tileX+dirX]->getRect().getGlobalBounds();

    //Get pacmanbounds adjusted for an offset
    sf::FloatRect pacmanBounds = this->packieSprite->getGlobalBounds();
    // sf::FloatRect pacManBoundsNeg = sf::FloatRect(sf::Vector2f(newX-15*dirX, newY-15*dirY), sf::Vector2f(pacmanBounds.width, pacmanBounds.height));
    // sf::FloatRect pacManBoundsPos = sf::FloatRect(sf::Vector2f(newX+15*dirX, newY+15*dirY), sf::Vector2f(pacmanBounds.width, pacmanBounds.height));
    // std::cout << tileBoundNeg.getPosition().y << " " << pacManBoundsNeg.getPosition().y << std::endl;

    if ((pacmanBounds.findIntersection(tileBound) 
        && map->getTiles()[tileY][tileX]->getRect().getFillColor() == sf::Color::Blue)) 
            return true; // Collision detected
    // else if ((pacManBoundsNeg.findIntersection(tileBoundNeg)
    //     && map->getTiles()[tileY-dirY][tileX-dirX]->getRect().getFillColor() == sf::Color::Blue))
    //         return true; // Collision detected
    // else if ((pacManBoundsPos.findIntersection(tileBoundPos) 
    //     && map->getTiles()[tileY+dirY][tileX+dirX]->getRect().getFillColor() == sf::Color::Blue))
    //         return true; // Collision detected
    
    return false;
}

void Packie::checkForPellet(Map *map)
{
    int tileX = this->packieSprite->getPosition().x/40;
    int tileY = this->packieSprite->getPosition().y/40;

    if (map->getTiles()[tileY][tileX]->hasPellet())
    {
        this->score += 10;
        map->getTiles()[tileY][tileX]->destroyPellet();
    }

}

bool Packie::checkForGhost(Ghost &ghost)
{
    if (this->packieSprite->getGlobalBounds().findIntersection(ghost.getSprite().getGlobalBounds()))
        return true;
    
    return false;
   
}

void Packie::render(sf::RenderTarget* target)
{
    target->draw(*this->packieSprite); 
}

#pragma GCC diagnostic pop