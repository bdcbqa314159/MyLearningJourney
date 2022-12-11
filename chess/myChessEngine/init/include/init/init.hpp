#ifndef INIT_H
#define INIT_H

#include "definitions_lib"
#include "board_lib"

std::array<int, BRD_SQ_NUM> Sq120ToSq64;
std::array<int, 64> Sq64ToSq120;

void initSq120To64();

void AllInit();

#endif