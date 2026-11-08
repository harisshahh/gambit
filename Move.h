#pragma once
#include "Board.h"

#include <cstdint>

enum class MoveFlag : uint8_t {
    None = 0,
    Capture = 1,
    DoublePawnPush = 2,
    EnPassant = 4,
    KingCastle = 8,
    QueenCastle = 16,
    Promotion = 32,
};

inline MoveFlag operator|(MoveFlag a, MoveFlag b) {
    return static_cast<MoveFlag>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline bool hasFlag(MoveFlag flags, MoveFlag flag) {
    return (static_cast<uint8_t>(flags) & static_cast<uint8_t>(flag)) != 0;
}

struct Move {
    uint8_t from;
    uint8_t to;
    Piece movingPiece;
    Piece capturedPiece;
    MoveFlag flags;
    Piece promotionPiece;
};

struct UndoState {
    uint8_t capturedSquare;
    Piece capturedPiece;
    Color sideToMove;

    bool whiteKingSideCastle;
    bool whiteQueenSideCastle;
    bool blackKingSideCastle;
    bool blackQueenSideCastle;
    
    int enPassantTarget;
    int halfmoveClock;
    int fullmoveNumber;
};