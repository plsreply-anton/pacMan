#pragma once

#include "State.h"
#include "WallObject.h"
#include "Packie.h"

class GameState :
    public State
{
private:

    sf::Font font;
    sf::Sprite* bgSprite;
    sf::Texture bgImage;
    bool paused;

    bool keyPressed = false; // Flag to track if a key is currently pressed
    sf::Clock debounceClock; // Clock to measure key press duration

    Packie pacMan;
    std::vector<WallObject*> WallObjectVector;

public:

    //Constructor and Destructor
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    virtual ~GameState();

    //Methods
    void initWorld();
    void endState();
    void updateKeybinds(const float& dt);
    void moveButton();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

};