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

        sf::Font pacManFont;
        sf::Font atariFont;

        sf::Text* text;
        sf::Text* scoreText;
        sf::Text* highScoreText;
        sf::Text* currentScoreText;
        sf::Text* playerName = new sf::Text(atariFont, "", 20);

        
        bool paused = false;
        bool endGame = false;
        bool highScore_ = false;
        bool fileRead = false;
        bool useAstar = false;
        bool keyPressed = false; 

        const string filePath = "../util/highScore.csv";

        vector<ScoreData> highScores;
        vector<sf::Sprite*> heartSprites;
       
        int initialHealth = 3;
        int health = 3;

        Map* map;
        PacMan pacMan;
        vector <Ghost*> ghosts;
        GhostMode currentMode = Scatter;
       

        sf::RectangleShape rectangle;
        sf::RectangleShape statusbarRectangle;
        sf::RectangleShape playerNameRectangle;
        sf::Texture heartTexture;
        sf::Clock blinkClock;
        sf::Clock modeClock;
        sf::Clock debounceClock;
        
        string playerNameString = "";

    public:
        //Constructor and Destructor
        GameState(sf::RenderWindow* window, std::stack<State*>* states);
        ~GameState();

        //Initializers
        void initWorld();
        void initStatusbar();

        //Methods
        void endState() const;
        void endGameDialog();

        void checkForQuit();
        void readFile();
        void writeHighScore();

        void updateGhostMode();
        void updatePlayerName();
        void updateInput(const float& dt, const sf::Event ev);
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);
};