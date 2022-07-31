#include "Game.hpp"

int main()
{
    Game game{};
    while (!game.IsDone())
    {
        game.Run();
    }
    return 0;
}