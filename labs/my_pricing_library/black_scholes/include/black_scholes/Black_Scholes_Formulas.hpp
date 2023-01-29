#ifndef BLACK_SCHOLES_FORMULAS_H
#define BLACK_SCHOLES_FORMULAS_H
#include "mathematics_lib"
#include <cmath>

class Black_Scholes_Formulas
{
public:
    Black_Scholes_Formulas() {}
    Black_Scholes_Formulas(double rfr, double vol, double strike, double timeToMaturity, double assetValue, double dividend = 0)
        : r(rfr), sigma(vol), K(strike), tau(timeToMaturity), S(assetValue), q(dividend)
    {
        double standardDeviation = sigma * std::sqrt(tau);
        double moneyness = std::log(S / K);

        d_1 = (moneyness + (r - q + 0.5 * standardDeviation * standardDeviation)) / standardDeviation;
        d_2 = d_1 - standardDeviation;
        calculation_1 = S * std::exp(-q * tau);
        calculation_2 = K * std::exp(-r * tau);
    }

    virtual double operator()() = 0;
    virtual ~Black_Scholes_Formulas() {}

protected:
    double r{}, sigma{}, K{}, tau{}, S{}, q{};
    double d_1{}, d_2{}, calculation_1{}, calculation_2{};
};

class BlackScholes_Call : public Black_Scholes_Formulas
{
public:
    BlackScholes_Call() {}
    BlackScholes_Call(double rfr, double vol, double strike, double timeToMaturity, double assetValue, double dividend) : Black_Scholes_Formulas(rfr, vol, strike, timeToMaturity, assetValue, dividend) {}
    virtual double operator()() override
    {
        return calculation_1 * cumulativeNormal(d_1) - calculation_2 * cumulativeNormal(d_2);
    }
};

class BlackScholes_Put : public Black_Scholes_Formulas
{
public:
    BlackScholes_Put() {}
    BlackScholes_Put(double rfr, double vol, double strike, double timeToMaturity, double assetValue, double dividend) : Black_Scholes_Formulas(rfr, vol, strike, timeToMaturity, assetValue, dividend) {}
    virtual double operator()() override
    {
        return -calculation_1 * (1. - cumulativeNormal(d_1)) + calculation_2 * (1. - cumulativeNormal(d_2));
    }
};

#endif