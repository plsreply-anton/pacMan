#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "AnimationButton.h"

AnimationButton::AnimationButton(sf::Color buttonColor, sf::Color textColor, sf::Color activeTextColor,
                string text, vector<string> textVector, float x, float y, float width, float height)
{
    this->font.loadFromFile("../util/SF Atarian System.ttf");
    this->buttonColor = buttonColor;
    this->activeButtonColor = activeTextColor;

    //this->text = new sf::Text(font, textVector[0], 40);
    
    // this->text->setPosition(
    //     sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
    //                  int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height)));
    this->buttonState=BTN_IDLE;
    this->textVector = textVector;
    this->initGraphics(x, y, width, height, text);

}

void AnimationButton::initGraphics(float x, float y, float width, float height, std::string text)
{
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(this->buttonColor);

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

    this->currentValueText = new sf::Text(font, this->textVector[this->currentIndex], 15);
    this->currentValueText->setPosition(
        sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->currentValueText->getGlobalBounds().width / 2.f)+ 40, 
                     int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->currentValueText->getGlobalBounds().height / 2.f) + 5));
    this->currentValueText->setFillColor(sf::Color::Black);
}

bool AnimationButton::useAstar()
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
    //this->currentIndex = (this->currentIndex + 1) % textVector.size();
    this->currentValueText->setString(this->textVector[currentIndex]);
    this->currentValueText->setPosition(
        sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->currentValueText->getGlobalBounds().width / 2.f), 
            int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->currentValueText->getGlobalBounds().height) + 10));
}

void AnimationButton::moveButton(sf::Event ev)
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