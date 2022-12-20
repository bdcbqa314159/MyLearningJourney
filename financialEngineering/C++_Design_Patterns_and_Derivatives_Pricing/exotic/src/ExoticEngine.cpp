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

void ExoticBSEngine::getOnePath(Vector &spotValues)
{
    theGenerator->getGaussians(variates);
    double currentLogSpot = logSpot;

    for (unsigned long j = 0; j < numberOfTimes; j++)
    {
        currentLogSpot += drifts[j];
        currentLogSpot += standardDeviations[j] * variates[j];
        spotValues[j] = std::exp(currentLogSpot);
    }

    return;
}

ExoticBSEngine::ExoticBSEngine(const Wrapper<PathDependent> &theProduct, const Parameters &r, const Parameters &d, const Parameters &vol, const Wrapper<RandomBase> &theGenerator, double spot) : ExoticEngine(theProduct, r), theGenerator(theGenerator)
{

    Vector times(theProduct->getLookAtTimes());
    numberOfTimes = times.size();
    (this->theGenerator)->resetDimensionality(numberOfTimes);
    drifts.resize(numberOfTimes);
    standardDeviations.resize(numberOfTimes);

    double variance = vol.integral(0, times[0]);
    drifts[0] = r.integral(0., times[0]) - d.integral(0., times[0]) - 0.5 * variance;

    for (unsigned long j = 1; j < numberOfTimes; j++)
    {
        double thisVariance = vol.integralSquare(times[j - 1], times[j]);
        drifts[j] = r.integral(times[j - 1], times[j]) - d.integral(times[j - 1], times[j]) - 0.5 * thisVariance;

        standardDeviations[j] = std::sqrt(thisVariance);
    }

    logSpot = std::log(spot);
    variates.resize(numberOfTimes);
}
