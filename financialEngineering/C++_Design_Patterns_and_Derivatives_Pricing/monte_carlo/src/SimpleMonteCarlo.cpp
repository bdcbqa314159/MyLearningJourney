#include "monte_carlo_lib"
#include "random_lib"
#include "data_lib"
#include <cmath>
#include <algorithm>

double simpleMonteCarlo(double expiry, double strike, double spot, double vol, double r, unsigned long numberOfPaths)
{
    double variance = vol * vol * expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5 * variance;

    double movedSpot = spot * exp(r * expiry + itoCorrection);
    double thisSpot{}, runnigSum{};

    for (unsigned long i = 0; i < numberOfPaths; i++)
    {
        double thisGaussian = getOneGaussianBoxMuller();
        thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        double thisPayoff = thisSpot - strike;

        thisPayoff = std::max(thisPayoff, 0.);

        runnigSum += thisPayoff;
    }

    double mean = runnigSum / numberOfPaths;
    mean *= exp(-r * expiry);
    return mean;
}

double interfaceForSimpleMonteCarlo(const OptionData &option, const ModelData &model, const MonteCarloData &mc)
{

    return simpleMonteCarlo(option.expiry, option.strike, model.initialValue, model.diffusion, model.drift, mc.numberOfSteps);
}

void testingSimpleMonteCarlo()
{
    OptionData option;
    ModelData model;
    MonteCarloData simpleMC;

    double result = interfaceForSimpleMonteCarlo(option, model, simpleMC);

    std::cout << "The value for this input :" << std::endl;
    std::cout << option << std::endl;
    std::cout << model << std::endl;
    std::cout << simpleMC << std::endl;
    std::cout << " is PV = " << result << std::endl;
}
