#ifndef EQUITY1_H
#define EQUITY1_H

class EQ1
{
public:
    EQ1(){}
    EQ1(double T, double K, double S0, double sigma, double r, int N, int M) : T(T), K(K), S0(S0), sigma(sigma), r(r), N(N), M(M) {}

    double get_premium() const
    {
        return find_premium();
    }

private:
    double T{1}, K{100}, S0{100}, sigma{0.1}, r{0.05};
    int N{500}, M{10000};

    double find_premium() const;
};

#endif
