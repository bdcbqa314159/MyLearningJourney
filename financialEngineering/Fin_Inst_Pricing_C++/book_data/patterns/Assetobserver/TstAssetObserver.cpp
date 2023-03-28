// TstAssetObserver.cpp
//
// (C) Datasim Education BV 2001-2004

#include "asset.hpp"
#include "option.hpp"

int main()
{
	// Create a Asset object
	Asset ass;
	
	// Just increase the Asset without observing it
    ass.setStock(100.0);
	
	// Create an observer
	Option observer1;			// Default is a Call
	observer1.U = (19.0);
	observer1.K = (19.0);
	observer1.T = (0.75);
	observer1.r = (0.10);
	observer1.sig = (0.28);
	observer1.b = (0.0);

	cout << "Put option on a future: " << observer1.Price() << endl;

	ass.AddObserver(&observer1);

	// Increase the Asset
    ass.setStock(19.0);

	// Create another observer
	Option observer2;
	ass.AddObserver(&observer2);


	// Increase the Asset
    ass.setStock(16.5);

	// Remove the first observer
	ass.DeleteObserver(&observer1);

	// Decrease/Increase the Asset, bingo
    ass.setStock(56.3);

	return 0;

}

