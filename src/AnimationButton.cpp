#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "AnimationButton.h"

AnimationButton::AnimationButton(sf::Color buttonColor, sf::Color textColor, sf::Color activeTextColor,
                string text, vector<string> textVector, float x, float y, float width, float height)
{
    this->font.loadFromFile("../util/SF Atarian System.ttf");
    this->buttonColor = buttonColor;
    this->activeButtonColor = activeTextColor;

    this->textVector = textVector;
    this->initGraphics(x, y, width, height, text);

}

void AnimationButton::initGraphics(const float& x, const float& y, const float& width, const float& height, const std::string& text)
{
    // Initialize main button shape
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(this->buttonColor);

    // Initialize left arrow
    this->initArrow(this->leftArrow, true);

    // Initialize right arrow
    this->initArrow(this->rightArrow, false);

    // Initialize button text
    this->initButtonText(text);

    // Initialize current value text
    this->initCurrentValueText();
}

void AnimationButton::initArrow(sf::CircleShape& arrow, bool isLeft)
{
    arrow.setPointCount(3);
    arrow.setRadius(14);
    arrow.setOrigin(sf::Vector2f(arrow.getRadius(), arrow.getRadius()));
    
    float arrowX = isLeft ? this->shape.getPosition().x + 15 : this->shape.getPosition().x + this->shape.getGlobalBounds().width - 15;
    
    arrow.setPosition(sf::Vector2f(static_cast<int>(arrowX), 
                                   static_cast<int>(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f))));
    
    arrow.setFillColor(this->textColor);
    arrow.setRotation(isLeft ? sf::degrees(270) : sf::degrees(90));
}

void AnimationButton::initButtonText(const std::string& text)
{
    this->text = new sf::Text(this->font, text, 20);
    this->text->setPosition(
        sf::Vector2f(static_cast<int>(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
                     static_cast<int>(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f) - 15));
}

void AnimationButton::initCurrentValueText()
{
    this->currentValueText = new sf::Text(font, this->textVector[this->currentIndex], 15);
    this->currentValueText->setPosition(
        sf::Vector2f(static_cast<int>(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->currentValueText->getGlobalBounds().width / 2.f) + 40, 
                     static_cast<int>(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->currentValueText->getGlobalBounds().height / 2.f) + 5));
    this->currentValueText->setFillColor(sf::Color::Black);
}

bool AnimationButton::useAstar() const
{
    if (this->currentIndex == 0)
        return false;
    else
        return true;
}

void AnimationButton::update()
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

void AnimationButton::updateCurrentValue()
{
    this->currentValueText->setString(this->textVector[currentIndex]);
    this->currentValueText->setPosition(
        sf::Vector2f(static_cast<int>(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->currentValueText->getGlobalBounds().width / 2.f), 
                     static_cast<int>(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->currentValueText->getGlobalBounds().height) + 10));
}

void AnimationButton::moveButton(const sf::Event ev)
{

    if (ev.key.code == sf::Keyboard::Left && this->currentIndex > 0)
    {
        this->currentIndex -= 1;
        this->leftArrow.setFillColor(this->activeButtonColor);
        this->arrowClock.restart(); 
    }
    else if (ev.key.code == sf::Keyboard::Right && this->currentIndex < this->textVector.size()-1)
    {
        this->currentIndex += 1;
        this->rightArrow.setFillColor(this->activeButtonColor);
        this->arrowClock.restart();  
    }
}

void AnimationButton::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
    target->draw(*this->text);
    target->draw(*this->currentValueText);
    target->draw(this->leftArrow);
    target->draw(this->rightArrow);
}

#pragma GCC diagnostic pop