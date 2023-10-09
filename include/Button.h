#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum buttonState{BTN_IDLE = 0, BTN_HOVER = 1, BTN_PRESSED = 2};

class Button 
{
    private:
        short unsigned buttonState;
        bool pressed;

        sf::RectangleShape shape;
        sf::Text* text;
        sf::Font font;

        sf::Color buttonColor;
        sf::Color textColor;
        sf::Color activeButtonColor;

        sf::Sprite* blinkySprite;
        sf::Texture blinkyTexture;

    public:

        //Constructor and Destructor
        Button(sf::Color buttonColor, sf::Color textColor, sf::Color activeTextColor, 
                std::string text, float x, float y, float width, float height);
        virtual ~Button();

        //Methods
        void setActiveButton();
        void setUnactiveButton();
        short unsigned getButtonState();
        void buttonPressed();
        void update();
        void render(sf::RenderTarget* target);
};