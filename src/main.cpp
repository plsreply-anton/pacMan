#include "Game.h"
#include "pacManConfig.h"
#include <iostream>

int main(int argc, char* argv[]) 
{
    std::cout << argv[0] << " V " << pacMan_VERSION_MAJOR << "." << pacMan_VERSION_MINOR << std::endl;
    Game game;

    game.run();

    return 0;
}