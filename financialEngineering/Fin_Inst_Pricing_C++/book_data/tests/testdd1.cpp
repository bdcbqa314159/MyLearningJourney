// testdd1.cpp
//
// Testing weighted graphs.
//

#include "weightedgraph.cpp"
#include "Array.cpp"
#include <iostream.h>

class Point
{
public:
		double x,y;

		Point () { x = y = 0;}
		Point (double xc, double yc) { x = xc; y = yc;}
		Point (double cc) { x = y = cc;}
};

void print(const Point& p)  // T == Point
{
	cout<< "(" << p.x << " " << p.y << ")" << endl;
}

void printwg(const WeightedGraph<long, Point, double>& wg )  // T == weighted graph
{ // Print a weighted graph

	wg.dftraverse(1, print);
	
}

int main()
{

	Array<Point, long> arr(8, 1);
	arr[1] = Point(13);
	arr[2] = Point(10);
	arr[3] = Point(25);
	arr[4] = Point(2);
	arr[5] = Point(12);
	arr[6] = Point(20);
	arr[7] = Point(31);
	arr[8] = Point(29);


	WeightedGraph<long, Point, double> myfirst(arr);

	myfirst.path(1,2, 2.4);
	myfirst.path(1,3, 0.5);
	myfirst.path(2,4, 1.6);
	myfirst.path(2,5, 2.4);
	myfirst.path(3,6, 0.5);
	myfirst.path(3,7, 1.6);
	myfirst.path(7,8, 2.4);

	cout << "Depth first\n";

	myfirst.dftraverse(1, print);

	cout << "Breadth first\n";

	myfirst.bftraverse(1, print);

//	myfirst.debug_print();


	// Create an array of Weighted graphs
	Array<WeightedGraph<long, Point, double>, long> nested_array(2, 1); // Length 2, start index 1

	nested_array[1] = myfirst;
	nested_array[2] = myfirst;

	WeightedGraph<long, WeightedGraph<long, Point, double>, double> rec(nested_array);

	rec.path(1, 2, 100.75);

	cout << "Navigation in a recursive graph\n";

	rec.dftraverse(1, printwg);

	// Now we would like to modify a point deep in the recursive graph
	return 0;
}