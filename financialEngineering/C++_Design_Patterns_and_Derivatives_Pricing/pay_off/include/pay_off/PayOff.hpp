#ifndef PAY_OFF_H
#define PAY_OFF_H
#include <memory>

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

class PayOffDoubleDigital_1 : public PayOff_1
{
public:
    PayOffDoubleDigital_1(double lowerLevel, double upperLevel);
    virtual double operator()(double spot) const;
    virtual ~PayOffDoubleDigital_1() {}

private:
    double lowerLevel, upperLevel;
};

class PayOff
{
public:
    PayOff() {}
    virtual double operator()(double spot) const = 0;
    virtual ~PayOff() {}
    virtual std::unique_ptr<PayOff> clone() const = 0;

private:
};

class PayOffCall : public PayOff
{
public:
    PayOffCall(double strike);
    virtual double operator()(double spot) const override;
    virtual ~PayOffCall() override {}
    virtual std::unique_ptr<PayOff> clone() const override;

private:
    double strike;
};

class PayOffPut : public PayOff
{
public:
    PayOffPut(double strike);
    virtual double operator()(double spot) const override;
    virtual ~PayOffPut() override {}
    virtual std::unique_ptr<PayOff> clone() const override;

private:
    double strike;
};

class PayOffDoubleDigital : public PayOff
{
public:
    PayOffDoubleDigital(double lowerStrike, double upperStrike);
    virtual double operator()(double spot) const override;
    virtual ~PayOffDoubleDigital() override {}
    virtual std::unique_ptr<PayOff> clone() const override;

private:
    double lowerStrike, upperStrike;
};

class PayOffBridge
{
public:
    PayOffBridge(const PayOffBridge &original);
    PayOffBridge(const PayOff &innerPayOff);
    double operator()(double spot) const;
    ~PayOffBridge();
    PayOffBridge &operator=(const PayOffBridge &original);

private:
    std::unique_ptr<PayOff> thePayOffPtr;
};

#endif
