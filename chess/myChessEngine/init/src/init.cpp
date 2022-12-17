#include "init_lib"
#include <iostream>
#include <iomanip>

std::array<int, BRD_SQ_NUM> Sq120ToSq64;
std::array<int, 64> Sq64ToSq120;
std::array<U64, 64> setMask;
std::array<U64, 64> clearMask;

std::array<std::array<U64, 13>, 120> pieceKeys;
U64 sideKeys;
std::array<U64, 16> castleKeys;

U64 rand_64()
{
    U64 a1 = static_cast<U64>(rand());
    U64 a2 = static_cast<U64>(rand());
    U64 a3 = static_cast<U64>(rand());
    U64 a4 = static_cast<U64>(rand());
    U64 a5 = static_cast<U64>(rand());

    return a1 + (a2 << 15) + (a3 << 30) + (a4 << 45) + ((a5 & 0xf) << 60);
}

void initHashKeys()
{
    int index = 0;
    int index_2 = 0;
    for (index = 0; index < 13; index++)
    {
        for (index_2 = 0; index_2 < 120; index_2++)
            pieceKeys[index][index_2] = rand_64();
    }
    sideKeys = rand_64();
    for (index = 0; index < 16; index++)
        castleKeys[index] = rand_64();
}

void initBitMasks()
{
    int index = 0;

    for (index = 0; index < 64; index++)
    {
        setMask[index] = 0ULL;
        clearMask[index] = 0ULL;
    }

    for (index = 0; index < 64; index++)
    {
        setMask[index] |= (1ULL << index);
        clearMask[index] = ~setMask[index];
    }
}

void initSq120To64()
{

    int index{};
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64{};

    for (index = 0; index < BRD_SQ_NUM; index++)
    {
        Sq120ToSq64[index] = 65;
    }

    for (index = 0; index < 64; index++)
    {
        Sq64ToSq120[index] = 120;
    }

    for (rank = RANK_1; rank <= RANK_8; rank++)
    {
        for (file = FILE_A; file <= FILE_H; file++)
        {
            sq = fr_to_sq(file, rank);
            Sq64ToSq120[sq64] = sq;
            Sq120ToSq64[sq] = sq64;
            sq64++;
        }
    }
    return;
}

void AllInit()
{
    std::cout << "From AllInit()" << std::endl;
    initSq120To64();
    initBitMasks();
    initHashKeys();
}

void printingBoards()
{
    for (int index = 0; index < BRD_SQ_NUM; index++)
    {
        if (index % 10 == 0)
            std::cout << std::endl;
        std::cout << std::right << std::setw(2) << Sq120ToSq64[index] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    for (int index = 0; index < 64; index++)
    {
        if (index % 8 == 0)
            std::cout << std::endl;
        std::cout << std::right << std::setw(2) << Sq64ToSq120[index] << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;
    return;
}
