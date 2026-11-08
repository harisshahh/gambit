# Gambit

Gambit is a chess engine written in C++20. The project is being built from scratch, with a focus on bitboards, efficient move generation, and chess search algorithms.

## Features

- Bitboard-based board representation using 64-bit integers
- Piece and square representations
- FEN position parsing and validation
- Castling rights and en passant state tracking
- Move representation with support for special moves
- Bitwise operations for adding and removing pieces

## Tech Stack

- C++20
- CMake
- GoogleTest

## Building

```bash
git clone <repository-url>
cd gambit
cmake -S . -B build
cmake --build build
```

