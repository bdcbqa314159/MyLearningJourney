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

#endif
