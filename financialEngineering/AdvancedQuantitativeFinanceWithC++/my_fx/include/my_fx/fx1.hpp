#ifndef FX1_H
#define FX1_H

#include "my_linalg/matrix.hpp"
#include <iostream>
#include <iomanip>

using vec = std::vector<double>;

struct result_data{
	result_data(){}

	result_data(double alpha, double dtau, double k, vec x, vec S, vec t,
		vec tau, matrix<double> u, matrix<double> v):alpha(alpha),
		dtau(dtau),k(k),x(x), S(S),t(t),tau(tau),u(u), v(v){

	}

	double alpha, dtau, k;
	vec x, S, t, tau;
	matrix<double> u, v;

	friend std::ostream& operator<<(std::ostream& os, const result_data& rs);
};

class FX1{
public:
	FX1(){}

	FX1(double T, double K, double S0, double sigma, double r, double dt, double dx, int N, int M):
	T(T), K(K), S0(S0), sigma(sigma), r(r), dt(dt), dx(dx), N(N), M(M){}

	result_data get_data_and_premium() const{
		return evaluate_data_and_premium();
	}

private:
	double T{0.5}, K{75}, S0{75}, sigma{0.3}, r{0.05}, dt{0.1}, dx{0.5};
	int N{5}, M{6};

	result_data evaluate_data_and_premium() const;
};




#endif