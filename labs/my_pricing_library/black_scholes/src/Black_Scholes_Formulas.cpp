#include "black_scholes_lib"

double BlackScholes::theDrift() const
{
    return rfr - dividend;
}

double BlackScholes::theDiffusion() const
{
    return vol;
}

double BlackScholes::initialValue() const
{
    return spot;
}

double BlackScholes::theRfr() const
{
    return rfr;
}

double BlackScholes::theDividend() const
{
    return dividend;
}