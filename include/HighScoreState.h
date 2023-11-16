#pragma once

#include "GameState.h"
#include "Button.h"

#include <vector>

class HighScoreState : public State
{
    private:
        string filePath = "../util/highScore.csv";

        sf::Sprite* bgSprite;
        sf::Texture bgTexture;

        sf::Sprite* backArrowSprite;
        sf::Texture backArrowTexture;

        sf::RectangleShape shape;
        sf::Text* text;

        sf::Font headerFont;
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
        void updateInput(const float& dt, sf::Event ev);
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};