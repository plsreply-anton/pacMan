#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "LooseState.h"

LooseState::LooseState(sf::RenderWindow* window, std::stack<State*>* states, int score)
    : State(window, states)
{
    this->initBackground();
    this->initEndText();
    this->score = score;

    std::cout << "New Loose State" << std::endl;
}

LooseState::~LooseState()
{
    this->endState();
    delete this->bgSprite;
    delete this->backSprite;
    delete this->text;
}

void LooseState::initBackground()
{
    this->bgImage.loadFromFile("../util/menuImage.png");
    this->bgImage.setSmooth(true);
    this->bgSprite = new sf::Sprite(this->bgImage);

    this->backImage.loadFromFile("../util/back.png");
    this->backImage.setSmooth(true);
    this->backSprite = new sf::Sprite(this->backImage);
    this->backSprite->setPosition(sf::Vector2f(20,830));
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
        this->quit = true;
}

void LooseState::initEndText()
{
    this->textFont.loadFromFile("../util/PacfontGood.ttf");
    int pos_x = ((sf::Vector2u(this->window->getSize()).x - 200)/2)+130;
    int pos_y = 340;
    this->shape.setPosition(sf::Vector2f(pos_x,pos_y));
    this->shape.setSize(sf::Vector2f(200, 50));
    this->shape.setFillColor(this->buttonColor);
    this->text = new sf::Text(textFont, "looser", 20);
    this->text->setFillColor(this->textColor);
    this->text->setPosition(
        sf::Vector2f(int(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text->getGlobalBounds().width / 2.f), 
                     int(this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text->getGlobalBounds().height / 2.f)));
    
    
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
    target->draw(this->shape);
    target->draw(*this->text);
    target->draw(*this->backSprite);
}

#pragma GCC diagnostic pop