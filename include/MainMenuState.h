#pragma once

#include "GameState.h"

class MainMenuState : 
    public State
{
private:
    sf::RectangleShape background;
    sf::Font font;

public:
    MainMenuState(sf::RenderWindow* window);
    virtual ~MainMenuState();

    void endState();

    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    sf::Text setHeader();
};