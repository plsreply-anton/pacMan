#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
    int width = 800;
    int height = 600;

    sf::RenderWindow window;
    sf::Event ev;

public:
    Game();
    virtual ~Game();

    int getHeight() const;
    int getWidth() const;
    void setHeight(int heigth);
    void setWidth(int width);

    const sf::RenderWindow& getWindow() const;

    void initWindow();
    void update();
    void render();


};