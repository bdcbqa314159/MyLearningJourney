#ifndef RANDOM_H
#define RANDOM_H
#include <memory>
#include "wrappers_lib"
#include "linear_algebra_lib"
#include "mathematics_lib"

class RandomBase
{
public:
    RandomBase() {}
    RandomBase(unsigned long dimensionality);
    inline unsigned long getDimensionality() const;
    virtual ~RandomBase() {}

    virtual std::unique_ptr<RandomBase> clone() const = 0;
    virtual void getUniforms(Vector &variates) = 0;
    virtual void skip(unsigned long numberOfPaths) = 0;
    virtual void setSeed(unsigned long seed) = 0;
    virtual void reset() = 0;

    virtual void getGaussians(Vector &variates);
    virtual void resetDimensionality(unsigned long newDimensionality);

private:
    unsigned long dimensionality{};
};

unsigned long RandomBase::getDimensionality() const
{
    return dimensionality;
}

class ParkMiller
{
public:
    ParkMiller() {}
    ParkMiller(long seed);
    long getOneRandomInteger();
    void setSeed(long seed);
    static unsigned long max();
    static unsigned long min();

private:
    long seed{1};
};

class RandomParkMiller : public RandomBase
{
public:
    RandomParkMiller(unsigned long dimensionality, unsigned long seed = 1);
    virtual std::unique_ptr<RandomBase> clone() const override;
    ~RandomParkMiller() {}

    virtual void getUniforms(Vector &variates) override;
    virtual void skip(unsigned long numberOfPaths) override;
    virtual void setSeed(unsigned long seed) override;
    virtual void reset() override;
    virtual void resetDimensionality(unsigned long newDimensionality) override;

private:
    ParkMiller innerGenerator;
    unsigned long initialSeed;
    double reciprocal;
};

class Antithetic : public RandomBase
{
public:
    Antithetic(const Wrapper<RandomBase> &innerGenerator);
    virtual std::unique_ptr<RandomBase> clone() const override;
    virtual void getUniforms(Vector &variates) override;
    virtual void skip(unsigned long numberOfPaths) override;
    virtual void setSeed(unsigned long seed) override;
    virtual void resetDimensionality(unsigned long newDimensionality) override;
    virtual void reset() override;

private:
    Wrapper<RandomBase> innerGenerator;
    bool oddEven;
    Vector nextVariate;
};

#endif