#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states) : states(states),window(window)
{
    // this->window = window;
    // this->states = states;
}

State::~State() {}

const bool& State::getQuit() const
{
    return this->quit;
}