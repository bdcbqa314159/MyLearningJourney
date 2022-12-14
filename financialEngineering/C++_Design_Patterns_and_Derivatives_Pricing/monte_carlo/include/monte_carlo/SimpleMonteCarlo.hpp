#ifndef SIMPLE_MONTE_CARLO_H
#define SIMPLE_MONTE_CARLO_H

#include "vanilla_lib"

double simpleMonteCarlo(double expiry, double strike, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo2(const PayOff_ &thePayOff, double expiry, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo3(const PayOff_1 &thePayOff, double expiry, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo4(const VanillaOption_ &theOption, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo5(const VanillaOption_1 &theOption, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo6(const VanillaOption &theOption, double spot, double vol, double r, unsigned long numberOfPaths);

void testingSimpleMonteCarlo();
void testingSimpleMonteCarlo2();
void testingSimpleMonteCarlo3();
void testingSimpleMonteCarlo4();
void testingSimpleMonteCarlo5();
void testingSimpleMonteCarlo6();

#endif