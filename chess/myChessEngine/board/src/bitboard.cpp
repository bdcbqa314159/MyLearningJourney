#include "board_lib"
#include <iostream>

void printBitBoard(U64 bitboard)
{
    U64 shiftMe = 1ULL;
    int rank = 0, file = 0, sq = 0, sq64 = 0;

    std::cout << std::endl;
    for (rank = RANK_8; rank >= RANK_1; rank--)
    {
        for (file = FILE_A; file <= FILE_H; file++)
        {
            sq = fr_to_sq(file, rank);
            sq64 = Sq120ToSq64[sq];

            if ((shiftMe << sq64) & bitboard)
                std::cout << "X";
            else
                std::cout << "-";
        }
        std::cout << std::endl;
    }
}

void testingBitBoard()
{
    std::cout << "From Bitboard" << std::endl;
    U64 playBitBoard = 0ULL;

    std::cout << "Start: " << std::endl;
    printBitBoard(playBitBoard);

    playBitBoard |= (1ULL << Sq120ToSq64[D2]);
    std::cout << "D2 added: " << std::endl;
    printBitBoard(playBitBoard);
    std::cout << std::endl;

    playBitBoard |= (1ULL << Sq120ToSq64[G2]);
    std::cout << "G2 added: " << std::endl;
    printBitBoard(playBitBoard);
    std::cout << std::endl;
}