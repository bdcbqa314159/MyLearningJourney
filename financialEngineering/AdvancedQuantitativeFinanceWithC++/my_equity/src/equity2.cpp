#include "my_equity/equity2.hpp"
#include "my_random/random.hpp"
#include <algorithm>
#include <vector>
#include <cmath>

double EQ2::find_premium() const
{
    double sumpayoff = 0.;
    double premium = 0.;
    double dt = T / N;

    std::vector<double> S1(N + 1);
    std::vector<double> S2(N + 1);

    SampleBoxMuller normal;

    for (int j = 0; j < M; j++)
    {
        S1[0] = S10;
        S2[0] = S20;
        for (int i = 0; i<N; i++){
            double epsilon1 = normal();
            double epsilon2 = normal();
            S1[i+1] = S1[i]*(1+ r*dt+sigma1*sqrt(dt)*epsilon1);
            S2[i+1] = S1[i]*(1+ r*dt+sigma2*sqrt(dt)*(epsilon1*rho +sqrt(1-rho*rho)*epsilon2));
            
        }
        
        sumpayoff+=std::max(S1[N],S2[N]);
        
    }
    
    premium = exp(-r*T)*(sumpayoff/M);
    return premium;
}

