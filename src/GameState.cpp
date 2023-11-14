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

    ghosts.push_back(new Ghost(sf::Vector2f(160, 60), blinky));
    ghosts.push_back(new Ghost(sf::Vector2f(740, 760), pinky));
    ghosts.push_back(new Ghost(sf::Vector2f(740, 60), inky));
    ghosts.push_back(new Ghost(sf::Vector2f(160, 760), clyde));
    std::cout << "New Game State" << std::endl;
}

GameState::~GameState()
{
    this->endState(); 
    delete this->map;
    for (Ghost *ghost : this->ghosts)
        delete ghost;
    this->ghosts.clear();
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
        this->quit = true;
}

void GameState::moveButton()
{
    //SKABADADO
}

void GameState::update(const float& dt)
{
    this->updateKeybinds(dt);
    this->pacMan.update(dt, this->map, this->statusBar, this->ghosts);
    for (Ghost *ghost : this->ghosts)
        ghost->update(dt, this->map);
    

    if (!this->pacMan.checkAlive())
    {
        this->quit = true;
        this->states->push(new LooseState(this->window, this->states, pacMan.getScore()));
    }
    
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(this->bgRect);
    this->map->render(target);
    this->pacMan.render(target);
    for (Ghost *ghost : this->ghosts)
        ghost->render(target);
    this->statusBar.render(target);
}

#pragma GCC diagnostic pop