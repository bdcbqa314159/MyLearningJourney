#ifndef BLACK_SCHOLES_FORMULAS_H
#define BLACK_SCHOLES_FORMULAS_H
#include "mathematics_lib"
#include <cmath>

class RealFunction
{
public:
    virtual ~RealFunction() {}
    virtual double operator()(double x) = 0;
};

class RealFunction2D
{
public:
    virtual ~RealFunction2D() {}
    virtual double operator()(double x, double y) = 0;
};

class Constant : virtual public RealFunction
{

public:
    Constant() {}

    Constant(double intensity) : intensity(intensity) {}

    virtual double operator()(double x) override
    {
        return intensity;
    }

    ~Constant() {}

private:
    double intensity{};
};

class Constant2D : virtual public RealFunction2D
{

public:
    Constant2D() {}

    Constant2D(double intensity) : intensity(intensity) {}

    virtual double operator()(double x, double y) override
    {
        return intensity;
    }

    ~Constant2D() {}

private:
    double intensity{};
};

class BlackScholes
{
public:
    BlackScholes() {}

    BlackScholes(double spot, double rfr, double dividend, double vol) : spot(spot), rfr(rfr), dividend(dividend), vol(vol) {}

    double theDrift() const;

    double theDiffusion() const;

    double initialValue() const;

    double theRfr() const;

    double theDividend() const;

private:
    double spot{}, rfr{}, dividend{}, vol{};
};

class EuroPutCallValues
{
public:
    EuroPutCallValues() {}
    EuroPutCallValues(double strike, double maturity) : strike(strike), maturity(maturity) {}

    double theStrike() const
    {
        return strike;
    }

    double theMaturity() const
    {
        return maturity;
    }

private:
    double strike{};
    double maturity{};
};

class BlackScholes_Formulas
{
public:
    BlackScholes_Formulas() {}

    BlackScholes_Formulas(const BlackScholes &model, const EuroPutCallValues &theValues) : theModel(model), theOptionValues(theValues)
    {
        standardDeviation = theModel.theDiffusion() * std::sqrt(theOptionValues.theMaturity());
        moneyness = std::log(theModel.initialValue() / theOptionValues.theStrike());
        d1 = (moneyness + theModel.theDrift() * theOptionValues.theMaturity() + 0.5 * standardDeviation * standardDeviation) / standardDeviation;
        d2 = d1 - standardDeviation;
    }

    virtual double operator()() = 0;
    virtual ~BlackScholes_Formulas() {}

protected:
    BlackScholes theModel;
    EuroPutCallValues theOptionValues;
    double moneyness{}, standardDeviation{}, d1{}, d2{};
};

class BlackScholes_Call : public BlackScholes_Formulas
{
public:
    BlackScholes_Call(){};
    BlackScholes_Call(const BlackScholes &model, const EuroPutCallValues &theValues) : BlackScholes_Formulas(model, theValues) {}

    double operator()() override
    {
        return theModel.initialValue() * std::exp(-theModel.theDividend()) * cumulativeNormal(d1) - theOptionValues.theStrike() * std::exp(-theModel.theRfr() * theOptionValues.theMaturity()) * cumulativeNormal(d2);
    }
};

class BlackScholes_Put : public BlackScholes_Formulas
{
public:
    BlackScholes_Put(){};
    BlackScholes_Put(const BlackScholes &model, const EuroPutCallValues &theValues) : BlackScholes_Formulas(model, theValues) {}

    double operator()() override
    {
        return -theModel.initialValue() * std::exp(-theModel.theDividend()) * (1. - cumulativeNormal(d1)) + theOptionValues.theStrike() * std::exp(-theModel.theRfr() * theOptionValues.theMaturity()) * (1. - cumulativeNormal(d2));
    }
};

#endif