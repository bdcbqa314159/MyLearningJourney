// tstiter5.cxx
//
// Test of input iterators to show how to read an input stream and output it to 
// an output stream with new line separation.
//
// (C) Datasim Education 1998

#include "common.hxx"

int main()
{ // Musser page 251

	istream_iterator<int> end_of_stream; // End-of-stream marker

	partial_sum(istream_iterator<int> (cin), end_of_stream, 
				ostream_iterator<int> (cout, "\n"));

	return 0;
}