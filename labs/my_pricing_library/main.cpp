#include <iostream>
#include "black_scholes_lib"
#include "mathematics_lib"

using namespace std;

int main()
{

    cout << "My first pricing library." << endl;

    cout << "Calling a call and a put under BS" << endl;

    BlackScholes model(300, 0.03, 0, 0.15);
    EuroPutCallValues values(250, 1);

    BlackScholes_Call call(model, values);
    BlackScholes_Put put(model, values);
    cout << "The call: " << call() << endl;
    cout << "The put: " << put() << endl;

    return 0;
}