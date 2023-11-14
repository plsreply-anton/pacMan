#include "Game.h"
#include <iostream>

using namespace std;


Game::Game()
{
    this->initWindow();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
        this->states = std::stack<State*>();
    }
    
}
 
void Game::initWindow()
{
    int width = 860;
    int height = 880;
    ifstream ifs("../src/config/window.ini");

    string title = "PacMan, by Anton";
    sf::VideoMode window_bounds(sf::Vector2u(width, height));
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned int antialiasing_level = 0;
    cout << "Current Working Directory: " << filesystem::current_path() << endl;
    
    if (ifs.is_open())
    {
        cout << "open" << endl;
        getline(ifs, title);
        ifs >> width >> height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        
        window_bounds = sf::VideoMode(sf::Vector2u(width, height));
    } 
    else if(!ifs.is_open())
    {
        cerr << "Error: Could not open ../src/config/window.ini" << endl;
    }

    sf::ContextSettings window_settings;
    window_settings.antialiasingLevel = antialiasing_level;

    this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Default, window_settings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->states));
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit())
        {
            delete this->states.top();
            this->states.pop();
        }
    } else if (this->states.empty())
    {
        std::cout << "No More States - Exiting" << std::endl;
        this->window->close();
    }
    sf::sleep(sf::microseconds(50));
    
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        if (this->ev.type == sf::Event::Closed)
        {
            this->window->close();
        } else if ((this->ev.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
        {
            this->window->close();
        } 
    }

}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

void Game::render()
{
    this->window->clear();

    //Render items
    if (!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();

}

void Game::updateDt()
{
    this->dt = this->dtClock.getElapsedTime().asSeconds();
}
