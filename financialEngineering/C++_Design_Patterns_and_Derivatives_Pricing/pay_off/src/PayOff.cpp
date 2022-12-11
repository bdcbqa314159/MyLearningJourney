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
