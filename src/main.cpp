#include "Game.h"
#include "cstdio"

int main(int argc, char** argv)
{
    Game game;
    
    bool success = game.Initialize();
    if (success)
    {
        game.RunLoop();
        
    } else {
        printf("error");
    }

    game.Shutdown();

    return 0;
}