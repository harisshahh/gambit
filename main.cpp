#include <iostream>
#include <cstdint>
#include "Board.h"

int main() {
    Board board;
    board.print();
    uint64_t e2 = 1ULL << static_cast<int>(Square::E2);
    uint64_t e7 = 1ULL << static_cast<int>(Square::E7);
    uint64_t e4 = 1ULL << static_cast<int>(Square::E4);

    std::cout << "white occupies E2: " << ((board.whitePieces() & e2) != 0) << '\n';
    std::cout << "black occupies E7: " << ((board.blackPieces() & e7) != 0) << '\n';
    std::cout << "occupied E4: " << ((board.occupied() & e4) != 0) << '\n';
    std::cout << "empty E4: " << ((board.emptySquares() & e4) != 0) << '\n';

    return 0;
}