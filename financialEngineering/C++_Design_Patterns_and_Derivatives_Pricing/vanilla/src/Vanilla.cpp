#include "vanilla_lib"
#include <algorithm>

VanillaOption_::VanillaOption_(PayOff_1 &thePayOff, double expiry) : thePayOff(thePayOff), expiry(expiry)
{
}

double VanillaOption_::getExpiry() const
{
    return expiry;
}

double VanillaOption_::OptionPayOff(double spot) const
{
    return thePayOff(spot);
}
