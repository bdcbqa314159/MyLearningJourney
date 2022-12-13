#include "pay_off_lib"
#include <algorithm>

PayOff_::PayOff_(double strike, OptionType theOptionsType) : strike(strike), theOptionsType(theOptionsType)
{
}

double PayOff_::operator()(double spot) const
{
    switch (theOptionsType)
    {
    case call:
        return std::max(spot - strike, 0.);
    case put:
        return std::max(strike - spot, 0.);
    default:
        throw("unkwnon option type found.");
    }
}

PayOffCall_1::PayOffCall_1(double strike) : strike(strike) {}

double PayOffCall_1::operator()(double spot) const
{
    return std::max(spot - strike, 0.);
}

PayOffPut_1::PayOffPut_1(double strike) : strike(strike) {}

double PayOffPut_1::operator()(double spot) const
{
    return std::max(strike - spot, 0.);
}

PayOffDoubleDigital_1::PayOffDoubleDigital_1(double lowerLevel, double upperLevel) : lowerLevel(lowerLevel), upperLevel(upperLevel) {}

double PayOffDoubleDigital_1::operator()(double spot) const
{
    return 1. * (lowerLevel < spot && spot < upperLevel);
}