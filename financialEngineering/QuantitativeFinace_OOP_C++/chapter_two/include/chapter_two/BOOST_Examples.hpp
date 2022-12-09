#ifndef BOOST_EXAMPLES_H
#define BOOST_EXAMPLES_H
#include <map>
#include <boost/function.hpp>
#include <boost/bind/bind.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>
#include <memory>

// #include <boost/bind.hpp> -> it does not work anymore

void calculate_and_print(boost::function<double(int x, int y)> g);

double divide(int a, int b);

class multiply{
public:
    double operator()(int a, int b){ return a* b; }
};


void workingWithFunctors();


void calculate_and_print_bind1(boost::function<double(int x)> g);

class multiply_1{
private:
    double coefficient;
public:
    multiply_1(double x):coefficient(x){};
    double operator()(int a){ return coefficient*a;}
};


void workingWithBinding_1();

double func(int x, double y, double z);

void workingWithBinding_2();

std::shared_ptr<double> create_a_double(double d);

void sharedPointerExample();


#endif