#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initBackground();
    this->initButtons();
    std::cout << "New Menu State" << std::endl;
}

MainMenuState::~MainMenuState()
{
    this->endState();
    for (int i = 0; i < buttons.size(); i++)
    {
       delete this->buttons[i];
    }
    this->buttons.clear();
    delete this->bgSprite;
}

void MainMenuState::initBackground()
{
    this->bgImage.loadFromFile("../util/menuImage.png");
    this->bgImage.setSmooth(true);
    this->bgSprite = new sf::Sprite(this->bgImage);
}

void MainMenuState::initButtons()
{ 
    int width = 200;
    int height = 50; 
    int pos_x = ((sf::Vector2u(this->window->getSize()).x - width)/2)+130;

    this->buttons.push_back(new Button(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "PLAY", pos_x, 340, width, height));
    this->buttons.push_back(new Button(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "LEADERBOARD", pos_x, 420, width, height));
    this->buttons.push_back(new Button(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "SETTINGS", pos_x, 500, width, height));
    this->buttons.push_back(new Button(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "QUIT", pos_x, 580, width, height));
    this->buttons[0]->setActiveButton();
}

void MainMenuState::endState()
{
    std::cout << "Ending Menu State" << std::endl;
}

void MainMenuState::updateKeybinds(const float& dt)
{
    this->checkForQuit();
    this->moveButton();
}

void MainMenuState::moveButton()
{   
    // Navigate menu, checks if out of bounds etc
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keyPressed)
    {
        this->buttonNumber += 1;
        if (this->buttonNumber >= this->buttons.size())
            this->buttonNumber = this->buttons.size()-1;

        this->setActiveButton();
        this->keyPressed = true; 
        this->debounceClock.restart();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !keyPressed)
    {
        this->buttonNumber -= 1;
        if (this->buttonNumber < 0)
            this->buttonNumber = 0;

        this->setActiveButton();
        this->keyPressed = true;
        this->debounceClock.restart();
    }

    // Reset keyPressed if no key is pressed or key has been pressed 200ms+
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            this->keyPressed = false;
    else if (this->debounceClock.getElapsedTime().asMilliseconds() > 200)
    {
        this->keyPressed = false; 
        this->debounceClock.restart();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        this->buttons[buttonNumber]->buttonPressed();
}

void MainMenuState::setActiveButton()
{
    for (int i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->setUnactiveButton();

    this->buttons[this->buttonNumber]->setActiveButton();
}



void MainMenuState::update(const float& dt)
{
    this->updateKeybinds(dt);

    for (int i = 0; i < buttons.size(); i++)
    {
        this->buttons[i]->update();
        if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 0)
        {
            this->states->push(new GameState(this->window, this->states));
            this->buttons[i]->setActiveButton();
        } 
        if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 1)
        {
            this->states->push(new HighScoreState(this->window, this->states));
            this->buttons[i]->setActiveButton();
        } 
        else if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 3)
            this->quit = true;
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(*this->bgSprite);
    
    for (int i = 0; i < buttons.size(); i++)
        this->buttons[i]->render(target);
    
}

#pragma GCC diagnostic pop