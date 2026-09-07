#include "Game.h"

// main stays tiny on purpose.. all the real work lives inside the Game class,
// so main just builds the game and hands control over to it.
int main()
{
    Game game;    // the constructor loads all the data
    game.Run();   // let the menu loop take over from here
    return 0;
}
