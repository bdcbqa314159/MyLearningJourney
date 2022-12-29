#include "trees_lib"
#include <algorithm>

TreeProduct::TreeProduct(double finalTime) : finalTime(finalTime)
{
}

double TreeProduct::getFinalTime() const
{
    return finalTime;
}

TreeEuropean::TreeEuropean(double finalTime, const PayOffBridge &thePayOff) : TreeProduct(finalTime), thePayOff(thePayOff)
{
}

std::unique_ptr<TreeProduct> TreeEuropean::clone() const
{
    return std::make_unique<TreeEuropean>(*this);
}

double TreeEuropean::finalPayOff(double spot)
    const
{
    return thePayOff(spot);
}

double TreeEuropean::preFinalValue(double spot, double time, double discoutnedFurureValue) const
{
    return discoutnedFurureValue;
}

TreeAmerican::TreeAmerican(double finalTime, const PayOffBridge &thePayOff) : TreeProduct(finalTime), thePayOff(thePayOff) {}

std::unique_ptr<TreeProduct> TreeAmerican::clone() const
{
    return std::make_unique<TreeAmerican>(*this);
}

double TreeAmerican::finalPayOff(double spot) const
{
    return thePayOff(spot);
}

double TreeAmerican::preFinalValue(double spot, double time, double discountedFutureValue) const
{
    return std::max(thePayOff(spot), discountedFutureValue);
}