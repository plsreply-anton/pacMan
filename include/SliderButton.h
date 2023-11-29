#pragma once

#include "Button.h"
#include <iostream>
#include <iomanip>
#include <sstream>


using namespace std;

class SliderButton : public Button
{
    protected:
        sf::CircleShape rightArrow;
        sf::CircleShape leftArrow;
        float currentValue = 1;
        bool useFloat = true;
        float min = 0;
        float max = 2;
        
        sf::Clock arrowClock;

    public:

        //Constructor and Destructor
        SliderButton(sf::Color buttonColor, sf::Color textColor, sf::Color activeTextColor, 
                    std::string text, float x, float y, float width, float height, bool useFloat, float min, float max);
        void initGraphics(float x, float y, float width, float height, std::string text);
        //Methods
        void setActiveButton();
        void setUnactiveButton();
        short unsigned getButtonState();
        void buttonPressed();
        void setButtonText(string text);
        void update();
        void moveButton(sf::Event ev); 
        void updateCurrentValue();
        float getCurrentValue();
        void render(sf::RenderTarget* target);
};