#ifndef SOLVERS_IMPLEMENTATION_H
#define SOLVERS_IMPLEMENTATION_H

#include <cmath>

template <class T>
double bissection(double target, double low, double high, double tolerance, T theFunction)
{
    double x = 0.5 * (low + high);
    double y = theFunction(x);

    do
    {
        if (y < target)
            low = x;
        else if (y > target)
            high = x;

        x = 0.5 * (low + high);
        y = theFunction(x);
    } while (fabs(y - target) > tolerance);

    return x;
}

template <class T, double (T::*value)(double) const, double (T::*derivative)(double) const>
double newtonRaphson(double target, double start, double tolerance, const T &theObject)
{
    double y = (theObject.*value)(start);
    double x = start;

    while (fabs(y - target) > tolerance)
    {
        double d = (theObject.*derivative)(x);
        x += (target - y) / d;
        y = (theObject.*value)(x);
    }

    return x;
}

#endif