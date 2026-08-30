#include <iostream>
#include <cstdint>
#include "Board.h"

int main() {
    Board board;
    std::cout << "e2: " << board.hasWhitePawn(Square::E2) << '\n';
    std::cout << "e4: " << board.hasWhitePawn(Square::E4) << '\n';

    return 0;
}