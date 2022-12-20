#include "exotic_lib"
#include "pay_off_lib"
#include <iostream>

void testingExotic()
{
    std::cout << "Saying Hello from exotic library." << std::endl;
}

void testingBSEngine()
{
    double expiry{1}, spot(0.56), vol{0.005}, r(0.1), strike{0.4}, d{0.01};
    unsigned long numberOfPaths{10}, numberOfDates{12};

    PayOffCall thePayOff(strike);

    Vector times(numberOfDates);
    for (unsigned long i = 0; i < numberOfDates; i++)
    {
        times[i] = (i + 1) * expiry / numberOfDates;
    }

    ParametersConstant volParam(vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    PathDependentAsian theOption(times, expiry, thePayOff);

    StatisticsMean gatherer;
    std::cout << "Convergence Table" << std::endl;

    ConvergenceTable gathererTwo(gatherer);

    RandomParkMiller generator(numberOfDates);
    Antithetic genTwo(generator);

    ExoticBSEngine theEngine(theOption, rParam, dParam, volParam, genTwo, spot);

    theEngine.doSimulation(gathererTwo, numberOfPaths);

    std::vector<std::vector<double>> results = gathererTwo.getResultSoFar();

    std::cout << "For the asian call price the results are:" << std::endl;

    for (unsigned long i = 0; i < results.size(); i++)
    {
        for (unsigned long j = 0; j < results[i].size(); j++)
            std::cout << results[i][j] << " ";
        std::cout << std::endl;
    }
}