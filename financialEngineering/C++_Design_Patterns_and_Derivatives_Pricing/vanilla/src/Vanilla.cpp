#include "vanilla_lib"
#include <algorithm>

VanillaOption::VanillaOption(const PayOffBridge &thePayOff, double expiry) : thePayOff(thePayOff), expiry(expiry) {}

double VanillaOption::getExpiry() const
{
    return expiry;
}

double VanillaOption::optionPayOff(double spot) const
{
    return thePayOff(spot);
}
