#pragma once

#include "GameState.h"
#include "Button.h"

#include <vector>

class HighScoreState : public State
{
    private:
        string filePath = "../util/highScore.csv";

        sf::Sprite* bgSprite;
        sf::Texture bgImage;

        sf::Sprite* backSprite;
        sf::Texture backImage;

        sf::RectangleShape shape;
        sf::Text* text;

        sf::Font textFont;
        sf::Font leaderboardFont;

        sf::Color buttonColor = sf::Color (255,237,10);
        sf::Color textColor = sf::Color (255,122,0);

        std::vector<sf::Text*> leaderboard;


    public:

        //Constructor and Destructor
        HighScoreState(sf::RenderWindow* window, std::stack<State*>* states);
        virtual ~HighScoreState();

        //initialisers
        void initBackground();
        void initLeaderboard();

        //Methods
        void readFile();
        void endState();
        void updateKeybinds(const float& dt);
        void checkForQuit();
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};