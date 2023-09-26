#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : 
    public State
{
private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Font buttonFont;
    sf::Sprite* bgSprite;
    sf::Texture bgImage;

    std::vector<Button*> buttons;
    int buttonNumber;

    bool keyPressed = false; // Flag to track if a key is currently pressed
    sf::Clock debounceClock; // Clock to measure key press duration

    //Button* playButton;

public:
    MainMenuState(sf::RenderWindow* window);
    virtual ~MainMenuState();

    void initButtons();
    void updateKeybinds(const float& dt);

    void moveButton();
    void setActiveButton();

    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    sf::Text setHeader();
};