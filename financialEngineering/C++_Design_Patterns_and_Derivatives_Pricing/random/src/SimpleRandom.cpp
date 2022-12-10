#include "random_lib"
#include <cmath>

double getOneGaussianBySummation()
{

    double result{};
    for (int j = 0; j < 12; j++)
    {
        result += rand() / static_cast<double>(RAND_MAX);
    }

    result -= 6.;
    return result;
}

double getOneGaussianBoxMuller()
{
    double result{}, x{}, y{}, sizeSquared{};

    do
    {
        x = 2. * rand() / static_cast<double>(RAND_MAX) - 1;
        y = 2. * rand() / static_cast<double>(RAND_MAX) - 1;

        sizeSquared = x * x + y * y;

    } while (sizeSquared >= 1.);

    result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);
    return result;
}