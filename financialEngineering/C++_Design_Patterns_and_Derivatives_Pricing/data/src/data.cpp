#include "data_lib"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const OptionData &object)
{
    os << "The option: " << std::endl;
    os << "strike: " << object.strike << std::endl;
    os << "maturity: " << object.expiry << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const ModelData &object)
{
    os << "The model (Black Scholes): " << std::endl;
    os << "initial value = " << object.initialValue << std::endl;
    os << "drift = " << object.drift << std::endl;
    os << "diffusion = " << object.diffusion << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const MonteCarloData &object)
{
    os << "The Monte Carlo Model: " << std::endl;
    os << "Number of steps = " << object.numberOfSteps << std::endl;
    return os;
}