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

double simpleMonteCarlo3(const PayOff_1 &thePayOff, double expiry, double spot, double vol, double r, unsigned long numberOfPaths)
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

double interfaceForSimpleMonteCarlo3(const OptionData &option, const PayOff_1 &thePayOff, const ModelData &model, const MonteCarloData &mc)
{

    return simpleMonteCarlo3(thePayOff, option.expiry, model.initialValue, model.diffusion, model.drift, mc.numberOfSteps);
}

void testingSimpleMonteCarlo3()
{
    OptionData option;
    ModelData model;
    MonteCarloData simpleMC;
    PayOffCall_1 callPayOff(option.strike);

    double result = interfaceForSimpleMonteCarlo3(option, callPayOff, model, simpleMC);

    std::cout << "The value for this input (call) :" << std::endl;
    std::cout << option << std::endl;
    std::cout << model << std::endl;
    std::cout << simpleMC << std::endl;
    std::cout << " is PV = " << result << std::endl;

    PayOffPut_1 putPayOff(option.strike);

    result = interfaceForSimpleMonteCarlo3(option, putPayOff, model, simpleMC);

    std::cout << "The value for this input (put) :" << std::endl;
    std::cout << option << std::endl;
    std::cout << model << std::endl;
    std::cout << simpleMC << std::endl;
    std::cout << " is PV = " << result << std::endl;
}

double simpleMonteCarlo4(const VanillaOption_ &theOption, double spot, double vol, double r, unsigned long numberOfPaths)
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
        double thisPayOff = theOption.OptionPayOff(thisSpot);
        runningSum += thisPayOff;
    }

    double mean = runningSum / numberOfPaths;
    mean *= std::exp(-r * expiry);
    return mean;
}

void testingSimpleMonteCarlo4()
{
    double expiry{1}, low{0.4}, up{1}, spot(0.56), vol{0.005}, r(0.1);
    unsigned long numberOfPaths{10};

    PayOffDoubleDigital_1 thePayOff(low, up);
    VanillaOption_ theOption(thePayOff, expiry);

    double result = simpleMonteCarlo4(theOption, spot, vol, r, numberOfPaths);
    std::cout << "the result is :" << result << std::endl;
}
