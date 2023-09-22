#include <SFML/Graphics.hpp>
#include "../include/game.h"

int main() 
{
    //srand(time(static_cast<unsigned>(0)));

    Game game;

    while(game.getWindow().isOpen())
    {
        game.update();
        game.render();
    }

    return 0;
}
