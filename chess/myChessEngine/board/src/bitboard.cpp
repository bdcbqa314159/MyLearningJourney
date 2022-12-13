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

// const std::array<int, 64> BitTable = {
//     63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
//     51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
//     26, 60, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
//     58, 20, 37, 17, 36, 8};

int PopBit(U64 *bb)
{
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = static_cast<unsigned>((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}

int CountBits(U64 b)
{
    int r{};
    for (r = 0; b; r++, b &= b - 1)
        ;
    return r;
}

void testingBitBoard()
{
    std::cout << "From Bitboard" << std::endl;
    U64 playBitBoard = 0ULL;
    // SQ64 in the videos means Sq120toSq64 here.

    playBitBoard |= (1ULL << Sq120ToSq64[D2]);
    playBitBoard |= (1ULL << Sq120ToSq64[D3]);
    playBitBoard |= (1ULL << Sq120ToSq64[D4]);

    // printBitBoard(playBitBoard);
    // int count = CountBits(playBitBoard);

    // std::cout << "Count: " << count << std::endl;

    // int index = PopBit(&playBitBoard);
    // std::cout << "Index: " << index << std::endl;
    // printBitBoard(playBitBoard);
    // count = CountBits(playBitBoard);

    // std::cout << "Count: " << count << std::endl;
    int sq64 = 0;
    while (playBitBoard)
    {
        sq64 = PopBit(&playBitBoard);
        std::cout << "popped: " << sq64 << std::endl;
        printBitBoard(playBitBoard);
    }
}
