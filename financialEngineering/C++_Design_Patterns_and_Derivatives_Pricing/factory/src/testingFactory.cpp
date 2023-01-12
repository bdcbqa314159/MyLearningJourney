#include "factory_lib"
#include <iostream>

void testingFactory()
{
    std::cout << "Saying Hello from Factory library." << std::endl;
}

void testingPayOffFactory()
{
    double strike = 130;
    std::string name = "call";

    std::unique_ptr<PayOff> payOffPtr = PayOffFactory::getInstance()->createPayOff(name, strike);

    if (payOffPtr)
    {
        double spot = 40;
        std::cout << "With strike = " << strike << " and spot = " << spot << " the pay off of the " << name << " is = " << payOffPtr->operator()(spot) << std::endl;
    }

    else
    {
        std::cout << "we have a problem." << std::endl;
    }
}