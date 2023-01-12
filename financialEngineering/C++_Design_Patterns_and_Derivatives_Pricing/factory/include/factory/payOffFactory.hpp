#ifndef PAY_OFF_FACTORY_H
#define PAY_OFF_FACTORY_H

#include <map>
#include <string>
#include <mutex>
#include <iostream>
#include "pay_off_lib"

class PayOffFactory
{

public:
    typedef std::unique_ptr<PayOff> (*createPayOffFunction)(double);
    static std::shared_ptr<PayOffFactory> getInstance();
    void registerPayOff(std::string payoffId, createPayOffFunction creatorFunction);
    std::unique_ptr<PayOff> createPayOff(std::string payOffId, double strike);
    ~PayOffFactory()
    {
        std::cout << "destructor" << std::endl;
    }

    std::map<std::string, createPayOffFunction> theCreatorFunctions;

private:
    static std::mutex myMutex;
    static std::shared_ptr<PayOffFactory> instance;
    PayOffFactory(){};
    PayOffFactory(const PayOffFactory &other){};
    PayOffFactory &operator=(const PayOffFactory &other)
    {
        return *this;
    }
};

inline void PayOffFactory::registerPayOff(std::string payOffId, createPayOffFunction creatorFunction)
{
    std::cout << "registering " << payOffId << std::endl;
    theCreatorFunctions.insert(std::pair<std::string, createPayOffFunction>(payOffId, creatorFunction));
}

inline std::unique_ptr<PayOff> PayOffFactory::createPayOff(std::string payOffId, double strike)
{
    std::map<std::string, createPayOffFunction>::const_iterator it = theCreatorFunctions.find(payOffId);

    if (it == theCreatorFunctions.end())
    {
        std::cout << "PayOffId: " << payOffId << " is an unknown payoff" << std::endl;
        return 0;
    }

    return (it->second)(strike);
}

inline std::shared_ptr<PayOffFactory> PayOffFactory::getInstance()
{

    if (!instance)
    {
        std::lock_guard<std::mutex> lock(myMutex);
        if (!instance)
        {
            instance.reset(new PayOffFactory());
        }
    }

    return instance;
}

template <class T>
class PayOffHelper
{
public:
    PayOffHelper(std::string id);
    static std::unique_ptr<PayOff> create(double strike);
};

template <class T>
inline PayOffHelper<T>::PayOffHelper(std::string id)
{
    std::shared_ptr<PayOffFactory> thePayOffFactory = PayOffFactory::getInstance();
    thePayOffFactory->registerPayOff(id, PayOffHelper<T>::create);
}

template <class T>
inline std::unique_ptr<PayOff> PayOffHelper<T>::create(double strike)
{
    return std::make_unique<T>(strike);
}

#endif