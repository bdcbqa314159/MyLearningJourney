// chap4set2.cpp
//
// Testing set-like operations using vectors.
//
// (C) Datasim Education BV 2003

#include "common.hxx"

int main()
{
	vector<int> v1(4, 2); // size == 4
	vector<int> v2(5, 3);

	ostream_iterator<int> iter (cout, " ");

	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), iter);

	return 0;
}