#include <iostream>
#include "my_fx_lib"

using namespace std;

int main()
{

	std::cout << "Hello from Advanced Quantitative Finance with C++" << std::endl;
    FX1 fx;

    auto result = fx.get_data_and_premium();

    cout<<result<<endl;
    
	
	return 0;
}