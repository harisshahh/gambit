#include <iostream>
#include <cstdint>
#include "Board.h"

int main() {
    Board board;

    std::cout << "valid start: " << board.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") << '\n'; // need 1

    std::cout << "valid custom: " << board.loadFEN("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2") << '\n'; // need 1

    std::cout << "invalid color: " << board.loadFEN("8/8/8/8/8/8/4k3/4K3 x - - 0 1") << '\n'; //need 0

    std::cout << "invalid kings: " << board.loadFEN("8/8/8/8/8/8/8/8 w - - 0 1") << '\n'; //nedd 0

    std::cout << "invalid en passant: " << board.loadFEN("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e3 0 2") << '\n'; // need 0
    return 0;
}