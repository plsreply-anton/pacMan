#pragma once

#include "State.h"
#include "PacMan.h"
#include "Map.h"
#include "Ghost.h"
#include "Blinky.h"
#include "Inky.h"
#include "Pinky.h"
#include "Clyde.h"

struct ScoreData {
    std::string line;
    int score;
};

class GameState : public State
{
    private:

        sf::Font looserFont;
        sf::Font textFont;
        sf::Text* text;
        sf::Text* scoreText;
        sf::Text* highScoreText;
        sf::RectangleShape bgRect;
        bool paused;
        bool endGame = false;
        string filePath = "../util/highScore.csv";
        std::vector<ScoreData> highScores;
        bool highScore_ = false;
        bool fileRead = false;
        bool useAstar = false;
        int initialHealth = 3;

        bool keyPressed = false; // Flag to track if a key is currently pressed
        sf::Clock debounceClock; // Clock to measure key press duration

        PacMan pacMan;
        vector <Ghost*> ghosts;
        Map* map;

        sf::RectangleShape rectangle;
        sf::RectangleShape statusbarRectangle;
        sf::RectangleShape playerNameRectangle;

        int health = 3;
        sf::Font font;
        sf::Text *currentScoreText;
        sf::Texture heartTexture;
        std::vector<sf::Sprite*> heartSprites;
        sf::Clock blinkClock;
        sf::Clock modeClock;
        GhostMode currentMode = Scatter;
        sf::Text* playerName = new sf::Text(textFont, "", 20);
        string playerNameString = "";

    public:
        //Constructor and Destructor
        GameState(sf::RenderWindow* window, std::stack<State*>* states);
        ~GameState();

        //Methods
        void updateGhostMode();
        void updatePlayerName();
        void writeHighScore();
        void checkForQuit();
        void initWorld();
        void initStatusbar();
        void endState();
        void updateInput(const float& dt, sf::Event ev);
        void endGameDialog();
        void readFile();
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);

};