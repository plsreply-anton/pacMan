#include "../include/MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window)
    : State(window)
{
    this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(sf::Color::Blue);

    bool booltest = this->font.loadFromFile("../util/OASIS___.TTF");
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::endState()
{

}

sf::Text MainMenuState::setHeader()
{
    sf::Text text(font, "PacMan", 30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(400,300));

    return text;

}


void MainMenuState::update(const float& dt)
{
    //std::cout << "Hola from GS" << std::endl;
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->getWindow();
    }

    target->draw(this->background);
    target->draw(this->setHeader());
    
}