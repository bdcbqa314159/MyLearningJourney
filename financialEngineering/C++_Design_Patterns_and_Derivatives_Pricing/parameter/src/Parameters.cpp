#include "parameter_lib"
#include <algorithm>

Parameters::Parameters(const ParametersInner &innerObject)
{
    innerObjectPtr = innerObject.clone();
}

Parameters::Parameters(const Parameters &original)
{
    innerObjectPtr = original.innerObjectPtr->clone();
}

Parameters &Parameters::operator=(const Parameters &original)
{
    if (this != &original)
    {
        innerObjectPtr = original.innerObjectPtr->clone();
    }
    return *this;
}

Parameters::~Parameters() {}

double Parameters::integral(double time1, double time2) const
{
    return innerObjectPtr->integral(time1, time2);
}

double Parameters::integralSquare(double time1, double time2) const
{
    return innerObjectPtr->integralSquare(time1, time2);
}

double Parameters::mean(double time1, double time2) const
{
    double total = integral(time1, time2);
    return total / (time2 - time1);
}

double Parameters::rootMeanSquare(double time1, double time2) const
{
    double total = integralSquare(time1, time2);
    return total / (time2 - time1);
}

ParametersConstant::ParametersConstant(double constant) : constant(constant), constantSquare(constant * constant) {}

std::unique_ptr<ParametersInner> ParametersConstant::clone() const
{
    return std::make_unique<ParametersConstant>(*this);
}

double ParametersConstant::integral(double time1, double time2) const
{
    return constant * (time2 - time1);
}

double ParametersConstant::integralSquare(double time1, double time2) const
{
    return constantSquare * (time2 - time1);
}