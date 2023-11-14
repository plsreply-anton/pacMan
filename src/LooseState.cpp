#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "LooseState.h"

LooseState::LooseState(sf::RenderWindow* window, std::stack<State*>* states, int score)
    : State(window, states)
{
    this->initBackground();
    this->initEndText(score);
    this->score = score;

    this->textFont.loadFromFile("../util/PacfontGood.ttf");
    this->scoreFont.loadFromFile("../util/SF Atarian System.ttf");

    std::cout << "New Loose State" << std::endl;
}

LooseState::~LooseState()
{
    this->endState();
    delete this->bgSprite;
    delete this->backArrowSprite;
    delete this->text;
    delete this->scoreText;
}

void LooseState::initBackground()
{
    this->bgTexture.loadFromFile("../util/menuImage.png");
    this->bgTexture.setSmooth(true);
    this->bgSprite = new sf::Sprite(this->bgTexture);

    this->backArrowTexture.loadFromFile("../util/BackArrow.png");
    this->backArrowTexture.setSmooth(true);
    this->backArrowSprite = new sf::Sprite(this->backArrowTexture);
    this->backArrowSprite->setPosition(sf::Vector2f(20,830));
}

void LooseState::endState()
{
    std::cout << "Ending LooserState" << std::endl;
}

void LooseState::updateKeybinds(const float& dt)
{
    this->checkForQuit();
}

void LooseState::checkForQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->quit = true;
    }
}

void LooseState::initEndText(int score)
{
    
    int pos_x = ((sf::Vector2u(this->window->getSize()).x - 200)/2)+130;
    int pos_y = 340;
    this->rectangle.setPosition(sf::Vector2f(pos_x,pos_y));
    this->rectangle.setSize(sf::Vector2f(200, 50));
    this->rectangle.setFillColor(this->rectangleColor);
    this->text = new sf::Text(textFont, "looser", 20);
    this->text->setFillColor(this->textColor);
    this->text->setPosition(
        sf::Vector2f(int(this->rectangle.getPosition().x + (this->rectangle.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
                     int(this->rectangle.getPosition().y + (this->rectangle.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f)));
    
    
    std::string scoreString = "your score: ";
    scoreString += std::to_string(score);
    this->scoreText = new sf::Text(scoreFont, scoreString, 14);
    this->scoreText->setFillColor(this->textColor);
    this->scoreText->setPosition(
        sf::Vector2f(int(this->rectangle.getPosition().x + (this->rectangle.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
                     int(this->rectangle.getPosition().y + (this->rectangle.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f) + 40));
    
    
}

void LooseState::update(const float& dt)
{
    this->updateKeybinds(dt);
}

void LooseState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(*this->bgSprite);
    target->draw(this->rectangle);
    target->draw(*this->text);
    target->draw(*this->scoreText);
    target->draw(*this->backArrowSprite);
}

#pragma GCC diagnostic pop