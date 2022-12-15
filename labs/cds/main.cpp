#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

class time_
{
public:
    time_(int duration) : duration(duration), dt(vector<int>(duration))
    {
        for (int i = 0; i < duration; i++)
            dt[i] = i + 1;
    }
    int duration{};
    vector<int> dt{};
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

    vector<double> survP{}, defP{};
    int duration{};
};

class discountFactors
{
public:
    discountFactors(int duration, double riskFreeRate) : duration(duration), riskFreeRate(riskFreeRate), df(vector<double>(duration))
    {
        time_ test(duration);
        for (int i = 0; i < duration; i++)
            df[i] = exp(-riskFreeRate * test.dt[i]);
    }

    vector<double> df{};
    double riskFreeRate;
    int duration;
};

int main()
{
    cout << "Hey - let's build a cds from a cds." << endl;

    double probability_of_default{0.0173};
    double recovery_rate{0.25};
    double risk_free_rate{0.0611};
    double duration{6};
    // default occur mid-year.

    vector<double> time{1, 2, 3, 4, 5, 6};

    vector<double> prob_default_vec(6);
    vector<double> prob_survival_vec(6);

    prob_default_vec[0] = probability_of_default;
    prob_survival_vec[0] = 1 - probability_of_default;

    for (int i = 1; i < 6; i++)
    {
        prob_default_vec[i] = prob_survival_vec[i - 1] * probability_of_default;
        prob_survival_vec[i] = prob_survival_vec[i - 1] - prob_default_vec[i];
    }

    for (int i = 0; i < 6; i++)
    {
        cout << prob_default_vec[i] << " " << prob_survival_vec[i] << endl;
    }

    vector<double> df(6);
    for (int i = 0; i < 6; i++)
        df[i] = exp(-risk_free_rate * time[i]);

    for (double disc_f : df)
        cout << disc_f << endl;

    vector<double> premium_leg_no_default(6);
    for (int i = 0; i < 6; i++)
        premium_leg_no_default[i] = prob_survival_vec[i] * df[i];

    cout << "premium leg no default" << endl;
    for (auto x : premium_leg_no_default)
        cout << x << endl;

    cout << "======================" << endl;

    vector<double> df_mid_year(6);
    for (int i = 0; i < 6; i++)
        df_mid_year[i] = exp(-risk_free_rate * (time[i] - 0.5));

    vector<double> premium_leg_default(6);
    for (int i = 0; i < 6; i++)
        premium_leg_default[i] = 0.5 * prob_default_vec[i] * df_mid_year[i];

    cout << "premium leg default" << endl;
    for (auto x : premium_leg_default)
        cout << x << endl;

    cout << "======================" << endl;

    vector<double> recovery_leg(6);
    for (int i = 0; i < 6; i++)
        recovery_leg[i] = prob_default_vec[i] * df_mid_year[i] * (1 - recovery_rate);

    cout << "recovery leg default" << endl;
    for (auto x : recovery_leg)
        cout << x << endl;

    cout << "======================" << endl;

    double expectedReceivedPremium = accumulate(premium_leg_no_default.begin(), premium_leg_no_default.end(), 0.);
    double accrual = accumulate(premium_leg_default.begin(), premium_leg_default.end(), 0.);

    cout << "expectedReceivedPremium = " << expectedReceivedPremium << endl;

    double expectedPayableDCF = accumulate(recovery_leg.begin(), recovery_leg.end(), 0.);

    double spread = expectedPayableDCF / expectedReceivedPremium;

    cout << "cds price: " << spread * 10000 << endl;

    return 0;
}