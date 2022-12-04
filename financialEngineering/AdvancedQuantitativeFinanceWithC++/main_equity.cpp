#include <iostream>
#include "my_equity_lib"

using namespace std;

int main()
{

	std::cout << "Hello from Advanced Quantitative Finance with C++" << std::endl;
    
    EQ1 eq1;
    
    double premium = eq1.get_premium();
    
    cout<<"premium = "<<premium<<endl;
    
    EQ2 eq2;
    
    double premium_basket = eq2.get_premium();
    
    cout<<"premium basket of stocks= "<<premium_basket<<endl;
	
	return 0;
}
