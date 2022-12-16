#ifndef SIMPLE_MONTE_CARLO_H
#define SIMPLE_MONTE_CARLO_H

#include "vanilla_lib"
#include "parameter_lib"
#include "statistics_lib"
#include "wrappers_lib"

double simpleMonteCarlo(double expiry, double strike, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo6(const VanillaOption &theOption, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo7(const VanillaOption &theOption, double spot, const Parameters &vol, const Parameters &r, unsigned long numberOfPaths);

void simpleMonteCarlo8(const VanillaOption &theOption, double spot, const Parameters &vol, const Parameters &r, unsigned long numberOfPaths, Statistics &gatherer);

void testingSimpleMonteCarlo();
void testingSimpleMonteCarlo6();
void testingSimpleMonteCarlo7();
void testingSimpleMonteCarlo8();

#endif