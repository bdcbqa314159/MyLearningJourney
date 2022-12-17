#include "testing_lib"
#include "init_lib"
#include "definitions_lib"
#include "board_lib"
#include <iostream>

using namespace std;

int main()
{
    cout << "Building a chess engine for fun" << endl;
    testingDefinitions();
    testingBoard();

    AllInit();
    printingBoards();

    testingBitBoard();

    int index = 0;
    U64 playBitBoard = 0ULL;

    // for (index = 0; index < 64; index++)
    // {
    //     std::cout << "Index: " << index << ": " << std::endl;
    //     printBitBoard(setMask[index]);
    //     std::cout << std::endl;
    // }

    std::cout << std::endl;
    std::cout << "******" << std::endl;

    setBit(&playBitBoard, 61);
    std::cout << std::endl;
    std::cout << "******" << std::endl;
    printBitBoard(playBitBoard);

    // for (index = 0; index < 64; index++)
    // {
    //     std::cout << "Index: " << index << ": " << std::endl;
    //     printBitBoard(clearMask[index]);
    //     std::cout << std::endl;
    // }

    clearBit(&playBitBoard, 61);
    std::cout << "******" << std::endl;
    printBitBoard(playBitBoard);

    return 0;
}