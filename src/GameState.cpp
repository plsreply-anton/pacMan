#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "../include/GameState.h"

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
    
    //for ( auto wallObj : this->WallObjectVector )
    //    delete wallObj;   
}

void GameState::initWorld()
{
        //this->WallObjectVector.push_back(new WallObject(100, 100, 10, 100));
        this->map.loadMapFromFile();
        this->map.initTiles();
}

void GameState::endState()
{
    std::cout << "Ending Game State" << std::endl;
}

void GameState::updateKeybinds(const float& dt)
{
    this->checkForQuit();
    //this->moveButton();
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

}

void GameState::update(const float& dt)
{
    this->updateKeybinds(dt);
    this->pacMan.update(dt, this->map);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->bgRect);
    this->map.render(target);
    this->pacMan.render(target);    
}

#pragma GCC diagnostic pop