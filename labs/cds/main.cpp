#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

ostream &operator<<(ostream &os, const vector<double> &data)
{
    for (double x : data)
        os << x << endl;
    return os;
}

double dot(const vector<double> &v1, const vector<double> &v2)
{
    if (v1.size() != v2.size())
        throw string{"Error size must be equal"};
    double result{};
    for (int i = 0; i < v1.size(); i++)
        result = v1[i] * v2[i];
    return result;
}

vector<double> operator*(const vector<double> &v1, const vector<double> &v2)
{
    if (v1.size() != v2.size())
        throw string{"Error size must be equal"};
    vector<double> result(v1.size());
    for (int i = 0; i < v1.size(); i++)
        result[i] = v1[i] * v2[i];
    return result;
}

vector<double> operator*(const vector<double> &v1, double lambda)
{
    vector<double> result(v1.size());
    for (int i = 0; i < v1.size(); i++)
        result[i] = v1[i] * lambda;
    return result;
}

vector<double> operator+(const vector<double> &v1, double lambda)
{
    vector<double> result(v1.size());
    for (int i = 0; i < v1.size(); i++)
        result[i] = v1[i] + lambda;
    return result;
}

vector<double> operator-(const vector<double> &v1, double lambda)
{
    return operator+(v1, -lambda);
}

class timer
{
public:
    timer() {}
    timer(int duration) : duration(duration)
    {
    }

    vector<double> operator()()
    {
        vector<double> result(duration);
        for (int i = 0; i < duration; i++)
            result[i] = i + 1;
        return result;
    }

    int duration{};
};

class creditRates
{
public:
    creditRates(int duration) : duration(duration), survP(vector<double>(duration)), defP(vector<double>(duration)) {}

    void operator()(double hazardRate)
    {
        defP[0] = hazardRate;
        survP[0] = 1 - hazardRate;

        for (int i = 1; i < duration; i++)
        {
            defP[i] = survP[i - 1] * hazardRate;
            survP[i] = survP[i - 1] - defP[i];
        }
    }

    double giveSpread(double hazardRate, const vector<double> &df_no_def, const vector<double> &df_def, double rr)
    {
        operator()(hazardRate);
        vector<double> premLeg = survP * df_no_def;
        vector<double> accrual = defP * df_def * 0.5;
        vector<double> protLeg = defP * df_def * (1 - rr);

        double protection = accumulate(protLeg.begin(), protLeg.end(), 0.);
        double expected_premium = accumulate(premLeg.begin(), premLeg.end(), 0.);
        double expected_accrual_mid = accumulate(accrual.begin(), accrual.end(), 0.);
        double spread = protection / (expected_premium + expected_accrual_mid);

        return spread;
    }

    vector<double> survP{}, defP{};
    int duration{};
};

class discounting
{
public:
    discounting() {}
    discounting(double riskFreeRate) : riskFreeRate(riskFreeRate) {}

    vector<double> operator()(const vector<double> &times)
    {

        vector<double> disc_factors(times.size());
        for (int i = 0; i < times.size(); i++)
            disc_factors[i] = exp(-riskFreeRate * times[i]);

        return disc_factors;
    }

    double riskFreeRate{0};
};

class prototypeCDS
{
public:
    prototypeCDS() {}
    prototypeCDS(double spread, int duration, double rfr, double rr) : spread(spread), duration(duration), rfr(rfr), rr(rr)
    {
    }

    double calibration_HR()
    {
        timer myTimes(duration);
        discounting myDiscount(rfr);
        vector<double> dt = myTimes();
        vector<double> dt_mid = dt - 0.5;

        vector<double> df_no_def = myDiscount(dt);
        vector<double> df_def = myDiscount(dt_mid);

        creditRates myCreditRates(duration);

        double hr0 = 0.1;
        double hr1 = 0.9;
        double hr2{};

        double spread0{};
        double spread1{};
        double spread2{};

        spread0 = myCreditRates.giveSpread(hr0, df_no_def, df_def, rr) - spread;
        spread1 = myCreditRates.giveSpread(hr1, df_no_def, df_def, rr) - spread;

        while (abs(spread0 - spread1) > 1e-9)
        {
            hr2 = hr1 - spread1 * (hr1 - hr0) / (spread1 - spread0);
            swap(hr0, hr1);
            swap(hr1, hr2);
            spread0 = myCreditRates.giveSpread(hr0, df_no_def, df_def, rr) - spread;
            spread1 = myCreditRates.giveSpread(hr1, df_no_def, df_def, rr) - spread;
        }

        return hr2;
    }

    double spread{};
    int duration{1};
    double rfr{}, rr{}, def_prob_init{0.5};
};

int main()
{
    cout << "Hey - let's build a cds from a video." << endl;

    double probability_of_default{0.0173};
    double recovery_rate{0.25};
    double risk_free_rate{0.0611};
    double duration{6};
    // default occur mid-year.

    cout << "========Pricing after watching the video==========" << endl;

    creditRates cr(duration);
    timer myTimes(duration);
    discounting myDiscount(risk_free_rate);
    vector<double> dt = myTimes();
    vector<double> dt_mid = dt - 0.5;

    vector<double> df_no_def = myDiscount(dt);
    vector<double> df_def = myDiscount(dt_mid);

    double spread = cr.giveSpread(probability_of_default, df_no_def, df_def, recovery_rate);
    cout << "cds price as in the video: " << spread << endl;

    prototypeCDS myCDS(spread, duration, risk_free_rate, recovery_rate);

    double myHR = myCDS.calibration_HR();
    cout << "hazard rate calibrated: " << myHR << endl;
    cout << "hazard rate from the video: " << probability_of_default << endl;

    double repricedSpread_original = cr.giveSpread(myHR, df_no_def, df_def, recovery_rate);

    cout << "cds repriced after calibration: " << repricedSpread_original << endl;

    return 0;
}