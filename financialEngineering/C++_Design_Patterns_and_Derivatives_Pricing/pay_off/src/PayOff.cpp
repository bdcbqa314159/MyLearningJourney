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

PayOffCall::PayOffCall(double strike) : strike(strike)
{
}

double PayOffCall::operator()(double spot) const
{
    return std::max(spot - strike, 0.);
}

std::unique_ptr<PayOff> PayOffCall::clone() const
{
    return std::make_unique<PayOffCall>(*this);
}

PayOffPut::PayOffPut(double strike) : strike(strike)
{
}

double PayOffPut::operator()(double spot) const
{
    return std::max(strike - spot, 0.);
}

std::unique_ptr<PayOff> PayOffPut::clone() const
{
    return std::make_unique<PayOffPut>(*this);
}

PayOffDoubleDigital::PayOffDoubleDigital(double lowerStrike, double upperStrike) : lowerStrike(lowerStrike), upperStrike(upperStrike)
{
}

double PayOffDoubleDigital::operator()(double spot) const
{
    return 1. * (lowerStrike < spot && spot < upperStrike);
}

std::unique_ptr<PayOff> PayOffDoubleDigital::clone() const
{
    return std::make_unique<PayOffDoubleDigital>(*this);
}

PayOffBridge::PayOffBridge(const PayOffBridge &original)
{
    thePayOffPtr = original.thePayOffPtr->clone();
}

PayOffBridge::PayOffBridge(const PayOff &innerPayOff)
{
    thePayOffPtr = innerPayOff.clone();
}

PayOffBridge::~PayOffBridge()
{
}

PayOffBridge &PayOffBridge::operator=(const PayOffBridge &original)
{
    if (this != &original)
    {
        thePayOffPtr = original.thePayOffPtr->clone();
    }

    return *this;
}

double PayOffBridge::operator()(double spot) const
{
    return thePayOffPtr->operator()(spot);
}