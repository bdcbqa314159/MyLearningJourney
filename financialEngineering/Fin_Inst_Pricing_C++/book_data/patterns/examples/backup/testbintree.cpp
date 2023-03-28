// tetbintree.cpp
//
// Creating a structure for the binomial tree
//
// (C) Datasim Education BV 2003
//

#include "vector.cpp"
#include "arraymechanisms.cpp"

int main()
{
	
	int N = 2; // Number of periods

	Vector<Vector<double, int>, int> tree(N+1, 1);


	// Initialise tree vectors (give sizes of vectors)
	for(int ii = tree.MaxIndex(); ii >= tree.MinIndex(); ii--)
	{
		tree[ii] = 	Vector<double, int>(ii);	
	}


	for(int i = tree.MaxIndex(); i>= tree.MinIndex(); i--)
	{
		for(int j = 1;j <= i;j++)
		{
			tree[i][j] = i;
		}
	}	

	for(int k = tree.MaxIndex(); k >= tree.MinIndex(); k--)
	{
			print (tree[k]);
	
	}	


	return 0;
}
