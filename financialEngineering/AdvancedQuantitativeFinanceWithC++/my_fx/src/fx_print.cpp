#include "my_fx/fx1.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

ostream &operator<<(ostream& os, const result_data& rs){
	int M{}, N{};

	N = rs.u.size();

	if (N)
		M = rs.u[0].size();

	os<<setw(10)<<" dtau = "<<rs.dtau<<endl;
	os<<setw(10)<<" alpha = "<<rs.alpha<<endl;
	os<<setw(10)<<" k = "<<rs.k<<endl;

	os<<endl<<"...... x and tau grids ........"<<endl<<endl;

	for (int i = 0; i<N; i++){
		os<<setw(5)<<"x "<<rs.x[i]<<endl;
		os<<setw(5)<<"S "<<rs.S[i]<<endl;
	}

	for (int j = 0; j<M; j++){
		os<<setw(5)<<"t "<<rs.t[j]<<endl;
		os<<setw(5)<<"tau "<<rs.tau[j]<<endl;
	}

	for (int i = 0; i<N; i++){
		os<<setw(5)<<"i "<<i<<setw(5)<<"u "<<rs.u[i][0]<<endl;
	}

	os<<endl<<"..... bcs ........"<<endl<<endl;

	for (int j = 1; j<M; j++){
		os<<setw(5)<<"j "<<j<<setw(12)<<"u[0][j] "<<rs.u[0][j]<<endl;
		os<<setw(5)<<"j "<<j<<setw(12)<<"u[N-1][j] "<<rs.u[N-1][j]<<endl;
	}

	os<<endl<<"..... u and v ........"<<endl<<endl;

	for (int j = 0; j<M; j++){
		for (int i = 0; i<N; i++){
			os<<setw(5)<<"i= "<<i<<", j= "<<j<<setw(11)<<" v[i][j] "<<rs.v[i][j]<<endl;
		}
	}

	os<<endl<<"premium = "<<rs.v[N/2][M-1]<<endl;

	return os;

}