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
        void initGraphics(float x, float y, float width, float height, std::string text);
        //Methods
        bool useAstar();
        void updateCurrentValue();
        void moveButton(sf::Event ev);
        void update();
        void render(sf::RenderTarget* target);
};