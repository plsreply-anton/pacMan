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
    for (int i = 0; i < buttons.size(); i++)
       delete this->buttons[i];
    this->buttons.clear();

    delete this->bgSprite;
    this->endState();
}

void MainMenuState::initBackground()
{
    this->bgImage.loadFromFile("../util/menuImage.png");
    this->bgSprite = new sf::Sprite(this->bgImage);
}

void MainMenuState::initButtons()
{ 
    const int width = 200;
    const int height = 50; 
    const int pos_x = ((sf::Vector2u(this->window->getSize()).x - width)/2)+130;

    this->buttons.push_back(new Button(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "PLAY", pos_x, 340, width, height));
    this->buttons.push_back(new Button(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "LEADERBOARD", pos_x, 420, width, height));
    this->buttons.push_back(new Button(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "SETTINGS", pos_x, 500, width, height));
    this->buttons.push_back(new Button(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "QUIT", pos_x, 580, width, height));
    this->buttons[0]->setActiveButton();
}

void MainMenuState::endState() const
{
    std::cout << "Ending Menu State" << std::endl;
}

void MainMenuState::updateInput(const float& dt, const sf::Event ev)
{
    this->moveButton(ev);
}

void MainMenuState::moveButton(const sf::Event ev)
{   
    // Navigate menu, checks if out of bounds etc
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Down && !keyPressed)
    {
        this->buttonNumber += 1;
        if (this->buttonNumber >= this->buttons.size())
            this->buttonNumber = this->buttons.size()-1;

        this->setActiveButton();
        this->keyPressed = true; 
        this->debounceClock.restart();
    }

    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Up && !keyPressed)
    {
        this->buttonNumber -= 1;
        if (this->buttonNumber < 0)
            this->buttonNumber = 0;

        this->setActiveButton();
        this->keyPressed = true;
        this->debounceClock.restart();
    }

    // Reset keyPressed if no key is pressed or key has been pressed 200ms+
    if (!(ev.type == sf::Event::KeyPressed))
            this->keyPressed = false;
    else if (this->debounceClock.getElapsedTime().asMilliseconds() > 200)
    {
        this->keyPressed = false; 
        this->debounceClock.restart();
    }

    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
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
        if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 2)
        {
            this->states->push(new SettingState(this->window, this->states));
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