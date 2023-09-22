#include "../include/game.h"
#include <iostream>
using namespace std;


Game::Game()
{
    this->initWindow();
}

Game::~Game()
{

}

int Game::getHeight() const
{
    return height;
}

int Game::getWidth() const
{
    return width;
}

void Game::setHeight(int height)
{
    this->height = height;
}

void Game::setWidth(int width)
{
    this->width = width;
}

void Game::initWindow()
{
    this->window.create(sf::VideoMode(sf::Vector2u(800, 600)), "PacMan", sf::Style::Close | sf::Style::Titlebar);
    this->window.setTitle("PacMan, by Anton");
}

void Game::update()
{
    while (this->window.pollEvent(this->ev))
    {
        if (this->ev.type == sf::Event::Closed)
        {
            this->window.close();
        } else if (this->ev.type == sf::Event::KeyPressed && sf::Keyboard::Escape)
        {
            this->window.close();
        }
        
        
    }
   
}

void Game::render()
{
    this->window.clear();

    this->window.display();

}

const sf::RenderWindow& Game::getWindow() const
{
    return this->window;
}


