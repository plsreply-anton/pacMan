#include "../include/State.h"

State::State(sf::RenderWindow* window)
{
    this->window = window;
}

State::~State()
{
    
}

sf::RenderWindow* State::getWindow()
{
    return this->window;
}