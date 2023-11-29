#pragma once

#include "Button.h"
#include "AnimationButton.h"
#include "SliderButton.h"
#include "State.h"

class SettingState : public State
{
    private:
        sf::Sprite* bgSprite;
        sf::Texture bgImage;

        std::vector<Button*> buttons;
        int buttonNumber = 0; //Current active button

        bool keyPressed = false; // Flag to track if a key is currently pressed
        sf::Clock debounceClock; // Clock to measure key press duration

    public:

        //Constructor and Destructor
        SettingState(sf::RenderWindow* window, std::stack<State*>* states);
        ~SettingState();

        //initialisers
        void initButtons();
        void initBackground();

        //Methods
        void endState();
        void updateInput(const float& dt, sf::Event ev);
        void saveSettings();
        void initKeybinds();
        void moveButton(sf::Event ev);
        void setActiveButton();
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};