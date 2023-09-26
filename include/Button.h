#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Button 
{
private:

    bool pressed;
    bool hover;
    bool active;

    sf::RectangleShape shape;
    sf::Text* text;

    sf::Color color;
    sf::Color hoverColor;

public:

    Button(sf::Font* font, sf::Color color, sf::Color hoverColor, 
            std::string text, float x, float y, float width, float height);
    virtual ~Button();

    void setActiveButton();
    void setUnactiveButton();

    void update();
    void render(sf::RenderTarget* target);
};