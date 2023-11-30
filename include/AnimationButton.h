#pragma once

#include "Button.h"
#include <iostream>

using namespace std;

class AnimationButton : public Button 
{
    private:
        int currentIndex = 0;

        sf::CircleShape rightArrow;
        sf::CircleShape leftArrow;

        vector<string> textVector;
        sf::Clock arrowClock;

    public:

        //Constructor and Destructor
        AnimationButton(sf::Color buttonColor, sf::Color textColor, sf::Color activeTextColor, 
                string text, vector<string> textVector, float x, float y, float width, float height);
        void initGraphics(const float& x, const float& y, const float& width, const float& height, const std::string& text);
        void initArrow(sf::CircleShape& arrow, bool isLeft);
        void initButtonText(const std::string& text);
        void initCurrentValueText();

        
        //Methods
        bool useAstar() const;
        void updateCurrentValue();
        void moveButton(const sf::Event ev);
        void update();
        void render(sf::RenderTarget* target);
};