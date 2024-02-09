#include "Tile.h"

#include "iostream"

Tile::Tile(int tileType, int xPos, int yPos, bool hasPellet, bool isEnergizer)
    : hasPellet_(hasPellet), xPos_(xPos), yPos_(yPos) 
{
    if (hasPellet_ & isEnergizer) 
    {
        pellet_ = std::make_unique<Energizer>(xPos+4, yPos+4); // Create a Pellet if hasPellet is true
        this->tileType_ = 0;
    }  
    else if (hasPellet_)
    {
        pellet_ = std::make_unique<Pellet>(xPos+18, yPos+18); // Create a Pellet if hasPellet is true
        this->tileType_ = 0;
    }
    else
    {
        this->tileType_ = tileType;
    }

    this->initSprite(tileType_, xPos, yPos);
}

Tile::Tile(const Tile& other)
    : rect_(other.rect_), color_(other.color_), tileType_(other.tileType_),
      hasPellet_(other.hasPellet_), width_(other.width_), height_(other.height_), xPos_(other.xPos_), yPos_(other.yPos_)
{
    if (other.hasPellet_) {
        pellet_ = std::make_unique<Pellet>(*other.pellet_); // Copy the Pellet if it exists
    }
}

void Tile::initSprite(const int& tileType, const int& xPos, const int& yPos)
{
    this->color_ = (tileType == 0) ? sf::Color::Black : sf::Color::Blue;
    this->rect_.setFillColor(this->color_);
    this->rect_.setSize(sf::Vector2f(this->width_, this->height_));
    this->rect_.setPosition(sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)));
}

int Tile::gettileType() const
{
    return this->tileType_;
}

void Tile::changeHasPellet()
{   
    this->hasPellet_=false;
}

void Tile::setTileColor(sf::Color color)
{
    this->rect_.setFillColor(color);
}

void Tile::destroyPellet()
{
    this->hasPellet_=false;
}

sf::RectangleShape Tile::getRect() const
{
    return this->rect_;
}

bool Tile::hasPellet() const
{
    return this->hasPellet_;
}

std::unique_ptr<Pellet> Tile::getPellet()
{
    return std::move(this->pellet_);
}

void Tile::render(sf::RenderTarget* target)
{
    target->draw(this->rect_);
    
    if (hasPellet_)
        this->pellet_->render(target);
}