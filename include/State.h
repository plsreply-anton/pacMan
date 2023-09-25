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
    std::vector<sf::Texture> textures;
    sf::RenderWindow* window;

    public:
    State(sf::RenderWindow* window);
    virtual ~State();

    sf::RenderWindow* getWindow();
    virtual void endState() = 0;

    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};