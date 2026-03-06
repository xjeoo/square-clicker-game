#include <iostream>
#include "Game.h"
#include <ctime>



int main()
{
    Game game;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}