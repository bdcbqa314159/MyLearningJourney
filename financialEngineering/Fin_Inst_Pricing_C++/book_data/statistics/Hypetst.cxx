// hypetst.cxx
// Program to use the use of the hypergeometric distribution.
//
// Problem description.
// Small electric motors are shipped in lots of 50. Before shipping
// however, 5 motors are chosen at random and inspected. The lot is
// accepted if none of the chosen motors is defective. If one or more
// is defective, the entire shipment is inspected. Let us suppose that
// there are 3 defective motors in the lot. What is the probability
// that 100% inspection is required?
//
// Answer.
// This is an application of the hypergeometric distribution with
//
//		N = total lot size = 50
//		r = number of defectives = 3
//              n = number chosen without replacement = 5
//
// If X is the number of defective motors found, then 100% inspection
// is required if and only if X >= 1. We use the formula
//
//       P(X >= 1) = 1.0 - P(X = 0).
//
// (C) Datasim Education BV 1992-1999
//

#include <iostream.h>
#include "hypedist.cxx"

main()
{

	int nlot = 50;
	int def  = 3;
	int norep = 5;
	HyperGeometric<double, int> random_var(nlot, def, norep);

	double res = 1.0 - random_var.probability(0.0);
	cout << "Probability of 100% inspection is: " << res;

	return 0;
}

