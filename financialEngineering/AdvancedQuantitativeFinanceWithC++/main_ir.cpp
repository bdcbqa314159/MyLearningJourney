#include <iostream>
#include "my_ir_lib"

using namespace std;

int main()
{

	std::cout << "Hello from Advanced Quantitative Finance with C++" << std::endl;
    
    double notional = 1e6;
    double K = 0.04;
    double alpha = 0.25;
    double sigma = 0.15;
    double dT = 0.25;

    int N = 3;
    int M = 1000;

    IR ir1(notional, K, alpha, sigma, dT, N, M);

    auto results = ir1.get_simulation_data();

    auto sz = results.datapoints.size();
    for (int nsim = 0; nsim<sz; nsim++)
        cout<<"simIRS["<<nsim<<"] = "<<results.datapoints[nsim]<<endl;

    cout<<"IRS PV = "<<results.value<<endl;
	
	return 0;
}