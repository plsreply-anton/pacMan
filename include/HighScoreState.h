#pragma once

#include "GameState.h"
#include "Button.h"

#include <vector>

class HighScoreState : public State
{
    private:
        const string filePath = "../util/highScore.csv";

        sf::Sprite* bgSprite;
        sf::Texture bgTexture;

        sf::RectangleShape rectangle;
        sf::Text* text;

        sf::Font atariFont;
        sf::Font pacManFont;

        const sf::Color buttonColor = sf::Color (255,237,10);
        const sf::Color textColor = sf::Color (255,122,0);

        vector<sf::Text*> leaderboard;


    public:

        //Constructor and Destructor
        HighScoreState(sf::RenderWindow* window, std::stack<State*>* states);
        virtual ~HighScoreState();

        //initialisers
        void initBackground();
        void initLeaderboard();

        //Methods
        void readFile();
        void endState() const;
        void updateInput(const float& dt, const sf::Event ev);
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};