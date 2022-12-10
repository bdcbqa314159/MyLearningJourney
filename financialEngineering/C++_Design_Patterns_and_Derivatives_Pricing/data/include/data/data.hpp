#ifndef DATA_H
#define DATA_H

#include <iostream>

struct OptionData
{
    double expiry{1.}, strike{50.};

    OptionData() {}

    OptionData(double expiry, double strike) : expiry(expiry), strike(strike)
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const OptionData &object);
};

struct ModelData
{

    double initialValue{100.}, drift{0.05}, diffusion{0.01};

    ModelData() {}

    ModelData(double spot, double r, double vol) : initialValue(spot), drift(r), diffusion(vol)
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const ModelData &object);
};

struct MonteCarloData
{
    unsigned long numberOfSteps{1000000};

    MonteCarloData() {}

    MonteCarloData(unsigned long numberOfSteps) : numberOfSteps(numberOfSteps) {}

    friend std::ostream &operator<<(std::ostream &os, const MonteCarloData &object);
};

#endif