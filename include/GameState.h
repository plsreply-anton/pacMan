#pragma once

#include "State.h"
#include "Packie.h"
#include "Map.h"
#include "StatusBar.h"
#include "Ghost.h"

class GameState : public State
{
    private:

        sf::Font font;
        sf::RectangleShape bgRect;
        bool paused;

        bool keyPressed = false; // Flag to track if a key is currently pressed
        sf::Clock debounceClock; // Clock to measure key press duration

        Packie pacMan;
        Ghost blinky;
        Map* map;
        StatusBar statusBar;

    public:

        //Constructor and Destructor
        GameState(sf::RenderWindow* window, std::stack<State*>* states);
        virtual ~GameState();

        //Methods
        void checkForQuit();
        void initWorld();
        void endState();
        void updateKeybinds(const float& dt);
        void moveButton();
        void update(const float& dt);
        void render(sf::RenderTarget* target = nullptr);

};