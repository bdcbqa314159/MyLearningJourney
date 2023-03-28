// tanh.hxx

#ifndef TANH_HXX
#define TANH_HXX

//uble (*func) (double x);
//#include "Interval.hxx"

double integrate (double (*f) (double), const INTERVAL& tr, int N);
double myfuncx (double x);
double difficult (double x);
double normal_func(double x);

#endif