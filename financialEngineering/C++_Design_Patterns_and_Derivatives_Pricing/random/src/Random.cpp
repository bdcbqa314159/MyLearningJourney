#include "random_lib"
#include <cmath>

void RandomBase::getGaussians(Vector &variates)
{
    getUniforms(variates);
    for (unsigned long i = 0; i < dimensionality; i++)
    {
        double x = variates[i];
        variates[i] = inverseCumulativeNormal(x);
    }
}

void RandomBase::resetDimensionality(unsigned long newDimensionality)
{
    dimensionality = newDimensionality;
}

RandomBase::RandomBase(unsigned long dimensionality) : dimensionality(dimensionality)
{
}

const long a = 16807;
const long m = 2147483647;
const long q = 127773;
const long r = 2836;

ParkMiller::ParkMiller(long seed) : seed(seed)
{
    if (seed == 0)
        seed = 1;
}

void ParkMiller::setSeed(long seed)
{
    this->seed = seed;
    if (seed == 0)
        seed = 1;
}

unsigned long ParkMiller::max()
{
    return m - 1;
}

unsigned long ParkMiller::min()
{
    return 1;
}

long ParkMiller::getOneRandomInteger()
{
    long k = seed / q;

    seed = a * (seed - k * q) - r * k;

    if (seed < 0)
        seed += m;

    return seed;
}

RandomParkMiller::RandomParkMiller(unsigned long dimensionality, unsigned long seed) : RandomBase(dimensionality), innerGenerator(seed), initialSeed(seed)
{
    reciprocal = 1. / (1. + innerGenerator.max());
}

std::unique_ptr<RandomBase> RandomParkMiller::clone() const
{
    return std::make_unique<RandomParkMiller>(*this);
}

void RandomParkMiller::getUniforms(Vector &variates)
{
    for (unsigned long j = 0; j < getDimensionality(); j++)
    {
        variates[j] = innerGenerator.getOneRandomInteger() * reciprocal;
    }
}

void RandomParkMiller::skip(unsigned long numberOfPaths)
{
    Vector temp(getDimensionality());
    for (unsigned long j = 0; j < numberOfPaths; j++)
        getUniforms(temp);
}

void RandomParkMiller::setSeed(unsigned long seed)
{
    initialSeed = seed;
    innerGenerator.setSeed(seed);
}

void RandomParkMiller::reset()
{
    innerGenerator.setSeed(initialSeed);
}

void RandomParkMiller::resetDimensionality(unsigned long newDimensionality)
{
    RandomBase::resetDimensionality(newDimensionality);
    innerGenerator.setSeed(initialSeed);
}

Antithetic::Antithetic(const Wrapper<RandomBase> &innerGenerator) : RandomBase(*innerGenerator), innerGenerator(innerGenerator)
{
    (this->innerGenerator)->reset();
    oddEven = true;
    nextVariate.resize(getDimensionality());
}

std::unique_ptr<RandomBase> Antithetic::clone() const
{
    return std::make_unique<Antithetic>(*this);
}

void Antithetic::getUniforms(Vector &variates)
{
    if (oddEven)
    {
        innerGenerator->getUniforms(variates);
        for (unsigned long i = 0; i < getDimensionality(); i++)
            nextVariate[i] = 1. - variates[i];
        oddEven = false;
    }

    else
    {
        variates = nextVariate;
        oddEven = true;
    }
}

void Antithetic::setSeed(unsigned long seed)
{
    innerGenerator->setSeed(seed);
    oddEven = true;
}

void Antithetic::skip(unsigned long numberOfPaths)
{
    if (numberOfPaths == 0)
        return;
    if (oddEven)
    {
        oddEven = false;
        numberOfPaths--;
    }

    innerGenerator->skip(numberOfPaths / 2);
    if (numberOfPaths % 2)
    {
        Vector temp(getDimensionality());
        getUniforms(temp);
    }
}

void Antithetic::resetDimensionality(unsigned long newDimensionality)
{
    RandomBase::resetDimensionality(newDimensionality);
    nextVariate.resize(newDimensionality);
    innerGenerator->resetDimensionality(newDimensionality);
}

void Antithetic::reset()
{
    innerGenerator->reset();
    oddEven = true;
}