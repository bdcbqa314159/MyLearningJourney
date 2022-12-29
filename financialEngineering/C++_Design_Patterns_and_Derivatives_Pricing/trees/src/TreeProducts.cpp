#include "trees_lib"
#include "pay_off_lib"
#include "black_scholes_lib"
#include <algorithm>
#include <string>
#include <cmath>

TreeProduct::TreeProduct(double finalTime) : finalTime(finalTime)
{
}

double TreeProduct::getFinalTime() const
{
    return finalTime;
}

TreeEuropean::TreeEuropean(double finalTime, const PayOffBridge &thePayOff) : TreeProduct(finalTime), thePayOff(thePayOff)
{
}

std::unique_ptr<TreeProduct> TreeEuropean::clone() const
{
    return std::make_unique<TreeEuropean>(*this);
}

double TreeEuropean::finalPayOff(double spot)
    const
{
    return thePayOff(spot);
}

double TreeEuropean::preFinalValue(double spot, double time, double discoutnedFurureValue) const
{
    return discoutnedFurureValue;
}

TreeAmerican::TreeAmerican(double finalTime, const PayOffBridge &thePayOff) : TreeProduct(finalTime), thePayOff(thePayOff) {}

std::unique_ptr<TreeProduct> TreeAmerican::clone() const
{
    return std::make_unique<TreeAmerican>(*this);
}

double TreeAmerican::finalPayOff(double spot) const
{
    return thePayOff(spot);
}

double TreeAmerican::preFinalValue(double spot, double time, double discountedFutureValue) const
{
    return std::max(thePayOff(spot), discountedFutureValue);
}

SimpleBinomialTree::SimpleBinomialTree(double spot, const Parameters &r, const Parameters &d, double volatility, unsigned long steps, double time) : spot(spot), r(r), d(d), volatility(volatility), steps(steps), time(time), discounts(steps)
{
    treeBuilt = false;
}

void SimpleBinomialTree::buildTree()
{
    treeBuilt = true;
    theTree.resize(steps + 1);
    double initialLogSpot = std::log(spot);
    for (unsigned long i = 0; i <= steps; i++)
    {
        theTree[i].resize(i + 1);
        double thisTime = (i * time) / steps;
        double movedLogSpot = initialLogSpot + r.integral(0., thisTime) - d.integral(0., thisTime);

        movedLogSpot -= 0.5 * volatility * volatility * thisTime;

        double sd = volatility * std::sqrt(time / steps);

        for (long j = -static_cast<long>(i), k = 0; j <= static_cast<long>(i); j = j + 2, k++)
        {
            theTree[i][k].first = std::exp(movedLogSpot + j * sd);
        }
    }

    for (unsigned long k = 0; k < steps; k++)
    {
        discounts[k] = std::exp(-r.integral(k * time / steps, (k + 1) * time / steps));
    }
}

double SimpleBinomialTree::getThePrice(const TreeProduct &theProduct)
{
    if (!treeBuilt)
        buildTree();

    if (theProduct.getFinalTime() != time)
        throw std::string("mismatched product in simpleBinomialTree");

    for (long j = -static_cast<long>(steps), k = 0; j <= static_cast<long>(steps); j = j + 2, k++)
    {
        theTree[steps][k].second = theProduct.finalPayOff(theTree[steps][k].first);
    }

    for (unsigned long i = 1; i <= steps; i++)
    {
        unsigned long index = steps - i;
        double thisTime = index * time / steps;

        for (long j = -static_cast<long>(index), k = 0; j <= static_cast<long>(index); j = j + 2, k++)
        {
            double spot = theTree[index][k].first;
            double futureDiscountedValue = 0.5 * discounts[index] * (theTree[index + 1][k].second + theTree[index + 1][k + 1].second);

            theTree[index][k].second = theProduct.preFinalValue(spot, thisTime, futureDiscountedValue);
        }
    }

    return theTree[0][0].second;
}

void testingTreePricer()
{
    double expiry{1}, strike{0.4}, spot{0.56}, vol{0.005}, r(0.1), d(0.03);
    unsigned long steps(100);

    PayOffCall theCallPayOff(strike);

    ParametersConstant rParam(r);
    ParametersConstant dParam(d);

    TreeEuropean europeanOption(expiry, theCallPayOff);

    TreeAmerican americanOption(expiry, theCallPayOff);

    SimpleBinomialTree theTree(spot, rParam, dParam, vol, steps, expiry);

    double euroPrice = theTree.getThePrice(europeanOption);

    double americanPrice = theTree.getThePrice(americanOption);

    std::cout << "euro price " << euroPrice << std::endl;
    std::cout << "american price " << americanPrice << std::endl;

    double bsPrice = blackScholesCall(spot, strike, r, d, vol, expiry);

    std::cout << "BS formula call euro price: " << bsPrice << std::endl;

    PayOffForward forwardPayOff(strike);
    TreeEuropean forward(expiry, forwardPayOff);

    double forwardPrice = theTree.getThePrice(forward);
    std::cout << "forward price by tree " << forwardPrice << std::endl;
    double actualForwardPrice = exp(-r * expiry) * (spot * exp((r - d) * expiry) - strike);

    std::cout << "forward price " << actualForwardPrice << std::endl;

    steps++;
    SimpleBinomialTree theNewTree(spot, rParam, dParam, vol, steps, expiry);

    double euroNewPrice = theNewTree.getThePrice(europeanOption);
    double americanNewPrice = theNewTree.getThePrice(americanOption);

    std::cout << "new euro price " << euroNewPrice << std::endl;
    std::cout << "new american price " << americanNewPrice << std::endl;

    double forwardNewPrice = theNewTree.getThePrice(forward);
    std::cout << "new forward price by tree " << forwardPrice << std::endl;

    double averageEuro = 0.5 * (euroPrice + euroNewPrice);
    double averageAmerican = 0.5 * (americanPrice + americanNewPrice);
    double averageForward = 0.5 * (forwardPrice + forwardNewPrice);

    std::cout << "prices corrected: " << std::endl;
    std::cout << averageEuro << std::endl;
    std::cout << averageAmerican << std::endl;
    std::cout << averageForward << std::endl;
}