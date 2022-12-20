#include "path_dependent_lib"
#include <algorithm>

PathDependent::PathDependent(const Vector &lookAtTimes) : lookAtTimes(lookAtTimes) {}

const Vector &PathDependent::getLookAtTimes() const
{
    return lookAtTimes;
}

PathDependentAsian::PathDependentAsian(const Vector &lookAtTimes, double deliveryTime, const PayOffBridge &thePayOff) : PathDependent(lookAtTimes), deliveryTime(deliveryTime), thePayOff(thePayOff), numberOfTimes(lookAtTimes.size()) {}

unsigned long PathDependentAsian::maxNumberOfCashFlows() const
{
    return 1;
}

Vector PathDependentAsian::possibleCashFlowTimes() const
{
    Vector result(1);
    result[0] = deliveryTime;
    return result;
}

unsigned long PathDependentAsian::CashFlows(const Vector &spotValues, std::vector<CashFlow> &generatedCashFlows) const
{
    double sum = spotValues.sum();

    double mean = sum / numberOfTimes;
    generatedCashFlows[0].timeIndex = 0;
    generatedCashFlows[0].amount = thePayOff(mean);

    return 1;
}

std::unique_ptr<PathDependent> PathDependentAsian::clone() const
{
    return std::make_unique<PathDependentAsian>(*this);
}
