#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "Button.h"

Button::Button(){};

Button::Button(sf::Color buttonColor, sf::Color textColor, sf::Color activeTextColor,
                std::string text, float x, float y, float width, float height)
{
    this->font.loadFromFile("../util/PacfontGood.ttf");
    this->font.setSmooth(true);

    this->buttonColor = buttonColor;
    this->activeButtonColor = activeTextColor;

    this->initGraphics(x, y, width, height, text);
}

Button::~Button()
{
    delete this->text;
    delete this->currentValueText;
}

void Button::initGraphics(const float& x, const float& y, const float& width, const float& height, const std::string& text)
{
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(buttonColor);

    this->text = new sf::Text(font, text, 20);
    
    this->text->setPosition(
        sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
                     int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f)));

}

void Button::setActiveButton()
{
    this->buttonState=BTN_HOVER;
}

void Button::setUnactiveButton()
{
    this->buttonState=BTN_IDLE;
    this->pressed = false;
}

short unsigned Button::getButtonState() const
{
    return this->buttonState;
}

bool Button::useAstar() const
{
    return false;
}

float Button::getCurrentValue() const
{
    return 0;
}

void Button::setButtonText(string text)
{
    this->text->setString(text);
}

void Button::buttonPressed()
{
    this->buttonState = BTN_PRESSED;
}

void Button::moveButton(const sf::Event ev){}
    
void Button::update()
{
    if (this->buttonState == BTN_HOVER)
        this->text->setFillColor(this->activeButtonColor);
    else if (this->buttonState == BTN_IDLE)
        this->text->setFillColor(this->textColor);
    else if (this->buttonState == BTN_PRESSED)
        this->pressed = true;
}

void Button::render(sf::RenderTarget* target)
{

    target->draw(this->shape);
    target->draw(*this->text);
}

#pragma GCC diagnostic pop