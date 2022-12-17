#ifndef INIT_H
#define INIT_H

#include "definitions_lib"
#include "board_lib"
#include <cstdlib>

void initSq120To64();
void initBitMasks();
U64 rand_64();
void initHashKeys();

void AllInit();

void printingBoards();

#endif