#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->bgRect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->bgRect.setFillColor(sf::Color::Black);
    this->paused = false;
    this->initWorld();
    std::cout << "New Game State" << std::endl;
}

GameState::~GameState()
{
    this->endState(); 
}

void GameState::initWorld()
{
    this->map = new Map();
    this->map->loadMapFromFile();
    this->map->initTiles();
    
    this->statusBar.initWindow();
}

void GameState::endState()
{
    std::cout << "Ending Game State" << std::endl;
}

void GameState::updateKeybinds(const float& dt)
{
    this->checkForQuit();
}

void GameState::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->quit = true;
    }
}

void GameState::moveButton()
{
    //SKABADADO
}

void GameState::update(const float& dt)
{
    this->updateKeybinds(dt);
    this->pacMan.update(dt, this->map, this->statusBar, this->blinky);
    this->blinky.update(dt, this->map);

    if (!this->pacMan.checkAlive())
    {
        this->quit = true;
        this->states->push(new LooseState(this->window, this->states, 10));
    }
    
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->bgRect);
    this->map->render(target);
    this->pacMan.render(target);
    this->blinky.render(target);
    this->statusBar.render(target);
}

#pragma GCC diagnostic pop