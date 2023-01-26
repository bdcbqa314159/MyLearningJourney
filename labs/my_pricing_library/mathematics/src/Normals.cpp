#include "mathematics_lib"
#include <cmath>
#include <array>

const double oneOverRootTwoPi = 0.398942280401433;

double normalDensity(double x)
{
    return oneOverRootTwoPi * std::exp(-x * x / 2);
}

double inverseCumulativeNormal(double u)
{
    static std::array<double, 4> a = {2.50662823884,
                                      -18.61500062529,
                                      41.39119773534,
                                      -25.44106049637};

    static std::array<double, 4> b = {-8.47351093090,
                                      23.08336743743,
                                      -21.06224101826,
                                      3.13082909833};

    static std::array<double, 9> c = {0.3374754822726147,
                                      0.9761690190917186,
                                      0.1607979714918209,
                                      0.0276438810333863,
                                      0.0038405729373609,
                                      0.0003951896511919,
                                      0.0000321767881768,
                                      0.0000002888167364,
                                      0.0000003960315187};

    double x = u - 0.5;
    double r{};

    if (std::fabs(x) < 0.42)
    {
        double y = x * x;
        r = x * (((a[3] * y + a[2]) * y + a[1]) * y + a[0]) / ((((b[3] * y + b[2]) * y + b[1]) * y + b[0]) * y + 1.0);
    }

    else
    {
        r = u;
        if (x > 0.)
            r = 1. - u;

        r = std::log(-std::log(r));
        r = c[0] + r * (c[1] + r * (c[2] + r * (c[3] + r * (c[4] + r * (c[5] +
                                                                        r * (c[6] + r * (c[7] + r * c[8])))))));

        if (x < 0.)
            r = -r;
    }

    return r;
}

double cumulativeNormal(double x)
{
    static std::array<double, 5> a = {0.319381530,
                                      -0.356563782,
                                      1.781477937,
                                      -1.821255978,
                                      1.330274429};

    double result{};

    if (x < -7.)
        result = normalDensity(x) / sqrt(1. + x * x);
    else
    {
        if (x > 7.)
            result = 1. - cumulativeNormal(-x);
        else
        {
            double temp = 1. / (1. + 0.2316419 * fabs(x));
            result = 1 - normalDensity(x) * (temp * (a[0] + temp * (a[1] + temp * (a[2] + temp * (a[3] + temp * a[4])))));
            if (x <= 0.)
                result = 1. - result;
        }
    }
    return result;
}
