#ifndef VANILLA_H
#define VANILLA_H

#include "pay_off_lib"

class VanillaOption_
{
public:
    VanillaOption_(PayOff_1 &thePayOff, double expiry);
    double getExpiry() const;
    double OptionPayOff(double spot) const;

private:
    double expiry;
    PayOff_1 &thePayOff;
};

#endif
