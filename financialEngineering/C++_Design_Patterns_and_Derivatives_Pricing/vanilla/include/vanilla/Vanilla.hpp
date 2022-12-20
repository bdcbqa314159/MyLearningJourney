#ifndef VANILLA_H
#define VANILLA_H

#include "pay_off_lib"

class VanillaOption
{
public:
    VanillaOption(const PayOffBridge &thePayOff, double expiry);
    double optionPayOff(double spot) const;
    double getExpiry() const;

private:
    double expiry;
    PayOffBridge thePayOff;
};

#endif
