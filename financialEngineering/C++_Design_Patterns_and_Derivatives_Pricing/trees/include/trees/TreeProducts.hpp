#ifndef TREE_PRODUCTS_H
#define TREE_PRODUCTS_H
#include <memory>
#include <vector>
#include "pay_off_lib"
#include "parameter_lib"
#include "linear_algebra_lib"

class TreeProduct
{
public:
    TreeProduct(double finalTimne);
    virtual double finalPayOff(double spot) const = 0;
    virtual double preFinalValue(double spot, double time, double discounyFutureValue) const = 0;
    virtual ~TreeProduct() {}
    virtual std::unique_ptr<TreeProduct> clone() const = 0;
    double getFinalTime() const;

private:
    double finalTime;
};

class TreeEuropean : public TreeProduct
{
public:
    TreeEuropean(double finalTime, const PayOffBridge &thePayOff);
    virtual std::unique_ptr<TreeProduct> clone() const;
    virtual double finalPayOff(double spot) const;
    virtual double preFinalValue(double spot, double time, double discountedFutureeValue) const;
    virtual ~TreeEuropean() {}

private:
    PayOffBridge thePayOff;
};

class TreeAmerican : public TreeProduct
{
public:
    TreeAmerican(double finalTime, const PayOffBridge &thePayOff);
    virtual std::unique_ptr<TreeProduct> clone() const;
    virtual double finalPayOff(double spot) const;
    virtual double preFinalValue(double spot, double time, double discountedFutureValue) const;

    virtual ~TreeAmerican() {}

private:
    PayOffBridge thePayOff;
};

class SimpleBinomialTree
{
public:
    SimpleBinomialTree(double spot, const Parameters &r, const Parameters &d, double volatility, unsigned long steps, double time);
    double getThePrice(const TreeProduct &theProduct);

protected:
    void buildTree();

private:
    double spot, volatility, time;
    Parameters r, d;
    unsigned long steps;
    bool treeBuilt;
    std::vector<std::vector<std::pair<double, double>>> theTree;
    Vector discounts;
};

void testingTreePricer();

#endif
