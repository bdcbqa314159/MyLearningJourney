#ifndef PAY_OFF_H
#define PAY_OFF_H

class PayOff_
{
public:
    enum OptionType
    {
        call,
        put
    };
    PayOff_(double strike, OptionType theOptionsType);
    double operator()(double spot) const;

private:
    double strike;
    OptionType theOptionsType;
};

class PayOff_1
{
public:
    PayOff_1(){};
    virtual double operator()(double spot) const = 0;
    virtual ~PayOff_1() {}

private:
};

class PayOffCall_1 : public PayOff_1
{
public:
    PayOffCall_1(double strike);
    virtual double operator()(double spot) const;
    virtual ~PayOffCall_1() {}

private:
    double strike;
};

class PayOffPut_1 : public PayOff_1
{
public:
    PayOffPut_1(double strike);
    virtual double operator()(double spot) const;
    virtual ~PayOffPut_1() {}

private:
    double strike;
};

class PayOffDoubleDigital_1
{
public:
    PayOffDoubleDigital_1(double lowerLevel, double upperLevel);
    virtual double operator()(double spot) const;
    virtual ~PayOffDoubleDigital_1() {}

private:
    double lowerLevel, upperLevel;
};

#endif
