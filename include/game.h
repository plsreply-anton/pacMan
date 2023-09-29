#pragma once
#include "GameState.h"
#include "MainMenuState.h"

class Game
{

    private:

    protected:
        sf::RenderWindow* window; //Window to render graphics on
        std::stack<State*> states; //Pointers to all different states
    
        sf::Event ev;

        sf::Clock dtClock;
        float dt;

    public:

        //Constructor and Destructor
        Game();
        virtual ~Game();

        //Getters
        const sf::RenderWindow* getWindow() const;

        //Initialisers
        void initWindow();
        void initStates();

        //Methods
        void update();
        void render();
        void run();
        void updateSFMLEvents();
        void updateDt();

};