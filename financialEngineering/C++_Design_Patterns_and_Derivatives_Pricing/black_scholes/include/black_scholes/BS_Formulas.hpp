#ifndef BS_FORMULAS_H
#define BS_FORMULAS_H

double blackScholesCall(double spot, double strike, double r, double d, double vol, double expiry);

double blackScholesPut(double spot, double strike, double r, double d, double vol, double expiry);

double blackScholesDigitalCall(double spot, double strike, double r, double d, double vol, double expiry);

double blackScholesDigitalPut(double spot, double strike, double r, double d, double vol, double expiry);

double blackScholesCallVega(double spot, double strike, double r, double d, double vol, double expiry);

#endif
