#include "chapter_two_lib"

using namespace std;

void calculate_and_print(boost::function<double(int x, int y)> g){
    cout<<"Result: "<<g(2,3)<<endl;
}

double divide(int a, int b){
    return static_cast<double>(a)/b;
}

void workingWithFunctors(){
    boost::function<double(int x,int y) >f;
    f = divide;
    calculate_and_print(f);
    f = multiply();
    calculate_and_print(f);
}

void calculate_and_print_bind1(boost::function<double(int x)> g){
    cout<<"Result: "<<g(3)<<endl;
}

void workingWithBinding_1(){
    boost::function<double (int x)>f;
    multiply_1 mult(3.5);
    f = boost::bind(boost::mem_fn(&multiply_1::operator()),&mult,boost::placeholders::_1);
    // f = boost::bind(boost::mem_fn(&multiply::operator()),&mult,_1); -> deprecated
    calculate_and_print_bind1(f);
}

double func(int x, double y, double z){
    return (x-z)*y;
}

void workingWithBinding_2(){
    boost::function<double (int x, int y)>f;

    f = boost::bind(func, boost::placeholders::_1, 3.14, boost::placeholders::_2);
    calculate_and_print(f);

    f = boost::bind(func, boost::placeholders::_2, 3.14, boost::placeholders::_1);
    calculate_and_print(f);
}

std::shared_ptr<double> create_a_double(double d){
    std::shared_ptr<double> result(new double (d));
    return result;
}

void sharedPointerExample(){
    std:shared_ptr<double> creation = create_a_double(5.3);
    std::cout<<*creation<<std::endl;
}