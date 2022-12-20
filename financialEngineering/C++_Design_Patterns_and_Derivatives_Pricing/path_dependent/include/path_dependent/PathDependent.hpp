#ifndef PATH_DEPENDENT_H
#define PATH_DEPENDENT_H

#include <memory>
#include <vector>
#include "linear_algebra_lib"
#include "pay_off_lib"

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

class PathDependentAsian : public PathDependent
{
public:
    PathDependentAsian(const Vector &lookAtTimes, double deliveryTime, const PayOffBridge &thePayOff);
    virtual unsigned long maxNumberOfCashFlows() const override;
    virtual Vector possibleCashFlowTimes() const override;

    virtual unsigned long CashFlows(const Vector &spotValues, std::vector<CashFlow> &generatdCashFlows) const override;

    virtual std::unique_ptr<PathDependent> clone() const override;
    virtual ~PathDependentAsian() {}

private:
    double deliveryTime;
    PayOffBridge thePayOff;
    unsigned long numberOfTimes;
};

#endif