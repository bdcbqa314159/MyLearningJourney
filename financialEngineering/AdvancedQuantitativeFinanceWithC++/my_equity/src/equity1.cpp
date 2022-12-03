#include "my_equity/equity1.hpp"
#include "my_random/random.hpp"
#include <algorithm>
#include <vector>
#include <cmath>

double EQ1::find_premium() const
{
    double sumpayoff = 0.;
    double premium = 0.;
    double dt = T / N;

    std::vector<double> S(N + 1);

    SampleBoxMuller normal;

    for (int j = 0; j < M; j++)
    {
        S[0] = S0;
        for (int i = 0; i<N; i++){
            double epsilon = normal();
            S[i+1] = S[i]*(1+ r*dt+sigma*sqrt(dt)*epsilon);
            
        }
        
        static double diff = 0.;
        diff = S[N]-K;
        sumpayoff+=std::max(diff, 0.);
        
    }
    
    premium = exp(-r*T)*(sumpayoff/M);
    return premium;
}
