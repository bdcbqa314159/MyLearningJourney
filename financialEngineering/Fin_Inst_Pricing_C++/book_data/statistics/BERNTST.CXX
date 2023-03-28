// berntst.cxx
// Program to test the Bernoulli distri
//
// Problem description.
// Telephone calls come into a large exchange and in a given 3 hour
// period a total of 270 calls were received. Compute the probability
// of receiving 0, 1, 2, ... calsss in the next three minutes.
//
// Answer.
// This is an application of the Binomial an Bernoulli distributions. We then
// divide the 3 minute interval into enough subintervals in such a way that at most
// once call is received at the exchange during a given interval of time.
// We consider 18 intervals which results in each subinterval lasting 10
// seconds. We then consider each subinterval as a Bernoulli trial in which
// a call does (success) or does not take place (failure).
// In this case
// P(success) = P(incoming call during interval) = 1.5 * 10 / 60 = 0.25
//
// (C) Datasim bv 1992
//

#include <iostream.h>
#include <conio.h>
#include <math.h>
#include "binodist.hxx"
#include "miscfun.hxx"

main()
{
	BINODIST random(0.25, 18);
	clrscr();

	for (int j = 0; j < 10; j++)
	    cout << "\nProbability of " << j << " calls in 3 minutes is: "
		 << random.pdf(j);

	// Sanity check using the exact representation
	MISCFUN pp;
	double t = pp.combination(18, 2);
	t = t * pow(0.25, 2) * pow(0.75, 16);
	cout << "\n(Sanity check) Probability of 2 calls: " << t;

	return 0;
}
