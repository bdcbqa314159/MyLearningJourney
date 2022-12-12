#ifndef BOARD_H
#define BOARD_H

#include "definitions_lib"

typedef struct
{
    int move, castlePermission, enPassant, fiftyMove;
    U64 positionKey;
} S_UNDO;

typedef struct
{
    std::array<int, BRD_SQ_NUM> pieces;
    std::array<U64, 3> pawns;

    std::array<int, 2> KingSquare;
    int side, enPassant, fiftyMoveCounter, ply, hisPly;

    U64 positionKey;

    std::array<int, 13> pieceNum;
    std::array<int, 3> bigPieces;
    std::array<int, 3> majorPieces;
    std::array<int, 3> minorPieces;

    std::array<S_UNDO, MAX_GAME_MOVES> historyOfTheGame;

} S_BOARD;

enum
{
    WhiteKingCastling = 1,
    WhiteQueenCastling = 1,
    BlackKingCastling = 1,
    BlackQueenCastling = 1
};

void testingBoard();
#endif