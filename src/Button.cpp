#include "../include/Button.h"

Button::Button(sf::Font* font, sf::Color color, sf::Color hoverColor,
                std::string text, float x, float y, float width, float height)
{
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->text = new sf::Text(*font, text, 20);
    this->color = color;
    this->shape.setFillColor(color);
    this->hoverColor = hoverColor;
    this->text->setPosition(
        sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
                     int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f)));
    this->active=false;
}

Button::~Button()
{
    delete this->text;
}

void Button::setActiveButton()
{
    this->active=true;
}

void Button::setUnactiveButton()
{
    this->active=false;
}

void Button::update()
{
    if (this->active)
    {
        this->shape.setFillColor(this->hoverColor);
    } else
    {
        this->shape.setFillColor(this->color);
    }
    
}

void Button::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(*this->text);
}