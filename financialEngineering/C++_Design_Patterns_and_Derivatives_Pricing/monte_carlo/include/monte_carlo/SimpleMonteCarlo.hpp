#ifndef SIMPLE_MONTE_CARLO_H
#define SIMPLE_MONTE_CARLO_H
#include "pay_off_lib"

double simpleMonteCarlo(double expiry, double strike, double spot, double vol, double r, unsigned long numberOfPaths);

double simpleMonteCarlo2(const PayOff_ &thePayOff, double expiry, double spot, double vol, double r, unsigned long numberOfPaths);

void testingSimpleMonteCarlo();
void testingSimpleMonteCarlo2();

#endif