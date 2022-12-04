#include "my_fx/fx1.hpp"
#include <algorithm>
#include <cmath>

using namespace std;

result_data FX1::evaluate_data_and_premium() const{
	double dtau{}, alpha{}, k{};

	vector<double> t(M), tau(M), S(N), x(N);

	matrix<double> u, v;
	matrix_resize(u, N, M);
	matrix_resize(v, N, M);

	dtau = dt*(0.5*sigma*sigma);
	alpha = dtau/(dx*dx);
	k = r/(0.5*sigma*sigma);

	double xmin = -1, xmax = 1;

// MESH:
	for (int i = 0; i<N; i++){
		x[i] = xmin+i*dx;
		S[i] = K*exp(x[i]);
	}

	for (int j = 0; j<M; j++){
		t[j] = j*dt;
		tau[j] = (T-t[j])/(0.5*sigma*sigma);
	}

// INITIAL CONDITION
	for (int i = 0; i<N; i++){
		u[i][0] = max(exp(0.5*(k+1)*x[i]) - exp(0.5*(k-1)*x[i]), 0.);
	}

// BOUNDARY CONDITION

	for (int j = 1; j<M; j++){
		u[0][j] = 0.;

		if (barrier)
			u[N-1][j] = 0.;
		else
			u[N-1][j] = u[N-1][0];
	}

// COMPUTE FORWARD DIFFERENCE

	for (int j = 0; j<M-1; j++){
		for (int i = 1; i<N-1; i++){
			u[i][j+1] = alpha*u[i+1][j] + (1 - 2*alpha)*u[i][j] + alpha*u[i-1][j];
		}
	}

// TRANSFORM SOLUTION FROM X TO S COORDINATES

	for (int j = 0; j<M; j++){
		for (int i = 1; i<N; i++){
			v[i][j] = pow(K, (0.5*(1+k)))*pow(S[i], (0.5*(1-k)))*exp((k+1)*(k+1)*sigma*sigma*(T-t[i])/8.)*u[i][j];
		}
	}

	result_data result(alpha, dtau, k,x,S, t, tau, u,v);

	return result;


}