#include "../include/MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window)
    : State(window)
{
    this->bgImage.loadFromFile("../util/bg.jpg");
    this->bgSprite = new sf::Sprite(this->bgImage);
    this->bgSprite->setPosition(sf::Vector2f(0, 0));

    this->font.loadFromFile("../util/PAC-FONT.TTF");

    this->initButtons();
    this->buttonNumber = 0;
}

void MainMenuState::initButtons()
{
    this->buttonFont.loadFromFile("../util/ARCADECLASSIC.TTF");

    this->buttons.push_back(new Button(&this->buttonFont, sf::Color (119,136,153), sf::Color (15,120,133), "play", 325, 300, 150, 40));
    this->buttons[0]->setActiveButton();
    this->buttons.push_back(new Button(&this->buttonFont, sf::Color (119,136,153), sf::Color (15,120,133), "Leaderboard", 325, 360, 150, 40));
    this->buttons.push_back(new Button(&this->buttonFont, sf::Color (119,136,153), sf::Color (15,120,133), "Settings", 325, 420, 150, 40));
    
}

MainMenuState::~MainMenuState()
{
    for (int i = 0; i < buttons.size(); i++)
    {
       delete this->buttons[i];
    }
    delete this->bgSprite;
}

void MainMenuState::updateKeybinds(const float& dt)
{
    this->checkForQuit();
    this->moveButton();
}

void MainMenuState::moveButton()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keyPressed)
    {
        this->buttonNumber += 1;
        this->setActiveButton();

        keyPressed = true; // Set the flag to indicate a key press
        debounceClock.restart(); // Start the debounce timer  
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !keyPressed)
    {
        this->buttonNumber -= 1;
        this->setActiveButton();

        keyPressed = true;
        debounceClock.restart();
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            keyPressed = false; // Reset the key press flag
        }
        else if (debounceClock.getElapsedTime().asMilliseconds() > 200)
        {
            // Adjust the debounce duration (200 milliseconds in this example)
            keyPressed = false; // Reset the key press flag if the key is held down for too long
            debounceClock.restart(); // Restart the debounce timer
        }
}

void MainMenuState::setActiveButton()
{
    for (int i = 0; i < this->buttons.size(); i++)
    {
        this->buttons[i]->setUnactiveButton();
    }
    this->buttons[this->buttonNumber]->setActiveButton();
}

sf::Text MainMenuState::setHeader()
{
    sf::Text text(font, "PacMan", 30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    float width = text.getGlobalBounds().width;
    text.setPosition(sf::Vector2f(int(400-(width/2)),200));
    text.setOutlineThickness(0);

    return text;

}

void MainMenuState::update(const float& dt)
{
    this->updateKeybinds(dt);

    for (int i = 0; i < buttons.size(); i++)
    {
        this->buttons[i]->update();
    }
    
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->getWindow();
    }

    target->draw(this->background);
    
    target->draw(*this->bgSprite);
    target->draw(this->setHeader());
    
    for (int i = 0; i < buttons.size(); i++)
    {
        this->buttons[i]->render(target);
    }
    
    
}