#ifndef EQUITY2_H
#define EQUITY2_H

class EQ2
{
public:
    EQ2(){}
    EQ2(double T, double r, double S10, double S20, double sigma1, double sigma2,double rho, int N, int M) : T(T),r(r), S10(S10), S20(S20), sigma1(sigma1), sigma2(sigma2), rho(rho), N(N), M(M) {}

    double get_premium() const
    {
        return find_premium();
    }

private:
    double T{1}, r{0.05}, S10{120},S20{100}, sigma1{0.1},sigma2{0.15}, rho{0.5};
    int N{300}, M{1000};

    double find_premium() const;
};

#endif
