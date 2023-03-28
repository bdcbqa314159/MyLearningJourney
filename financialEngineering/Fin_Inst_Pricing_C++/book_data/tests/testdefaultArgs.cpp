// testdefaultArgs.cpp
//
//

#include <string>
#include "property.cpp"
#include <iostream>

using namespace std;

int main()
{

	Property<string, double> s1("Rocky", 4.0);
	Property<string> s2("Rocky", 4.0);
	Property<> s3("Rocky", 4.0);
	
	cout << s1.name() << ", " << s1() << endl;
	cout << s2.name() << ", " << s2() << endl;
	cout << s3.name() << ", " << s3() << endl;


	return 0;
}
