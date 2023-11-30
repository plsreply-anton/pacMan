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
    this->bgImage.loadFromFile("../util/sprites/menuImage.png");
    this->bgSprite = new sf::Sprite(this->bgImage);
}

void SettingState::initButtons()
{ 
    const int width = 200;
    const int height = 50; 
    const int pos_x = ((sf::Vector2u(this->window->getSize()).x - width)/2)+130;

    vector<string> searchLabels = {"Dijkstra", "Astar"};
    this->buttons.push_back(new AnimationButton(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "Pathfinder" ,searchLabels , pos_x, 340, width, height));
    this->buttons.push_back(new SliderButton(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "Ghost-Speed", pos_x, 420, width, height, true, 0.1, 2));
    this->buttons.push_back(new SliderButton(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "PacMan-Speed", pos_x, 500, width, height, true, 0.1, 2));
    this->buttons.push_back(new SliderButton(sf::Color (255,237,10), sf::Color (255,255,255), sf::Color (255,122,0), "Initial Health", pos_x, 580, width, height, false, 1, 10));
    this->buttons[0]->setActiveButton();
}

void SettingState::endState() const
{
    std::cout << "Ending Settings State" << std::endl;
}

void SettingState::updateInput(const float& dt, sf::Event ev)
{
    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
    {
        this->saveSettings();
        this->quit = true;
    }

    this->moveButton(ev);
}

void SettingState::moveButton(const sf::Event ev)
{
    // Navigate menu, checks if out of bounds etc
    if (ev.type == sf::Event::KeyPressed && !keyPressed)
    {
        switch (ev.key.code)
        {
            case sf::Keyboard::Down:
                this->buttonNumber = std::min(this->buttonNumber + 1, static_cast<int>(this->buttons.size()) - 1);
                break;
            case sf::Keyboard::Up:
                this->buttonNumber = std::max(this->buttonNumber - 1, 0);
                break;
            case sf::Keyboard::Left:
            case sf::Keyboard::Right:
                this->buttons[this->buttonNumber]->buttonPressed();
                this->buttons[buttonNumber]->moveButton(ev);
                break;
            default:
                break;
        }

        if (ev.key.code == sf::Keyboard::Down || ev.key.code == sf::Keyboard::Up)
        {
            this->setActiveButton();
            this->keyPressed = true;
            this->debounceClock.restart();
        }
    }

    // Reset keyPressed if no key is pressed or key has been pressed for 200ms+
    if (ev.type != sf::Event::KeyPressed || this->debounceClock.getElapsedTime().asMilliseconds() > 200)
    {
        this->keyPressed = false;
        this->debounceClock.restart();
    }

    if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
    {
        this->buttons[this->buttonNumber]->buttonPressed();
    }
}

void SettingState::setActiveButton()
{
    for (int i = 0; i < this->buttons.size(); i++)
        this->buttons[i]->setUnactiveButton();

    this->buttons[this->buttonNumber]->setActiveButton();
}

void SettingState::saveSettings() const
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
        if (buttons[i]->getButtonState() == 2 && buttonNumber == i)
            buttons[i]->setActiveButton();
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