#pragma once
#include "GameState.h"
#include "MainMenuState.h"

class Game
{
private:
    //int width = 800;
    //int height = 600;

    sf::RenderWindow* window;
    sf::Event ev;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

public:

    Game();
    virtual ~Game();

    //Methods
    const sf::RenderWindow* getWindow() const;

    void initWindow();
    void initStates();
    void update();
    void render();
    void run();
    void updateSFMLEvents();
    void updateDt();

};