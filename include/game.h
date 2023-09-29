#pragma once
#include "GameState.h"
#include "MainMenuState.h"

class Game
{
private:
    sf::RenderWindow* window; //Window to render graphics on
    sf::Event ev;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states; //Pointers to all different states

public:

    //Constructor and Destructor
    Game();
    virtual ~Game();

    //Getters
    const sf::RenderWindow* getWindow() const;

    //Initialisers
    void initWindow();
    void initStates();

    //Methods
    void update();
    void render();
    void run();
    void updateSFMLEvents();
    void updateDt();

};