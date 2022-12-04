#ifndef IR1_H
#define IR1_H
#include <vector>

using namespace std;

struct IR_results{
	IR_results(){}

	IR_results(vector<double>& datapoints, double value):datapoints(datapoints), value(value){

	}

	vector<double> datapoints;
	double value{};
};

class IR{

public:
	IR(){}

	IR(double notional, double K, double alpha, double sigma, 
		double dT, int N, int M): notional(notional), K(K), alpha(alpha), sigma(sigma),dT(dT), N(N),M(M){

	}

	IR(double K, double alpha, double sigma, 
		double dT, int N, int M): notional(notional), K(K), alpha(alpha), sigma(sigma),dT(dT), N(N),M(M){

	}

	IR_results get_simulation_data() const{
		return run_LIBOR_simulations();
	}



private:
	double notional{}, K(0.05), alpha{0.5}, sigma{0.15}, dT{0.5};
	int N{4}, M{10000};

	IR_results run_LIBOR_simulations() const;
};




#endif