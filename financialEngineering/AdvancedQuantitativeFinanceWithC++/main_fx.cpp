#include <iostream>
#include "my_fx_lib"

using namespace std;

int main()
{

	std::cout << "Hello from Advanced Quantitative Finance with C++" << std::endl;
    FX1 fx;

    auto result = fx.get_data_and_premium();

    cout<<result<<endl;

    FX1 fx1;
    fx1.set_barrier(true);
    
    auto result1 = fx1.get_data_and_premium();

    cout<<result1<<endl;
	
	return 0;
}