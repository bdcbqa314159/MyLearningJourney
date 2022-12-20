#ifndef EXOTIC_ENGINE_H
#define EXOTIC_ENGINE_H

#include <vector>
#include "wrappers_lib"
#include "parameter_lib"
#include "path_dependent_lib"
#include "statistics_lib"

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

#endif