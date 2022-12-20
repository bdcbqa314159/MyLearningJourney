#ifndef EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H

#include <vector>
#include "wrappers_lib"
#include "parameter_lib"
#include "path_dependent_lib"
#include "statistics_lib"
#include "mathematics_lib"
#include "random_lib"
#include "pay_off_lib"

class ExoticEngine
{
public:
    ExoticEngine(const Wrapper<PathDependent> &theProduct, const Parameters &r);
    virtual void getOnePath(Vector &spotValues) = 0;
    void doSimulation(Statistics &theGatherer, unsigned long numberOfPaths);
    virtual ~ExoticEngine() {}
    double doOnePath(const Vector &spotValues) const;

private:
    Wrapper<PathDependent> theProduct;
    Parameters r;
    Vector discounts;
    mutable std::vector<CashFlow> theseCashFlows;
};

class ExoticBSEngine : public ExoticEngine
{
public:
    ExoticBSEngine(const Wrapper<PathDependent> &theProduct, const Parameters &r, const Parameters &d, const Parameters &vol, const Wrapper<RandomBase> &theGenerator, double spot);
    virtual void getOnePath(Vector &spotValues) override;
    virtual ~ExoticBSEngine() {}

private:
    Wrapper<RandomBase> theGenerator;
    Vector drifts, standardDeviations, variates;
    double logSpot;
    unsigned long numberOfTimes;
};

#endif