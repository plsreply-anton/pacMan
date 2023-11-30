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

        const sf::Clock dtClock;
        float dt;

    public:

        //Constructor and Destructor
        Game();
        virtual ~Game();

        //Initialisers
        void initWindow();
        void initStates();

        //Methods
        void update();
        void render() const;
        void run();
        void updateSFMLEvents();
        void updateDt();

};