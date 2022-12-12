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

    return 0;
}