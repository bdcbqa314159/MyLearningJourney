#ifndef BLITZ_EXAMPLES_H
#define BLITZ_EXAMPLES_H
#include <iostream>
#include <blitz/array.h>
#include <blitz/array/newet-macros.h>

void firstTest();

void slicing();

double add_one(double x);
double half(int x);
double hypothenuse(double a, double b);
int fit_into(double x, double y);

BZ_DECLARE_FUNCTION(add_one)
BZ_DECLARE_FUNCTION_RET(half,double)
BZ_DECLARE_FUNCTION2(hypothenuse)
BZ_DECLARE_FUNCTION2_RET(fit_into,int)

void scalarFunctions();

void reduce();


#endif