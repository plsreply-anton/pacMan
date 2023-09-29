#include "../include/MainMenuState.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->bgImage.loadFromFile("../util/bg.jpg");
    this->bgSprite = new sf::Sprite(this->bgImage);
    this->bgSprite->setPosition(sf::Vector2f(0, 0));
    this->bgSprite->setScale(sf::Vector2f(2,2));

    this->font.loadFromFile("../util/PAC-FONT.TTF");   //Remove after new BG

    this->initButtons(window);
    this->buttonNumber = 0;
    std::cout << "New Menu State" << std::endl;
}

MainMenuState::~MainMenuState()
{
    this->endState();
    for (int i = 0; i < buttons.size(); i++)
    {
       delete this->buttons[i];
    }
    delete this->bgSprite;
}

void MainMenuState::initButtons(sf::RenderWindow* window)
{
    this->buttonFont.loadFromFile("../util/ARCADECLASSIC.TTF");
 
    int width = 150;
    int height = 40; 
    int pos_x = (sf::Vector2u(window->getSize()).x - width)/2;

    this->buttons.push_back(new Button(&this->buttonFont, sf::Color (119,136,153), sf::Color (15,120,133), "play", pos_x, 300, width, height));
    this->buttons.push_back(new Button(&this->buttonFont, sf::Color (119,136,153), sf::Color (15,120,133), "Leaderboard", pos_x, 360, width, height));
    this->buttons.push_back(new Button(&this->buttonFont, sf::Color (119,136,153), sf::Color (15,120,133), "Settings", pos_x, 420, width, height));
    this->buttons.push_back(new Button(&this->buttonFont, sf::Color (119,136,153), sf::Color (15,120,133), "Quit", pos_x, 480, width, height));
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !keyPressed)
    {
        this->buttonNumber += 1;
        if (this->buttonNumber >= this->buttons.size())
        {
            this->buttonNumber = this->buttons.size()-1;
        }
        
        this->setActiveButton();

        this->keyPressed = true; // Set the flag to indicate a key press
        this->debounceClock.restart(); // Start the debounce timer  
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !keyPressed)
    {
        this->buttonNumber -= 1;

        if (this->buttonNumber < 0)
        {
            this->buttonNumber = 0;
        }
        this->setActiveButton();

        this->keyPressed = true;
        this->debounceClock.restart();
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            this->keyPressed = false; // Reset the key press flag
        }
        else if (this->debounceClock.getElapsedTime().asMilliseconds() > 200)
        {
            // Adjust the debounce duration (200 milliseconds in this example)
            this->keyPressed = false; // Reset the key press flag if the key is held down for too long
            this->debounceClock.restart(); // Restart the debounce timer
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        this->buttons[buttonNumber]->buttonPressed();
    }
}

void MainMenuState::setActiveButton()
{
    for (int i = 0; i < this->buttons.size(); i++)
    {
        this->buttons[i]->setUnactiveButton();
    }
    this->buttons[this->buttonNumber]->setActiveButton();
}

sf::Text MainMenuState::setText() //Remove after fixing new BG
{
    
    sf::Text text(font, "PacMan", 30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::White);
    int pos_x = int((sf::Vector2u(this->getWindow()->getSize()).x - text.getGlobalBounds().width)/2);
    text.setPosition(sf::Vector2f(pos_x, 200));
    text.setOutlineThickness(0);

    return text;
}

void MainMenuState::update(const float& dt)
{
    this->updateKeybinds(dt);

    for (int i = 0; i < buttons.size(); i++)
    {
        this->buttons[i]->update();
        if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 0)
        {
            this->states->push(new GameState(this->getWindow(), this->states));
            this->buttons[i]->setUnactiveButton();
        } else if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 3)
        {
            this->setQuit();
        }
        
        
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->getWindow();
    }

    target->draw(this->background);
    
    target->draw(*this->bgSprite);
    target->draw(this->setText()); //Remove after fixing new BG
    
    for (int i = 0; i < buttons.size(); i++)
    {
        this->buttons[i]->render(target);
    }
    
    
}
#pragma GCC diagnostic pop