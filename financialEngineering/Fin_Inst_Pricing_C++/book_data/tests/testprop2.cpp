// testprop2.cpp
//
// A class to test the CPS (Customer) system. The focus is on 
// Role modelling. To focus, we look at the Source system that have
// to do with the CPS::MAN subsystem. How many roles and what these
// roles are is determined by the different viewpoints in the 
// system.

#include "entity.cpp"
#include <string>
#include <iostream>


using namespace std;


int main()
{

	Property<string, string> name ("Name");
	Property<string, string> desc ("Description", "The Source system where all raw data comes from");

	Entity<string, string> Source("Source");	// The object that will have roles
	Source.AddProperty(name);
	Source.AddProperty(desc);


	// Now define roles

	// Role I: Conatct person for the request
	Entity<string, string> contact ("Contact Source for source data");
	// Build lowest level-properties
	//Property<string, string> name("Name", "Jeannet");
	name("Jeannet");
	Property<string, string> location("Location", "Amsterdam");
	Property<string, string> date("Date", "2003");
	contact.AddProperty(name);
	contact.AddProperty(location);
	contact.AddProperty(date);
	Source.addRole(&contact);
	contact.addRoleFiller (&Source);

	if (Source.hasRole("contact") == true)
		cout << "Yes, role contact\n";

	if (Source.hasRole("Student") == false)
		cout << "Source is not a student\n";

	if (contact.isARole() == true)
		cout << "contact is a role\n";

	// Role II: Type of source
	Entity<string, string> sourcetype ("Source ID");
	name("from the fax");
	sourcetype.AddProperty(name);

	string ip1 ("192.1.1.35");
	location(ip1);
	sourcetype.AddProperty(location);
	sourcetype.AddProperty(date);
	Source.addRole(&sourcetype);
	sourcetype.addRoleFiller (&Source);

	if (Source.hasRole("Source ID") == true)
		cout << "Yes, role Source ID\n";

	return 0;
}
