#include <iostream>
#include "black_scholes_lib"
#include "mathematics_lib"

using namespace std;

int main()
{

    cout << "My first pricing library." << endl;

    cout << "Calling a call and a put under BS" << endl;

    double spotPrice = 300, strike = 250, T = 1, vol = 0.15, rfr = 0.03, dividend = 0;

    BlackScholes_Call call(rfr, vol, strike, T, spotPrice, dividend);
    BlackScholes_Put put(rfr, vol, strike, T, spotPrice, dividend);

    cout << "Call: " << call() << endl;
    cout << "Put: " << put() << endl;

    return 0;
}