#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <memory>

class ParametersInner
{
public:
    ParametersInner() {}
    virtual std::unique_ptr<ParametersInner> clone() const = 0;
    virtual double integral(double time1, double time2) const = 0;
    virtual double integralSquare(double time1, double time2) const = 0;

    virtual ~ParametersInner() {}

private:
};

class Parameters
{
public:
    Parameters(const ParametersInner &innerObject);
    Parameters(const Parameters &original);
    Parameters &operator=(const Parameters &original);
    virtual ~Parameters();

    double integral(double time1, double time2) const;
    double integralSquare(double time1, double time2) const;
    double mean(double time1, double time2) const;
    double rootMeanSquare(double time1, double time2) const;

private:
    std::unique_ptr<ParametersInner> innerObjectPtr;
};

class ParametersConstant : public ParametersInner
{
public:
    ParametersConstant(double constant);
    virtual std::unique_ptr<ParametersInner> clone() const;
    virtual double integral(double time1, double time2) const;
    virtual double integralSquare(double time1, double time2) const;

private:
    double constant, constantSquare;
};

#endif
