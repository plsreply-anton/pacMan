#include "Tile.h"

#include "iostream"

Tile::Tile(int tileType, int xPos, int yPos, bool hasPellet)
    : hasPellet_(hasPellet), xPos_(xPos), yPos_(yPos) 
{
    if (hasPellet_) 
    {
        pellet_ = std::make_unique<Pellet>(xPos, yPos); // Create a Pellet if hasPellet is true
        this->tileType_ = 0;
    } else
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

void Tile::initSprite(int tileType, int xPos, int yPos)
{
    if (!tileType)
        this->color_ = sf::Color::Black;
    else
        this->color_ = sf::Color::Blue;
    
    this->rect_.setFillColor(this->color_);
    this->rect_.setSize(sf::Vector2f(this->width_, this->height_));
    this->rect_.setPosition(sf::Vector2f(static_cast<float>(xPos), static_cast<float>(yPos)));
}

int Tile::gettileType()
{
    return this->tileType_;
}

void Tile::changeHasPellet()
{   
    this->hasPellet_=false;
}

void Tile::destroyPellet()
{
    this->hasPellet_=false;
}

sf::RectangleShape Tile::getRect()
{
    return this->rect_;
}

bool Tile::hasPellet()
{
    return this->hasPellet_;
}

void Tile::render(sf::RenderTarget* target)
{
    target->draw(this->rect_);
    
    if (hasPellet_)
    {
        this->pellet_->render(target);
    }
}