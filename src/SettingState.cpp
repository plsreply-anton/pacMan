#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

#include "SettingState.h"

SettingState::SettingState(sf::RenderWindow* window, std::stack<State*>* states)
    : State(window, states)
{
    this->initBackground();
    this->initButtons();
    std::cout << "New Settings State" << std::endl;
}

SettingState::~SettingState()
{
    for (Button *button : buttons)
        delete button;
    this->buttons.clear();
    delete this->bgSprite;
    this->endState();
}

void SettingState::initBackground()
{
    this->bgImage.loadFromFile("../util/menuImage.png");
    this->bgImage.setSmooth(true);
    this->bgSprite = new sf::Sprite(this->bgImage);
}

void SettingState::initButtons()
{ 
    int width = 200;
    int height = 50; 
    int pos_x = ((sf::Vector2u(this->window->getSize()).x - width)/2)+130;

    vector<string> searchLabels = {"Dijkstra", "Astar"};
    this->buttons.push_back(new AnimationButton(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "Pathfinder" ,searchLabels , pos_x, 340, width, height));
    this->buttons.push_back(new SliderButton(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "Ghost-Speed", pos_x, 420, width, height, true, 0.1, 2));
    this->buttons.push_back(new SliderButton(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "PacMan-Speed", pos_x, 500, width, height, true, 0.1, 2));
    this->buttons.push_back(new SliderButton(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "Initial Health", pos_x, 580, width, height, false, 1, 10));
    this->buttons[0]->setActiveButton();
}

void SettingState::endState()
{
    std::cout << "Ending Settings State" << std::endl;
}

void SettingState::updateInput(const float& dt, sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
    {
        this->saveSettings();
        this->quit = true;
    }
    this->moveButton(ev);
}

void SettingState::moveButton(sf::Event ev)
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
        this->buttons[this->buttonNumber]->buttonPressed();
    
    if (ev.type == sf::Event::KeyPressed && (ev.key.code == sf::Keyboard::Left || ev.key.code == sf::Keyboard::Right))
    {
        this->buttons[this->buttonNumber]->buttonPressed();
        this->buttons[buttonNumber]->moveButton(ev);
    }

}

void SettingState::setActiveButton()
{
    for (int i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->setUnactiveButton();

    this->buttons[this->buttonNumber]->setActiveButton();
}

void SettingState::saveSettings()
{
    ofstream outFile("../src/config/gameSettings.ini");

    if (outFile.is_open()) {
        outFile << "useAstar " << boolalpha << this->buttons[0]->useAstar() << endl;
        outFile << "ghostSpeedMultiplier " << this->buttons[1]->getCurrentValue() << endl;
        outFile << "pacManSpeedMultiplier " << this->buttons[2]->getCurrentValue() << endl;
        outFile << "initialHealth " << this->buttons[3]->getCurrentValue() << endl;

        outFile.close();
        cout << "Data written to gameSettings.ini successfully." << endl;
    } else {
        cerr << "Error opening file for writing." << endl;
    }

}

void SettingState::update(const float& dt)
{
    for (int i = 0; i < buttons.size(); i++)
    {
        this->buttons[i]->update();
        if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 0)
            this->buttons[i]->setActiveButton(); 
        else if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 1)
            this->buttons[i]->setActiveButton(); 
        else if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 2)
            this->buttons[i]->setActiveButton(); 
        else if (this->buttons[i]->getButtonState() == 2 && buttonNumber == 3)
            this->buttons[i]->setActiveButton();
    }
}

void SettingState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    target->draw(*this->bgSprite);
    
    for (int i = 0; i < buttons.size(); i++)
        this->buttons[i]->render(target); 
}

#pragma GCC diagnostic pop