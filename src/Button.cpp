#include "../include/Button.h"

Button::Button(sf::RectangleShape shape, sf::Font font, sf::Color color, sf::Color hoverColor,
                std::string text, float x, float y, float width, float height)
{
    this->shape=shape;
    this->text = new sf::Text(font, text, 12);
    //this->text.setFont(*this->font);
    //this->text.setString(text);
    //this->text.setFillColor(sf::Color::White);
    //this->text.setCharacterSize(12);
    this->color = color;
    this->hoverColor = hoverColor;
}

Button::~Button()
{
    delete this->text;
}