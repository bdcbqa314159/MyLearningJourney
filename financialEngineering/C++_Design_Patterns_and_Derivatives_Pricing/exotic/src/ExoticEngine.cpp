#include "exotic_lib"
#include <cmath>

ExoticEngine::ExoticEngine(const Wrapper<PathDependent> &theProduct, const Parameters &r) : theProduct(theProduct), r(r), discounts(theProduct->possibleCashFlowTimes())
{
    for (unsigned long i = 0; i < discounts.size(); i++)
    {
        discounts[i] = std::exp(-r.integral(0, discounts[i]));
    }

    theseCashFlows.resize(theProduct->maxNumberOfCashFlows());
}

void ExoticEngine::doSimulation(Statistics &theGatherer, unsigned long numberOfPaths)
{
    Vector spotValues(theProduct->getLookAtTimes().size());
    theseCashFlows.resize(theProduct->maxNumberOfCashFlows());
    double thisValue{};

    for (unsigned long i = 0; i < numberOfPaths; i++)
    {
        getOnePath(spotValues);
        thisValue = doOnePath(spotValues);
        theGatherer.dumpOneResult(thisValue);
    }
    return;
}

double ExoticEngine::doOnePath(const Vector &spotValues) const
{
    unsigned long numberOfFlows = theProduct->CashFlows(spotValues, theseCashFlows);
    double value{};
    for (unsigned long i = 0; i < numberOfFlows; i++)
    {
        value += theseCashFlows[i].amount * discounts[theseCashFlows[i].timeIndex];
    }

    return value;
}