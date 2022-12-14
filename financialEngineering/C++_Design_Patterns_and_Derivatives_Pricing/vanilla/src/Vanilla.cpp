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

VanillaOption_1::VanillaOption_1(const PayOff &thePayOff, double expiry) : expiry(expiry)
{
    thePayOffPtr = thePayOff.clone();
}

double VanillaOption_1::getExpiry() const
{
    return expiry;
}

double VanillaOption_1::optionPayOff(double spot) const
{
    return (*thePayOffPtr)(spot);
}

VanillaOption_1::VanillaOption_1(const VanillaOption_1 &original)
{
    expiry = original.expiry;
    thePayOffPtr = original.thePayOffPtr->clone();
}

VanillaOption_1 & ::VanillaOption_1::operator=(const VanillaOption_1 &original)
{
    if (this != &original)
    {
        expiry = original.expiry;
        thePayOffPtr = original.thePayOffPtr->clone();
    }
    return *this;
}

VanillaOption_1::~VanillaOption_1() {}

VanillaOption::VanillaOption(const PayOffBridge &thePayOff, double expiry) : thePayOff(thePayOff), expiry(expiry) {}

double VanillaOption::getExpiry() const
{
    return expiry;
}

double VanillaOption::optionPayOff(double spot) const
{
    return thePayOff(spot);
}
