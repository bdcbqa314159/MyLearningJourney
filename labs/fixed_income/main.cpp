#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

class Bond
{
public:
    Bond(double coupon, double price) : coupon(coupon), price(price)
    {
    }

    double give_face_value(double investment)
    {
        face_value = 100 * investment / price;
        return face_value;
    }

    double give_coupon_value()
    {
        return face_value * coupon * 0.01;
    }

    double give_total_atm()
    {
        return face_value * (1 + coupon * 0.01);
    }

private:
    double coupon{}, price{}, face_value{};
};

class TBill
{

public:
    TBill(double price, int n) : price(price), n(n)
    {
    }

    double give_quote()
    {
        return 3.6 * (100 - price) / n;
    }

    double give_face_value(double investment)
    {
        face_value = 100 * investment / price;
        return face_value;
    }

private:
    double price{}, k{}, face_value{};
    int n{};
};

void working_first_example()
{
    Bond myBond(5., 102.1234);
    double investment = 1000000;
    cout << "FV = " << myBond.give_face_value(investment) << endl;
    cout << "Coupon value = " << myBond.give_coupon_value() << endl;
    cout << "At maturity we will receive = " << myBond.give_total_atm() << endl;
}

void working_second_example()
{
    TBill myTBill(98.123456, 182);

    cout << "quote for this TBill = " << myTBill.give_quote() << endl;
    double investment = 10000;
    cout << "FV = " << myTBill.give_face_value(investment) << endl;
}

void working_3rd_example()
{
    cout << "With a semi annual coupon of 4%" << endl;
    cout << "Between 15 Jan 2012 10 April 2012: " << endl;
    cout << "act/act -> 0.02*86/182 = " << 0.02 * 86 / 182 << endl;
    cout << "30/360 -> 0.02*85/180 = " << 0.02 * 85 / 180 << endl;
}

int main()
{
    cout << "Fixed income" << endl;
    working_first_example();
    working_second_example();
    working_3rd_example();

    return 0;
}