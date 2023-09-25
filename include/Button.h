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

    sf::RectangleShape shape;
    //sf::Font* font;
    sf::Text* text;

    sf::Color color;
    sf::Color hoverColor;

public:

    Button(sf::RectangleShape shape, sf::Font font, sf::Color color, sf::Color hoverColor, 
            std::string text, float x, float y, float width, float height);
    virtual ~Button();

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};