#include "chess/game/chess.h"

int main()
{
    using namespace Game;
    Chess chess;

    if (chess.init())
        chess.run();
    else
        std::cout << "Could not start Chess!" << std::endl;
}
