#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

enum buttonState{BTN_IDLE = 0, BTN_HOVER = 1, BTN_PRESSED = 2};

class Button 
{
    protected:
        short unsigned buttonState;
        bool pressed;

        sf::RectangleShape shape;
        sf::Text* text;
        sf::Text* currentValueText;
        sf::Font font;

        sf::Color buttonColor;
        sf::Color textColor;
        sf::Color activeButtonColor;

    public:

        //Constructor and Destructor
        Button();
        Button(sf::Color buttonColor, sf::Color textColor, sf::Color activeTextColor, 
                std::string text, float x, float y, float width, float height);
        virtual ~Button();

        //Methods
        void setActiveButton();
        void setUnactiveButton();
        short unsigned getButtonState();
        void buttonPressed();
        void setButtonText(string text);
        virtual bool useAstar();
        virtual float getCurrentValue();
        virtual void moveButton(sf::Event ev);
        virtual void update();
        virtual void render(sf::RenderTarget* target);
};