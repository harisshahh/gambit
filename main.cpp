#include <iostream>
#include <cstdint>
#include "Board.h"

int main() {
    Board board;

    std::string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    bool loaded = board.loadFEN(startFEN);

    std::cout << "FEN loaded: " << loaded << '\n';
    board.print();

    std::string customFEN = "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2";
    loaded = board.loadFEN(customFEN);

    std::cout << "\nCustom FEN loaded: " << loaded << '\n';
    board.print();
    return 0;
}