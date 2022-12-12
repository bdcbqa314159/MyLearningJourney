#include "init_lib"
#include <iostream>
#include <iomanip>

std::array<int, BRD_SQ_NUM> Sq120ToSq64;
std::array<int, 64> Sq64ToSq120;

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
