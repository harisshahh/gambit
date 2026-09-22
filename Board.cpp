#include "Board.h"
#include <iostream>

Board::Board() {
    whitePawns = 0xFFFFFULL;

}
bool Board::hasWhitePawn(Square square) const {
    return whitePawns & (1ULL << static_cast<int>(square));
}


