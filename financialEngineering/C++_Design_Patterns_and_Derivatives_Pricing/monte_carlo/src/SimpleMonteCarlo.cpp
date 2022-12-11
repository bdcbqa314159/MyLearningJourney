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

double simpleMonteCarlo2(const PayOff_ &thePayOff, double expiry, double spot, double vol, double r, unsigned long numberOfPaths)
{

    double variance = vol * vol * expiry;
    double rootVariance = std::sqrt(variance);
    double itoCorrection = -0.5 * variance;

    double movedSpot = spot * exp(r * expiry + itoCorrection);
    double thisSpot{};
    double runningSum{};

    for (unsigned long i = 0; i < numberOfPaths; i++)
    {
        double thisGaussian = getOneGaussianBoxMuller();
        thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        double thisPayOff = thePayOff(thisSpot);
        runningSum += thisPayOff;
    }

    double mean = runningSum / numberOfPaths;
    mean *= exp(-r * expiry);
    return mean;
}

double interfaceForSimpleMonteCarlo2(const OptionData &option, const PayOff_ &thePayOff, const ModelData &model, const MonteCarloData &mc)
{

    return simpleMonteCarlo2(thePayOff, option.expiry, model.initialValue, model.diffusion, model.drift, mc.numberOfSteps);
}

void testingSimpleMonteCarlo2()
{
    OptionData option;
    ModelData model;
    MonteCarloData simpleMC;
    PayOff_ thePayOff_call(option.strike, PayOff_::call);

    double result = interfaceForSimpleMonteCarlo2(option, thePayOff_call, model, simpleMC);

    std::cout << "The value for this input (call) :" << std::endl;
    std::cout << option << std::endl;
    std::cout << model << std::endl;
    std::cout << simpleMC << std::endl;
    std::cout << " is PV = " << result << std::endl;

    PayOff_ thePayOff_put(option.strike, PayOff_::put);

    result = interfaceForSimpleMonteCarlo2(option, thePayOff_put, model, simpleMC);

    std::cout << "The value for this input (put) :" << std::endl;
    std::cout << option << std::endl;
    std::cout << model << std::endl;
    std::cout << simpleMC << std::endl;
    std::cout << " is PV = " << result << std::endl;
}
