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
        sf::Font textFont;
        sf::Color buttonColor = sf::Color (255,237,10);
        sf::Color textColor = sf::Color (255,122,0);
        sf::Text* text;

        std::vector<sf::Text*> leaderboard;
        sf::Font leaderboardFont;

        bool keyPressed = false; // Flag to track if a key is currently pressed
        sf::Clock debounceClock; // Clock to measure key press duration

    public:

        //Constructor and Destructor
        HighScoreState(sf::RenderWindow* window, std::stack<State*>* states);
        virtual ~HighScoreState();

        //initialisers
        void initBackground();
        void initLeaderboard();
        void readFile();

        //Methods
        void endState();
        void updateKeybinds(const float& dt);
        void checkForQuit();
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};