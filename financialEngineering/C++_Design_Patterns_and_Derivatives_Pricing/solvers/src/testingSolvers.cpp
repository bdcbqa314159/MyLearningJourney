#include "solvers_lib"
#include "black_scholes_lib"
#include <iostream>

void testingSolvers()
{
    std::cout << "Saying Hello from Solvers library." << std::endl;
}

void testingBissection()
{
    std::cout << "\nBissection" << std::endl;
    double r = 0.03, d = 0.1, expiry = 1., spot = 40., strike = 89.;
    double price = 0.1;
    BSCall_one theCall(r, d, expiry, spot, strike);
    double vol = bissection(price, 0.1, 2., 0.0001, theCall);

    double price_approx = blackScholesCall(spot, strike, r, d, vol, expiry);

    std::cout << "vol: " << vol << " price approx.: " << price_approx << std::endl;
}

void testingNewtonRaphson()
{
    std::cout << "\nNewton Raphson" << std::endl;
    double r = 0.03, d = 0.1, expiry = 1., spot = 40., strike = 89.;
    double price = 0.1;
    BSCall_two theCall(r, d, expiry, spot, strike);
    double vol = newtonRaphson<BSCall_two, &BSCall_two::price, &BSCall_two::vega>(price, 0.6, 0.001, theCall);

    double price_approx = blackScholesCall(spot, strike, r, d, vol, expiry);

    std::cout << "vol: " << vol << " price approx.: " << price_approx << std::endl;
}