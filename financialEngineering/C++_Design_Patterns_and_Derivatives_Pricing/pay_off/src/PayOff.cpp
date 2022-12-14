#include "pay_off_lib"
#include <algorithm>

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