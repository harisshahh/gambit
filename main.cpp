#include <iostream>
#include <cstdint>
#include "Board.h"
#include "Move.h"

int main() {

    Move move{12, 28, Piece::WhitePawn, Piece::Empty, MoveFlag::DoublePawnPush, Piece::Empty};
    std::cout << "from: " << static_cast<int>(move.from) << "\n";
    std::cout << "to: " << static_cast<int>(move.to) << "\n";
    std::cout << "double pawn push: " << hasFlag(move.flags, MoveFlag::DoublePawnPush) << "\n";


    return 0;
}