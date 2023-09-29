#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : 
    public State
{
private:
    sf::Sprite* bgSprite;
    sf::Texture bgImage;

    std::vector<Button*> buttons;
    int buttonNumber; //Current active button

    bool keyPressed = false; // Flag to track if a key is currently pressed
    sf::Clock debounceClock; // Clock to measure key press duration

public:

    //Constructor and Destructor
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~MainMenuState();

    //initialisers
    void initButtons();
    void initBackground();

    //Methods
    void endState();
    void updateKeybinds(const float& dt);
    void moveButton();
    void setActiveButton();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};