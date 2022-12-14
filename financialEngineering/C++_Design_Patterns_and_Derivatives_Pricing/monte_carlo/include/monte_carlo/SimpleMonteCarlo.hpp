#ifndef SIMPLE_MONTE_CARLO_H
#define SIMPLE_MONTE_CARLO_H

#include "vanilla_lib"

double simpleMonteCarlo(double expiry, double strike, double spot, double vol, double r, unsigned long numberOfPaths);

void testingSimpleMonteCarlo();
void testingSimpleMonteCarlo6();

#endif