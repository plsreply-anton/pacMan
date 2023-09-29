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
    protected:
    std::stack<State*>* states; //Pointer to pointers for states

    private:
    std::vector<sf::Texture> textures;
    sf::RenderWindow* window;

    bool quit;

    public:

    //Constructor and Destructor
    State(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~State();

    //Getters
    const bool& getQuit() const;
    sf::RenderWindow* getWindow();

    //Setters
    void setQuit();

    //Methods
    virtual void checkForQuit();
    virtual void updateKeybinds(const float& dt) = 0;

    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};