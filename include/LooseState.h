#pragma once
#include "GameState.h"
#include "Button.h"
#include "MainMenuState.h"

#include <vector>

class LooseState : public State
{
    private:

        sf::Sprite* bgSprite;
        sf::Texture bgTexture;

        sf::Sprite* backArrowSprite;
        sf::Texture backArrowTexture;

        sf::RectangleShape rectangle;
        sf::Text* text;
        sf::Text* scoreText;

        sf::Font textFont;
        sf::Font scoreFont;

        sf::Color rectangleColor = sf::Color (255,237,10);
        sf::Color textColor = sf::Color (255,122,0);

        int score;
        

    public:

        //Constructor and Destructor
        LooseState(sf::RenderWindow* window, std::stack<State*>* states, int score);
        virtual ~LooseState();

        //initialisers
        void initBackground();
        void initEndText(int score);

        //Methods
        void endState();
        void updateKeybinds(const float& dt);
        void checkForQuit();
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};