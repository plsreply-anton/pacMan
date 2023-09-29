#include "../include/GameState.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->bgImage.loadFromFile("../util/bg.jpg");
    this->bgSprite = new sf::Sprite(this->bgImage);
    this->bgSprite->setPosition(sf::Vector2f(0, 0));
    this->bgSprite->setScale(sf::Vector2f(2,2));
    this->paused = false;
    std::cout << "New Game State" << std::endl;
    this->initWorld();
}

GameState::~GameState()
{
    this->endState();
    delete this->bgSprite;
    
    for ( auto wallObj : this->WallObjectVector )
        delete wallObj;   
}

void GameState::initWorld()
{
        this->WallObjectVector.push_back(new WallObject(100, 100, 10, 100));
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

void GameState::moveButton()
{

}



void GameState::update(const float& dt)
{
    this->updateKeybinds(dt);
    this->pacMan.update(dt, this->WallObjectVector);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->getWindow();
    }
    target->draw(*this->bgSprite);
    this->pacMan.render(target);

    for (int i = 0; i < this->WallObjectVector.size(); i++)
    {
        this->WallObjectVector[i]->render(target);
    }
    
}
#pragma GCC diagnostic pop