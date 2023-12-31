#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "PacMan.h"

PacMan::PacMan()
{
   this->initSprite();
   this->readSettingsFromFile("../src/config/gameSettings.ini");
}

PacMan::~PacMan()
{
    delete this->pacManSprite;
}

void PacMan::initSprite()
{
    this->pacManOpenTexture.loadFromFile("../util/sprites/pacMan_open.png");
    this->pacManClosedTexture.loadFromFile("../util/sprites/pacMan_closed.png");

    this->pacManSprite = new sf::Sprite(this->pacManClosedTexture); 
    this->pacManSprite->setOrigin(sf::Vector2f(
                                this->pacManSprite->getGlobalBounds().width/2,
                                this->pacManSprite->getGlobalBounds().height/2));
    this->pacManSprite->setPosition(sf::Vector2f(320, 480)); 
}

void PacMan::readSettingsFromFile(string filePath)
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
            if (identifier == "pacManSpeedMultiplier")
                iss >> multiplier;
            else if (identifier == "initialHealth")
                iss >> this->health;
        }
    }
    this->movementSpeed = this->movementSpeed*multiplier;
}   

sf::Sprite* PacMan::getSpritePointer()
{
    return this->pacManSprite;
}

int PacMan::getScore()
{
    return this->score;
}

float PacMan::getRotation()
{
    return this->pacManSprite->getRotation().asDegrees();
}

int PacMan::getHealth()
{
    return this->health;
}

sf::Clock PacMan::getEnergizerClock()
{
    return this->energizedClock;
}

bool PacMan::getEnergized()
{
    return this->energized;
}

sf::Clock PacMan::getCoolDownClock()
{
    return this->coolDown;
}

void PacMan::setValues(float deltaX, float deltaY, float rotation)
{
    if (deltaX < 0.1 & deltaY < 0.1)
       this->pacManSprite->setTexture(this->pacManOpenTexture);
    
    this->deltaX = deltaX;
    this->deltaY = deltaY;
    this->pacManSprite->setRotation(sf::degrees(rotation));
}

bool PacMan::checkForCollision(float newX, float newY, float deltaX, float deltaY, Map* map, float dir)
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
    sf::FloatRect pacmanBounds = this->pacManSprite->getGlobalBounds();
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

void PacMan::checkForPellet(Map *map)
{
    int tileX = this->pacManSprite->getPosition().x/40;
    int tileY = this->pacManSprite->getPosition().y/40;

    if (map->getTiles()[tileY][tileX]->hasPellet())
    {
        this->collectedPellets += 1;
        if (map->getTiles()[tileY][tileX]->getPellet()->powerUp())
        {
            this->energizedClock.restart();
            this->energized = true;
        }
        if (this->energizedClock.getElapsedTime().asSeconds() > 5)
        {
            this->energized = false;
        }
        
        this->score += 10;
        map->getTiles()[tileY][tileX]->destroyPellet();
    }

}

int PacMan::getCollectedPellets()
{
    return this->collectedPellets;
}

bool PacMan::checkForGhost(vector<Ghost*> ghosts)
{
    for (Ghost *ghost : ghosts)
    {
        if (this->pacManSprite->getGlobalBounds().findIntersection(ghost->getSprite().getGlobalBounds()))
        { 
            if (this->energized)
                ghost->setDead(true);
            return true;
        }
    }
    return false;
}

bool PacMan::checkAlive()
{
    if (this->health < 1)
        return false;
    return true;  
}

void PacMan::move(const float& dt, float x_dir, float y_dir)
{   
    float x = x_dir*this->movementSpeed;
    float y = y_dir*this->movementSpeed;

    this->pacManSprite->move(sf::Vector2(x, y));
    this->updateMouth();
    this->changeSide();
}

void PacMan::changeSide()
{
    if (this->pacManSprite->getPosition().x < 30 && 
        this->pacManSprite->getPosition().y > 400 &&
        this->pacManSprite->getPosition().y < 480 )
    {
       this->pacManSprite->setPosition(sf::Vector2f(800,420));
    }
    if (this->pacManSprite->getPosition().x > 810 && 
        this->pacManSprite->getPosition().y > 400 &&
        this->pacManSprite->getPosition().y < 480 )
    {
       this->pacManSprite->setPosition(sf::Vector2f(40,420));
    }
    
}

void PacMan::updateMouth()
{
    if (this->debounceClock.getElapsedTime().asMilliseconds() < 200)
        this->pacManSprite->setTexture(this->pacManOpenTexture);
    else
        this->pacManSprite->setTexture(this->pacManClosedTexture);
    
    if (this->debounceClock.getElapsedTime().asMilliseconds() > 400)
        this->debounceClock.restart();
}

void PacMan::update(const float& dt, Map *map, vector<Ghost*> ghosts)
{   

    // Calculate the new position Pacman wants to move to
    float newX = this->pacManSprite->getPosition().x + this->deltaX*this->movementSpeed;
    float newY = this->pacManSprite->getPosition().y + this->deltaY*this->movementSpeed;
    
    // Check for collisions here
    if (!checkForCollision(newX+20*this->deltaX, newY+20*this->deltaY, this->deltaX, this->deltaY, map, this->deltaX))
    {
        this->move(dt, this->deltaX, this->deltaY);
        this->checkForPellet(map);
    }

    if (checkForGhost(ghosts) && this->coolDown.getElapsedTime().asMilliseconds() > 1000)
    {
        if (this->energized)
        {
            this->score += 200;
            //this->energized = false;
        } else 
        { 
            this->health -= 1;
            this->coolDown.restart();
        }
        
    }
}

void PacMan::render(sf::RenderTarget* target)
{
    target->draw(*this->pacManSprite); 
}

#pragma GCC diagnostic pop