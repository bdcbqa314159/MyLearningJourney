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

double simpleMonteCarlo6(const VanillaOption &theOption, double spot, double vol, double r, unsigned long numberOfPaths)
{
    double expiry = theOption.getExpiry();
    double variance = vol * vol * expiry;

    double rootVariance = std::sqrt(variance);

    double itoCorrection = -0.5 * variance;

    double movedSpot = spot * std::exp(r * expiry + itoCorrection);
    double thisSpot{}, runningSum{};

    for (unsigned long i = 0; i < numberOfPaths; i++)
    {
        double thisGaussian = getOneGaussianBoxMuller();
        thisSpot = movedSpot * std::exp(rootVariance * thisGaussian);
        double thisPayOff = theOption.optionPayOff(thisSpot);
        runningSum += thisPayOff;
    }

    double mean = runningSum / numberOfPaths;
    mean *= std::exp(-r * expiry);
    return mean;
}

void testingSimpleMonteCarlo6()
{
    double expiry{1}, low{0.4}, up{1}, spot(0.56), vol{0.005}, r(0.1);
    unsigned long numberOfPaths{10};

    PayOffDoubleDigital thePayOff(low, up);
    VanillaOption theOption(thePayOff, expiry);

    double result = simpleMonteCarlo6(theOption, spot, vol, r, numberOfPaths);
    std::cout << "the result is :" << result << std::endl;
}

double simpleMonteCarlo7(const VanillaOption &theOption, double spot, const Parameters &vol, const Parameters &r, unsigned long numberOfPaths)
{
    double expiry = theOption.getExpiry();
    double variance = vol.integralSquare(0, expiry);
    double rootVariance = std::sqrt(variance);

    double itoCorrection = -0.5 * variance;
    double movedSpot = spot * std::exp(r.integral(0, expiry) + itoCorrection);

    double thisSpot{}, runningSum{};

    for (unsigned long i = 0; i < numberOfPaths; i++)
    {
        double thisGaussian = getOneGaussianBoxMuller();
        thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        double thisPayOff = theOption.optionPayOff(thisSpot);

        runningSum += thisPayOff;
    }

    double mean = runningSum / numberOfPaths;
    mean *= std::exp(-r.integral(0, expiry));
    return mean;
}

void testingSimpleMonteCarlo7()
{
    double expiry{1}, low{0.4}, up{1}, spot(0.56), vol{0.005}, r(0.1);
    unsigned long numberOfPaths{10};

    PayOffDoubleDigital thePayOff(low, up);
    VanillaOption theOption(thePayOff, expiry);

    ParametersConstant volParam(vol);
    ParametersConstant rParam(r);

    double result = simpleMonteCarlo7(theOption, spot, volParam, rParam, numberOfPaths);
    std::cout << "the result is :" << result << std::endl;
}