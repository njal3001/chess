#include "chess/game/chess.h"

int main()
{
    Chess::Game::Chess chess;
    if (chess.init())
        chess.run();
    else
        std::cout << "Could not start Chess!" << std::endl;
}
