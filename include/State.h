#pragma once

#include <vector>
#include <stack>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
    private:
        
    protected:
        std::stack<State*>* states; //Pointer to pointers for states
        std::vector<sf::Texture> textures;
        sf::RenderWindow* window;
        bool quit = false;
        
    public:

        //Constructor and Destructor
        State(sf::RenderWindow* window, std::stack<State*>* states);
        virtual ~State();

        //Getters
        const bool& getQuit() const;

        //Setters
        void setQuit();

        //Methods
        virtual void endState() const = 0;
        virtual void updateInput(const float& dt, const sf::Event ev) = 0;

        virtual void update(const float& dt) = 0;
        virtual void render(sf::RenderTarget* target = nullptr) = 0;
};