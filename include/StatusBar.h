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
    int health = 3;
    sf::Font font;
    sf::Text *text;
    std::string string;
    sf::Texture heartTexture;
    std::vector<sf::Sprite*> heartSprites;
    // sf::Sprite* heartSprite;

public:
    StatusBar();
    ~StatusBar();
    void initWindow();
    void update(const float& dt, int score, int health);
    void render(sf::RenderTarget* target = nullptr);
};

