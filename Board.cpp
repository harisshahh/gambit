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
    int newHalfmoveClock;
    int newFullmoveNumber;
    std::string extraField;

    if (!(input >> piecePlacement >> activeColor >> castling >> enPassant >> newHalfmoveClock >> newFullmoveNumber)) {
        return false;
    }
    if (input >> extraField) {
        return false;
    }
    if (activeColor != "w" && activeColor != "b") {
        return false;
    }
    if (newHalfmoveClock < 0 || newFullmoveNumber < 1) {
        return false;
    }
    if (castling.empty()) {
        return false;
    }
    if (castling != "-") {
        std::string seenCastling;
        for (char right: castling) {
            if (std::string("KQkq").find(right) == std::string::npos) {
                return false;
            }
            if (seenCastling.find(right) != std::string::npos) {
                return false;
            }
            seenCastling += right;
        }
    }

    uint64_t newWhitePawns = 0;
    uint64_t newWhiteKnights = 0;
    uint64_t newWhiteBishops = 0;
    uint64_t newWhiteRooks = 0;
    uint64_t newWhiteQueens = 0;
    uint64_t newWhiteKing = 0;
    uint64_t newBlackPawns = 0;
    uint64_t newBlackKnights = 0;
    uint64_t newBlackBishops = 0;
    uint64_t newBlackRooks = 0;
    uint64_t newBlackQueens = 0;
    uint64_t newBlackKing = 0;
    int whiteKingCount = 0;
    int blackKingCount = 0;


    int rank = 7;
    int file = 0;
    int ranksSeen = 1;

    for (char symbol: piecePlacement) {
        if (symbol == '/') {
            if (file != 8 || rank == 0) {
                return false;
            }
            --rank;
            file = 0;
            ++ranksSeen;
            continue;
        }
        if (symbol >= '1' && symbol <= '8') {
            int emptyCount = symbol - '0';
            if (file + emptyCount > 8) {
                return false;
            }
            file += emptyCount;
            continue;
        }
        if (file >= 8 || rank < 0) {
            return false;
        }

        uint64_t bit = 1ULL << (rank * 8 + file);

        switch (symbol) {
            case 'P': newWhitePawns |= bit; break;
            case 'N': newWhiteKnights |= bit; break;
            case 'B': newWhiteBishops |= bit; break;
            case 'R': newWhiteRooks |= bit; break;
            case 'Q': newWhiteQueens |= bit; break;
            case 'K': newWhiteKing |= bit; ++whiteKingCount; break;
            case 'p': newBlackPawns |= bit; break;
            case 'n': newBlackKnights |= bit; break;
            case 'b': newBlackBishops |= bit; break;
            case 'r': newBlackRooks |= bit; break;
            case 'q': newBlackQueens |= bit; break;
            case 'k': newBlackKing |= bit; ++blackKingCount; break;
            default: return false;
        }
        ++file;
    }
    if (ranksSeen != 8 || rank != 0 || file != 8) {
        return false;
    }
    if (whiteKingCount != 1 || blackKingCount != 1) {
        return false;
    }
    int newEnPassantTarget = -1;
    if (enPassant != "-") {
        if (enPassant.size() != 2) {
            return false;
        }
        if (enPassant[0] < 'a' || enPassant[0] > 'h') {
            return false;
        }
        if (enPassant[1] != '3' && enPassant[1] != '6') {
            return false;
        }
        if ((activeColor == "w" && enPassant[1] != '6') || (activeColor == "b" && enPassant[1] != '3')) {
            return false;
        }
        int epFile = enPassant[0] - 'a';
        int epRank = enPassant[1] - '1';
        newEnPassantTarget = epRank * 8 + epFile;
        if (((newWhitePawns | newBlackPawns | newWhiteKnights | newBlackKnights | newWhiteBishops | newBlackBishops | newWhiteRooks | newBlackRooks | newWhiteQueens | newBlackQueens | newWhiteKing | newBlackKing) & (1ULL << newEnPassantTarget)) != 0) {
            return false;
        }
    }

    whitePawns = newWhitePawns;
    whiteKnights = newWhiteKnights;
    whiteBishops = newWhiteBishops;
    whiteRooks = newWhiteRooks;
    whiteQueens = newWhiteQueens;
    whiteKing = newWhiteKing;
    blackPawns = newBlackPawns;
    blackKnights = newBlackKnights;
    blackBishops = newBlackBishops;
    blackRooks = newBlackRooks;
    blackQueens = newBlackQueens;
    blackKing = newBlackKing;

    currentSide = (activeColor == "w") ? Color::White : Color::Black;

    whiteKingSideCastle = castling.find('K') != std::string::npos;
    whiteQueenSideCastle = castling.find('Q') != std::string::npos;
    blackKingSideCastle = castling.find('k') != std::string::npos;
    blackQueenSideCastle = castling.find('q') != std::string::npos;
    enPassantTarget = newEnPassantTarget;
    halfmoveClock = newHalfmoveClock;
    fullmoveNumber = newFullmoveNumber;

    return true;
}

Color Board::sideToMove() const {
    return currentSide;
}

bool Board::canCastleKingSide(Color color) const {
    if (color == Color::White) {
        return whiteKingSideCastle;
    }
    return blackKingSideCastle;
}

bool Board::canCastleQueenSide(Color color) const {
    if (color == Color::White) {
        return whiteQueenSideCastle;
    }
    return blackQueenSideCastle;
}

int Board::getEnPassantTarget() const {
    return enPassantTarget;
}

int Board::getHalfmoveClock() const {
    return halfmoveClock;
}

int Board::getFullmoveNumber() const {
    return fullmoveNumber;
}
