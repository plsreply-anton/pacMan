#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "SliderButton.h"

SliderButton::SliderButton(sf::Color buttonColor, sf::Color textColor, sf::Color activeTextColor,
                std::string text, float x, float y, float width, float height, bool useFloat, float min, float max)
{
    this->useFloat = useFloat;
    this->min = min;
    this->max = max;

    this->font.loadFromFile("../util/SF Atarian System.ttf");
    this->buttonColor = buttonColor;
    this->activeButtonColor = activeTextColor;
    
    this->initGraphics(x, y, width, height, text);
    this->buttonState=BTN_IDLE; 
    
}

void SliderButton::initGraphics(float x, float y, float width, float height, std::string text)
{
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(buttonColor);

    this->leftArrow.setPointCount(3);
    this->leftArrow.setRadius(14);
    this->leftArrow.setOrigin(sf::Vector2f(this->leftArrow.getRadius(), this->leftArrow.getRadius()));
    this->leftArrow.setPosition(sf::Vector2f(int(this->shape.getPosition().x +15), 
                                        int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f))));
    this->leftArrow.setFillColor(this->textColor);
    this->leftArrow.setRotation(sf::degrees(270));

    this->rightArrow.setPointCount(3);
    this->rightArrow.setRadius(14);
    this->rightArrow.setOrigin(sf::Vector2f(this->rightArrow.getRadius(), this->rightArrow.getRadius()));
    this->rightArrow.setPosition(sf::Vector2f(int(this->shape.getPosition().x + this->shape.getGlobalBounds().width -15), 
                                        int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f))));
    this->rightArrow.setFillColor(this->textColor);
    this->rightArrow.setRotation(sf::degrees(90));


    this->text = new sf::Text(this->font, text, 20);
    this->text->setPosition(
        sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
                     int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f)-15));

    stringstream stream;
    stream << fixed << setprecision(1) << this->currentValue,
    this->currentValueText = new sf::Text(font, stream.str(), 15);
    this->currentValueText->setPosition(
        sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f)+ 40, 
                     int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f) + 5));
    this->currentValueText->setFillColor(sf::Color::Black);
}

void SliderButton::update()
{
    if (this->buttonState == BTN_HOVER)
        this->text->setFillColor(this->activeButtonColor);
    else if (this->buttonState == BTN_IDLE)
        this->text->setFillColor(this->textColor);
    else if (this->buttonState == BTN_PRESSED)
        this->pressed = true;
    this->updateCurrentValue();

    if (this->arrowClock.getElapsedTime().asMilliseconds() > 200)
    {   
        this->leftArrow.setFillColor(this->textColor);
        this->rightArrow.setFillColor(this->textColor);
    }
}

void SliderButton::moveButton(sf::Event ev)
{
    if (this->useFloat)
    {
        if (ev.key.code == sf::Keyboard::Left && this->currentValue >= this->min)
        {
            this->currentValue -= .1;
            this->leftArrow.setFillColor(this->activeButtonColor);
            this->arrowClock.restart(); 
        }
        else if (ev.key.code == sf::Keyboard::Right && this->currentValue <= this->max)
        {
            this->currentValue += .1;
            this->rightArrow.setFillColor(this->activeButtonColor);
            this->arrowClock.restart();  
        }
    } else
    {
        if (ev.key.code == sf::Keyboard::Left && this->currentValue > this->min)
        {
            this->currentValue -= 1;
            this->leftArrow.setFillColor(this->activeButtonColor);
            this->arrowClock.restart(); 
        }
        else if (ev.key.code == sf::Keyboard::Right && this->currentValue < this->max)
        {
            this->currentValue += 1;
            this->rightArrow.setFillColor(this->activeButtonColor);
            this->arrowClock.restart();  
        }
    }
}

void SliderButton::updateCurrentValue()
{
    stringstream stream;
    if (useFloat)
        stream << fixed << setprecision(1) << this->currentValue;   
    else
        stream << fixed << setprecision(0) << this->currentValue;
    
    this->currentValueText->setString(stream.str());
}
    
float SliderButton::getCurrentValue()
{
    return this->currentValue;
}

void SliderButton::render(sf::RenderTarget* target)
{

    target->draw(this->shape);
    target->draw(*this->text);
    target->draw(*this->currentValueText);
    target->draw(this->leftArrow);
    target->draw(this->rightArrow);
}

#pragma GCC diagnostic pop