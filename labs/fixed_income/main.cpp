#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

class ZeroCouponBond
{
};

class InterestRate
{
};

class Price
{
};

void price_quotes()
{
    double price_of_the_bond = 102.1234;
    double coupon = 5;
    double investment = 1000000;

    double face_value = investment / (price_of_the_bond * 0.01);
    double next_coupon_received = face_value * coupon * 0.01;

    double value_at_maturity = face_value * (1 + coupon * 0.01);

    cout << "If we invest " << investment << " we are able to buy the following face value (FV) : " << face_value << endl;
    cout << "Which means we are going to receive a coupon of " << next_coupon_received << endl;
    cout << "At maturity we are going to have " << value_at_maturity << endl;
}

int main()
{
    cout << "Fixed income" << endl;
    price_quotes();

    return 0;
}