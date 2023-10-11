#pragma once


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class StatusBar
{
private:
    int postionX;
    int postionY;
    sf::Font font;
    sf::Text *text;
    std::string string;

public:
    StatusBar();
    ~StatusBar();
    void initWindow();
    void update(const float& dt, int score);
    void render(sf::RenderTarget* target = nullptr);
};

