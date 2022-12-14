#ifndef PAY_OFF_H
#define PAY_OFF_H
#include <memory>

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
