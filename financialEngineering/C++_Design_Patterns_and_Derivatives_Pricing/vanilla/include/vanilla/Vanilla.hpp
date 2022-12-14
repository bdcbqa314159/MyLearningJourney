#ifndef VANILLA_H
#define VANILLA_H

#include "pay_off_lib"

// class VanillaOption_
// {
// public:
//     VanillaOption_(PayOff_1 &thePayOff, double expiry);
//     double getExpiry() const;
//     double OptionPayOff(double spot) const;

// private:
//     double expiry;
//     PayOff_1 &thePayOff;
// };

// class VanillaOption_1
// {
// public:
//     VanillaOption_1(const PayOff &thePayOff, double expiry);
//     VanillaOption_1(const VanillaOption_1 &original);
//     VanillaOption_1 &operator=(const VanillaOption_1 &original);
//     ~VanillaOption_1();

//     double getExpiry() const;
//     double optionPayOff(double spot) const;

// private:
//     double expiry;
//     std::unique_ptr<PayOff> thePayOffPtr;
// };

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
