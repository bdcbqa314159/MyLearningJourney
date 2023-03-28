
// miscfun.cxx
//
// Last modification dates:
//
// 1994-2-7: All member functions are now static.
// 1999-1-5: DD some new functions pow() and exp()
//
// Code file for the class MISCFUN which contains a number of useful
// functions which are needed in other areas.
// Thus MISCFUN is a server class for other classes.
//
// (C) Datasim Education BV 1992-1999

#include "miscfun.hxx"
#include <math.h>
#include <vector>
using namespace std;

/*
double MISCFUN::gamma_series(double a, double x)
{ // Series development for the incomplete gamma function
  // (see Press et al page 160).

  // This function (as with gamma_cf()) uses two global variables:
  //
  // STOP_CONDITION; how many times should we iterate before stopping?
  // GAMMA_TOL; desired tolerance in calculating the function.
  // These constants would be found in common blocks or as PARAMETER
  // statements in Fortran. In this case they are defined in the file
  // constant.hxx.

  // No preconditions or checking is needed here because the client
  // function which calls this function (that is, gamma(double, double))
  // gives correct arguments. Furthermore, gamma_series() is private, so
  // it cannot be accessed by functions external to MISCFUN.

	MISCFUN m1;
	double log_gam = log(m1.gamma(a));
	double ap = a;
	double result = 1.0 / a;        // gamma(a) / gamma(a + 1)
	double tmp = result;

	bool converged = false;
	for (int j = 0; j < STOP_CONDITION; j++)
	{
	    ap += 1.0;;
	    tmp = (tmp * x) /ap;
	    result += tmp;

	    // Test for convergence; we use the 'break' statement to get out
	    // of the loop; this would correspond to a 'GOTO' in Fortran.
	    if (fabs(tmp) < (fabs(result) * GAMMA_TOL))
	    {
	       converged = true;
	       break;
	    }
	}

	// At this stage it is possible that the convergence condition has
	// not be met. In this case the value returned cannot be trusted
	// and we thus give an UNDEFINED value. It is then up to the client
	// to decide what should be done with this value.
	if (converged == TRUE)
	   result = result * exp(- x + (a*log(x)) - log_gam);
	else
	   result = UNDEFINED;

	return result;
}
*/

MISCFUN::MISCFUN()
{ // Empty constructor. This is in fact a sort of 'dummy' constructor
  // but we include it because MISCFUN could contain member data at a
  // future revision and this data could be initialised here.

}

double MISCFUN::fact(int n)
{ // The n-factorial; by default 0! == 1! == 1. Note the use of
  // the recursive function call (this feature is not present in
  // all languages). For example, it Fortran it is necessary to use
  // an internal array to simulate the stack mechansisms in recursion.

	// Precondition: n cannot be negative
	if (n < 0)
	   return 0.0;

	if ((n == 0) || (n == 1))
	   return 1.0;

	return (double (n) * fact(n-1));
}

double MISCFUN::combination(int n, int k)
{ // The binomial coefficient. This is equivalent to the number of ways
  // of choosing k out of n differenet object, disregarding order.

	// Precondition: n > 0 and 0 <= k <= n
	if (n <= 0 || k < 0 || k > n)
	   return 0.0;

	// At this stage we are assured that the fact function is
	// never zero, so division by zero is not possible.
	double t1 = fact(n);
	double t2 = fact(n-k) * fact(k);
	return(t1/t2);
}


double MISCFUN::gamma(int k)
{ // The gamma function for integral values of its argument. It can
  // be mathematically proved that this is the same as (k - 1)! when
  // k >= 0.

	if (k < 0)
	   return 0.0;
	else
	   return fact(k - 1);
}


double MISCFUN::gamma(double x)
{ // The gamma integral for non-integral argument. This uses a series
  // representation due to Lanczos. We take a finite number of terms in
  // the series and the error in approximation is consequently "hard-coded"
  // into this function. However, the approximation should be good enough
  // for most purposes.

	// Precondition: The argument x must be positive
	if (x <= 0.0)
	   return 0.0;

	// First define the coefficients in the series expansion. We
	// use the class DLIST (arrays of double precision numbers).
	vector<double> arr(6);
	arr[0] = 76.18009173;
	arr[1] = -86.50532033;
	arr[2] = 24.01409822;
	arr[3] = -1.231739516;
	arr[4] = 0.120858003e-2;
	arr[5] = -0.536382382e-5;

	// Decrement x by 1; in fact x is a temporary copy (call by value)
	// and there is thus no need to define an extra variable in this
	// function (such as double xx = x - 1.0).
	x -= 1.0;

	double t = x + 5.5;
	t = (x + 0.5) * log(t) - t;

	// We now calculate the series part of the Lanczos formula.
	double series = 1.0;
	for (int j = 0; j <= 5; j++)
	{
	     x = x + 1.0;
	     series += arr[j] / x;
	}

	double result = t  + log(series * sqrt (2.0 * 3.1415));
	result = exp(result);

	return result;
}
/*
double MISCFUN::gamma(double a, double x)
{ // The incomplete gamma function P(a, x). Note that the help
  // function gamma_series() has the same arguments as this function
  // which adds to the readability of this piece of code.

	// Precondition: Conditions placed on both a and x
	if (a <= 0.0 || x <= 0.0)
	   return 0.0;

	return gamma_series(a, x);   // Series representation
}

double MISCFUN::gammac(double a, double x)
{ // The complement of the incomplete gamma function (also called an
  // incomplete gamma function).

	// Precondition
	if (x <= 0.0 || a <= 0.0)
	   return 0.0;

	return 1.0 - gamma_series(a, x);
}

double MISCFUN::beta(double z, double w)
{ // The beta function B(z, w) (calculated in terms of the gamma function).

	// Precondition: the sum z + w must be positive (this is
	// to avoid possible division by zero in this function).
	if (z + w <= 0.0)
	   return 0.0;

	return (gamma(z) * gamma(w)) / gamma(z+w);
}

double MISCFUN::erf(double x)
{ // The error function. This uses the incomplete gamma function.

	double res = gamma(0.5, x*x);
	if (x < 0.0)
	   res = - res;

	return res;
}

double MISCFUN::erfc(double x)
{ // The complementary error function. Uses the imcomplete gamma function
  // and the complementary gamma function.

	double res = 1.0 + gamma(0.5, x*x);
	if (x >= 0.0)
	   res = gammac(0.5, x*x);

	return res;
}
*/
