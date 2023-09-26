#include "../include/GameState.h"

GameState::GameState(sf::RenderWindow* window)
    : State(window)
{

}

GameState::~GameState()
{

}

void GameState::endState()
{

}

void GameState::updateKeybinds(const float& dt)
{
    this->checkForQuit();
}

void GameState::update(const float& dt)
{
    this->updateKeybinds(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
       std::cout << "Hola from GS" << std::endl;
    }
}

void GameState::render(sf::RenderTarget* target)
{

}