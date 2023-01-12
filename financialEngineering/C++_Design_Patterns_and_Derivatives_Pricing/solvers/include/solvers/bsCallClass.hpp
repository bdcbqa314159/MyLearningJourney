#ifndef BS_CALL_CLASS_H
#define BS_CALL_CLASS_H

class BSCall_one
{
public:
    BSCall_one(double r, double d, double T, double spot, double strike);
    double operator()(double vol) const;

private:
    double r, d, T, spot, strike;
};

class BSCall_two
{
public:
    BSCall_two(double r, double d, double T, double spot, double strike);
    double price(double vol) const;
    double vega(double vol) const;

private:
    double r, d, T, spot, strike;
};

#endif