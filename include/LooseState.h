#pragma once
#include "GameState.h"
#include "Button.h"

#include <vector>

class LooseState : public State
{
    private:

        sf::Sprite* bgSprite;
        sf::Texture bgImage;

        sf::Sprite* backSprite;
        sf::Texture backImage;

        sf::RectangleShape shape;
        sf::Text* text;

        sf::Font textFont;

        sf::Color buttonColor = sf::Color (255,237,10);
        sf::Color textColor = sf::Color (255,122,0);

        int score;

    public:

        //Constructor and Destructor
        LooseState(sf::RenderWindow* window, std::stack<State*>* states, int score);
        virtual ~LooseState();

        //initialisers
        void initBackground();
        void initEndText();

        //Methods
        void endState();
        void updateKeybinds(const float& dt);
        void checkForQuit();
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};