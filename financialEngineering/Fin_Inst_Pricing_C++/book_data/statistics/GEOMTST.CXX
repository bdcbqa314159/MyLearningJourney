// geomtst.cxx
// Program to show the use of the geometric distribution.
//
// Problem description.
// The probability that a thunderstorm will occur on any given day
// during the summer (July and August) is 0.1. If we assume independence
// from day to day, what is the probability that the first thunderstorm
// of the summer season occurs on August 3?
//
// Answer.
// August 3 corresponds to the 34th day and we wish to calculate
// P(X = 34). In other words, the first 33 no thunder occurs.
//
// (C) Datasim bv 1992

#include <iostream.h>
#include "geomdist.hxx"

main()
{

	double thunder_yes = 0.1;
	GEOMDIST thunder(thunder_yes);

	double res = thunder.pdf(34);

	cout << "\nResult: " << res;

	return 0;
}
//