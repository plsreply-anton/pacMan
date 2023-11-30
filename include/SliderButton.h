#pragma once

#include "Button.h"
#include <iostream>
#include <iomanip>
#include <sstream>


using namespace std;

class SliderButton : public Button
{
    private:
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
        
        //Initializers
        void initGraphics(const float& x, const float& y, const float& width, const float& height, const std::string& text);
        void initArrow(sf::CircleShape& arrow, bool isLeft);
        void initButtonText(const std::string& text);
        void initCurrentValueText();

        //Methods
        float getCurrentValue() const;
        void moveButton(const sf::Event ev); 
        void updateCurrentValue();
        void update();
        void render(sf::RenderTarget* target);
};