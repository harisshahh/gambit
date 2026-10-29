#include "Board.h"
#include <iostream>
#include <sstream>
#include<string>

Board::Board() {
    whitePawns = 0x00000000000000FF00ULL;
    whiteKnights = 0x0000000000000042ULL;
    whiteBishops = 0x0000000000000024ULL;
    whiteRooks = 0x0000000000000081ULL;
    whiteQueens = 0x0000000000000008ULL;
    whiteKing = 0x0000000000000010ULL;
    blackPawns = 0x00FF000000000000ULL;
    blackKnights = 0x4200000000000000ULL;
    blackBishops = 0x2400000000000000ULL;
    blackRooks = 0x8100000000000000ULL;
    blackQueens = 0x0800000000000000ULL;
    blackKing = 0x1000000000000000ULL;

    currentSide = Color::White;

    whiteKingSideCastle = true;
    whiteQueenSideCastle = true;
    blackKingSideCastle = true;
    blackQueenSideCastle = true;

    enPassantTarget = -1;
    halfmoveClock = 0;
    fullmoveNumber = 1;
}
Piece Board::getPiece(Square square) const {
    uint64_t bit = 1ULL << static_cast<int>(square);

    if (whitePawns & bit) return Piece::WhitePawn;
    if (whiteKnights & bit) return Piece::WhiteKnight;
    if (whiteBishops & bit) return Piece::WhiteBishop;
    if (whiteRooks & bit) return Piece::WhiteRook;
    if (whiteQueens & bit) return Piece::WhiteQueen;
    if (whiteKing & bit) return Piece::WhiteKing;

    if (blackPawns & bit) return Piece::BlackPawn;
    if (blackKnights & bit) return Piece::BlackKnight;
    if (blackBishops & bit) return Piece::BlackBishop;
    if (blackRooks & bit) return Piece::BlackRook;
    if (blackQueens & bit) return Piece::BlackQueen;
    if (blackKing & bit) return Piece::BlackKing;

    return Piece::Empty;
}
void Board::print() const {
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            Square square = static_cast<Square>(rank * 8 + file);
            Piece piece = getPiece(square);

            char symbol = '.';

            switch (piece) {
                case Piece::WhitePawn: symbol = 'P'; break;
                case Piece::WhiteKnight: symbol = 'N'; break;
                case Piece::WhiteBishop: symbol = 'B'; break;
                case Piece::WhiteRook: symbol = 'R'; break;
                case Piece::WhiteQueen: symbol = 'Q'; break;
                case Piece::WhiteKing: symbol = 'K'; break;

                case Piece::BlackPawn: symbol = 'p'; break;
                case Piece::BlackKnight: symbol = 'n'; break;
                case Piece::BlackBishop: symbol = 'b'; break;
                case Piece::BlackRook: symbol = 'r'; break;
                case Piece::BlackQueen: symbol = 'q'; break;
                case Piece::BlackKing: symbol = 'k'; break;

                case Piece::Empty: symbol = '.'; break;
            }
            std::cout << symbol << " ";
        }
        std::cout << '\n';
    }
}
uint64_t Board::whitePieces() const {
    return whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
}
uint64_t Board::blackPieces() const {
    return blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
}
uint64_t Board::occupied() const {
    return whitePieces() | blackPieces();
}
uint64_t Board::emptySquares() const {
    return ~occupied();
}
bool Board::loadFEN(const std::string& fen) {
    std::istringstream input(fen);
    std::string piecePlacement;
    std::string activeColor;
    std::string castling;
    std::string enPassant;

    if (!(input >> piecePlacement >> activeColor >> castling >> enPassant >> halfmoveClock >> fullmoveNumber)) {
        return false;
    }

    whitePawns = 0;
    whiteKnights = 0;
    whiteBishops = 0;
    whiteRooks = 0;
    whiteQueens = 0;
    whiteKing = 0;
    blackPawns = 0;
    blackKnights = 0;
    blackBishops = 0;
    blackRooks = 0;
    blackQueens = 0;
    blackKing = 0;

    int rank = 7;
    int file = 0;

    for (char symbol: piecePlacement) {
        if (symbol == '/') {
            --rank;
            file = 0;
            continue;
        }
        if (symbol >= '1' && symbol <= '8') {
            file += symbol - '0';
            continue;
        }
        Square square = static_cast<Square>(rank * 8 + file);
        uint64_t bit = 1ULL << static_cast<int>(square);

        switch (symbol) {
            case 'P': whitePawns |= bit; break;
            case 'N': whiteKnights |= bit; break;
            case 'B': whiteBishops |= bit; break;
            case 'R': whiteRooks |= bit; break;
            case 'Q': whiteQueens |= bit; break;
            case 'K': whiteKing |= bit; break;
            case 'p': blackPawns |= bit; break;
            case 'n': blackKnights |= bit; break;
            case 'b': blackBishops |= bit; break;
            case 'r': blackRooks |= bit; break;
            case 'q': blackQueens |= bit; break;
            case 'k': blackKing |= bit; break;
            default: return false;
        }
        ++file;
    }
    currentSide = (activeColor == "w") ? Color::White : Color::Black;

    whiteKingSideCastle = castling.find('K') != std::string::npos;
    whiteQueenSideCastle = castling.find('Q') != std::string::npos;
    blackKingSideCastle = castling.find('k') != std::string::npos;
    blackQueenSideCastle = castling.find('q') != std::string::npos;

    if (enPassant == "-") {
        enPassantTarget = -1;
    } else {
        int epFile = enPassant[0] - 'a';
        int epRank = enPassant[1] - '1';
        enPassantTarget = epRank * 8 + epFile;
    }
    return true;
}

