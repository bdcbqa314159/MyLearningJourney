#include "solvers_lib"
#include "black_scholes_lib"
#include <iostream>

BSCall_one::BSCall_one(double r, double d, double T, double spot, double strike) : r(r), d(d), T(T), spot(spot), strike(strike)
{
}

double BSCall_one::operator()(double vol) const
{
    return blackScholesCall(spot, strike, r, d, vol, T);
}

BSCall_two::BSCall_two(double r, double d, double T, double spot, double strike) : r(r), d(d), T(T), spot(spot), strike(strike)
{
}

double BSCall_two::price(double vol) const
{
    return blackScholesCall(spot, strike, r, d, vol, T);
}

double BSCall_two::vega(double vol) const
{
    return blackScholesCallVega(spot, strike, r, d, vol, T);
}