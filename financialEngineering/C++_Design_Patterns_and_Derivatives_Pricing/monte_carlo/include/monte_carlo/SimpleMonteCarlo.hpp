#ifndef SIMPLE_MONTE_CARLO_H
#define SIMPLE_MONTE_CARLO_H

#include "vanilla_lib"
#include "parameter_lib"

double simpleMonteCarlo(double expiry, double strike, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo6(const VanillaOption &theOption, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo7(const VanillaOption &theOption, double spot, const Parameters &vol, const Parameters &r, unsigned long numberOfPaths);

void testingSimpleMonteCarlo();
void testingSimpleMonteCarlo6();
void testingSimpleMonteCarlo7();

#endif