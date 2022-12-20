#ifndef PATH_DEPENDENT_H
#define PATH_DEPENDENT_H

#include <memory>
#include <vector>
#include "linear_algebra_lib"

class CashFlow
{
public:
    double amount;
    unsigned long timeIndex;
    CashFlow(double amount = 0, unsigned long timeIndex = 0) : amount(amount), timeIndex(timeIndex) {}
};

class PathDependent
{
public:
    PathDependent(const Vector &lookAtTimes);
    const Vector &getLookAtTimes() const;
    virtual unsigned long maxNumberOfCashFlows() const = 0;
    virtual Vector possibleCashFlowTimes() const = 0;
    virtual unsigned long CashFlows(const Vector &spotValues, std::vector<CashFlow> &generatedFlows) const = 0;
    virtual std::unique_ptr<PathDependent> clone() const = 0;
    virtual ~PathDependent() {}

private:
    Vector lookAtTimes;
};

#endif