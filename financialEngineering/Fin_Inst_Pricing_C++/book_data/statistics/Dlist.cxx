// dlist.cxx
//
// Member functions of the Double precision LIST class.
// This class represent an array of double precision numbers.
//
// Modification dates:
//
// 1993-5-15 DD Statistical functions added.
// 1993-6-11 DD percentage() and absolute() functions added (interesting for
// 	     statistical and business type problems).
// 1993-6-12 DD Modifier functions scale(), subtract(), swap(); also the
// 	     operator - between doubles and DLIST; constructor DLIST(double, DLIST).
// 1993-7-12 DD two new constructors DLIST(double, double, int) and
//	     DLIST(double, doubl, int)
// 1993-7-17 DD diff_product() added; needed for use in Lagrange polynomials
// 1993-9-4  DD Name changed DLIST --> DSDLIST.
// 
// Copyright (C) 1992, Datasim BV, Amsterdam.

#include "constant.hxx"
#include "dlist.hxx"                                  // Class definition

BOOLEAN equal(double d1, double d2)
{if (d1 == d2) return TRUE; else return FALSE; }

void DSDLIST::all_mem(int& j)
{ // Allocate memory for val

	// We allocate one extra double in the array for use with indices.
	val = new double [j + 1];
	if (val == 0)
	{ // Unable to allocate enough memory, so do array of length 1

		j = 1;
		val = new double[j + 1];
	}

	// Initialise the array (arbitrarily) to 0.0
	for (int k = 0; k < j; k++)
		val[k] = 0.0;

	val[j] = UNDEFINED;
}

BOOLEAN DSDLIST::check_range(int j) const
{ // Is the index valid?

	if (j < 0 || j >= sz)
	   return FALSE;

	return TRUE;
}

void DSDLIST::def(double d)
{
   for (int i = 0; i < sz; i++)
	 val[i] = d;
}

DSDLIST::DSDLIST (int elements, double val)
{ // Create a DSDLIST with elements

	// Precondition (class invariant)
	if (elements < 1)
	   elements = 1;

	all_mem(elements);
	sz = elements;
	def(val);
}

DSDLIST::DSDLIST (double d)                // Create a DSDLIST containing only
{
	sz = 1;                              // the value d.
	all_mem(sz);
	val[0] = d;
}

DSDLIST::DSDLIST (const DSDLIST& lst2)             // Copy initializer.
{
	// No precondition; if you give rubbish you will get rubbish
	int new_size = lst2.size();
	all_mem(new_size);
	sz = new_size;
	for (int i = 0; i < sz; i++)
	     val[i] = lst2.val[i];

}

DSDLIST::DSDLIST(double factor, const DSDLIST& darr)
{ // Construct a DSDLIST which is a multiple of another vector

        val = NULL;
	DSDLIST tmp = darr*factor;
	*this = tmp;		// Can be optimised
}

DSDLIST::DSDLIST (double start, double offset, int n)
{ // Array of length n with values at a certain offset

	// There are n elements in the array.

	// Precondition
	if (n < 2)
	  n = 2;

	sz = n;
	all_mem(sz);

	val[0] = start;
	for (int j = 1; j < sz; j++)
	    val[j] = val[j - 1] + offset;
}

DSDLIST::DSDLIST (double start, int n, double end)
{ // Array of length n with values in range [start, end]

	// Precondition
	if (n < 2)
	  n = 2;

	double increment = (end - start) / double(n - 1);

	sz = n;
	all_mem(sz);

	val[0] = start;
	val[sz - 1] = end;

	for (int j = 1; j < sz - 1; j++)
	    val[j] = val[j - 1] + increment;
}

DSDLIST::DSDLIST (const DSDLIST& x, const DSDLIST& y, double alpha)
{ // Convex combination of x and y

	// Precondition
	if (x.sz != y.sz)
	   *this = DSDLIST(UNDEFINED);

	DSDLIST result(x.sz);
	sz = x.sz;
        all_mem(sz);
	double omalpha = 1.0 - alpha;
	for (int j = 0; j < sz; j++)
	    val[j] = (alpha * x.val[j]) + (omalpha * y.val[j]);

}

DSDLIST::~DSDLIST()
{
	delete [] val;

	// What happens if delete a NULL (0) pointer? (general question)
	// ARM (page 63) says "Deleting a pointer with the value zero,
	// however, is guaranteed to be harmless". Thus, deleting the
	// pointer 'val' above will always work.
}

int DSDLIST::size() const
{
   return sz;
}

void DSDLIST::set_val (int j, double d)
{
   // Default precondition; do nothing if you don't satisfy the
   // conditions
   if (check_range(j) == TRUE)
	  val[j]=d;
}

// Iterator functions which give information on the elements of the vector
DSDLIST abs(const DSDLIST& dlist)
{ // The array with all positive values

	DSDLIST result(dlist.sz);
	for (int j = 0; j < dlist.sz; j++)
		result[j] = fabs(dlist[j]);

	return result;
}

double min(const DSDLIST& dlist)
{ // Smallest element of array

	double res = dlist[0];

	for (int i = 0; i < dlist.sz; i++)
	{
		if (res > dlist[i])
		   res = dlist[i];
	}

	return res;
}

double max(const DSDLIST& dlist)
{ // Largest element of array

	return dlist.inf_norm();
}

double avg(const DSDLIST& dlist)
{ // Average value of array

	return sum(dlist) / double(dlist.sz);
}

double sum(const DSDLIST& dlist)
{ // Sum of all elements of array

	double res = 0.0;

	for (int i = 0; i < dlist.sz; i++)
	{
		res += dlist[i];
	}

	return res;
}

double product(const DSDLIST& dlist)
{ // Product of elements of array

	double res = 1.0;

	for (int i = 0; i < dlist.sz; i++)
	{
		res *= dlist[i];
	}

	return res;
}

DSDLIST DSDLIST::hadamard(const DSDLIST& dlist2) const
{ // Hadamard product of two vectors

	// Precondition: arrays must have the same size
	if (sz != dlist2.sz)
	   return DSDLIST(UNDEFINED);

	DSDLIST result(sz);

	for (int i = 0; i < sz; i++)
	{
		result[i] = val[i] * dlist2[i];
	}

	return result;

}

DSDLIST DSDLIST::absolute() const
{ // Array with all positive values

	DSDLIST result(sz);
	for (int j = 0; j < sz; j++)
	   result[j] = fabs(val[j]);

	return result;
}

DSDLIST DSDLIST::percentage() const
{ // Array of percentages

	double sum = one_norm();
	DSDLIST result(sz);
	if (equal(sum, 0.0) == TRUE)
	   return result;

	for (int j = 0; j < sz; j++)
	   result[j] = (fabs(val[j]) * 100.0) / sum;

	return result;
}

DSDLIST DSDLIST::scurve() const
{
	DSDLIST result(sz);
	result[0] = val[0];
	for (int i = 1; i < sz; i++)
	      result[i] = result[i-1] + val[i];

	return result;
}

int DSDLIST::index_min() const
{ // Index of array having minimum value

	double tmp = val[0];
	int result = 0;	// We assume that 0 is the candidate for kick-off

	for (int i = 1; i < sz; i++)
	{
		if (val[i] < tmp)
		{
		   tmp = val[i];
		   result = i;
		}
	}

	return result;
}

int DSDLIST::index_max() const
{ // Index of array having maximum value

	double tmp = val[0];
	int result = 0;	// We assume that 0 is the candidate for kick-off

	for (int i = 1; i < sz; i++)
	{
		if (val[i] > tmp)
		{
		   tmp = val[i];
		   result = i;
		}
	}

	return result;
}

int DSDLIST::index_absmin() const
{ // Index of array having absolute minimum value

	DSDLIST new_dlist = abs(*this);		// New array with all positive values

	return new_dlist.index_min();
}

int DSDLIST::index_absmax() const
{ // Index of array having absolute maximum value

	DSDLIST new_dlist = abs(*this);

	return new_dlist.index_max();
}

int count(const DSDLIST& dlist)
{ // The number of non-zero elements in the array

	int result = 0;
	for (int j = 0 ; j < dlist.sz; j++)
	{
		if (equal(dlist.val[j], 0.0) == FALSE)
		   result++;
	}

	return result;
}

// Basic vector algebra
double DSDLIST::inner_product(const DSDLIST& dlist2) const
{ // Inner product of two dlists

	// Precondition
	if (sz != dlist2.sz)
	   return UNDEFINED;

	double result = 0.0;
	for (int i = 0; i < sz; i++)
		result += val[i] * dlist2.val[i];

	return result;
}

double DSDLIST::inner_product(const DSDLIST& dlist2, const DSDLIST& dlist3) const
{ // Triple inner product

	// Precondition
	if (sz != dlist2.sz && sz != dlist3.sz)
	   return UNDEFINED;

	double result = 0.0;
	for (int i = 0; i < sz; i++)
		result += val[i] * dlist2[i] * dlist3[i];

	return result;
}

double DSDLIST::inf_norm(const DSDLIST& dlist) const
{ // The L-infinaty norm

	double res = 0.0;
	double tmp;

	// Precondition
	if (sz != dlist.sz)
	   return UNDEFINED;

	// This code was set up for efficiency reasons (there is some
	// duplication of code).
	for (int i = 0; i < sz; i++)
	{
		tmp = fabs(val[i] - dlist.val[i]);
		if (res < tmp)
		   res = tmp;
	}

	return res;
}

double DSDLIST::inf_norm() const
{ // The L-infinity norm, optimize later

	double res = 0.0;
	double tmp;

	for (int i = 0; i < sz; i++)
	{
		tmp = fabs(val[i]);
		if (res < tmp)
		   res = tmp;
	}

	return res;
}

double DSDLIST::one_norm(const DSDLIST& dlist) const
{ // The L-1 norm

	double res = 0.0;

	// Precondition
	if (sz != dlist.sz)
	   return UNDEFINED;

	for (int i = 0; i < sz; i++)
		res += fabs(val[i] - dlist.val[i]);

	return res;
}

double DSDLIST::one_norm() const
{ // The L-1 norm

	double res = 0.0;

	for (int i = 0; i < sz; i++)
		res += fabs(val[i]);

	return res;
}

double DSDLIST::two_norm(const DSDLIST& dlist) const
{ // The L-2 norm

	double res = 0.0;
	double tmp;

	// Precondition
	if (sz != dlist.sz)
	   return UNDEFINED;

	for (int i = 0; i < sz; i++)
	{
		tmp = val[i] - dlist.val[i];
		res += tmp * tmp;
	}

	return sqrt(res);
}

double DSDLIST::two_norm() const
{ // The L-2 norm

	double res = 0.0;
	double tmp;

	for (int i = 0; i < sz; i++)
	{
		tmp = val[i];
		res += tmp * tmp;
	}

	return sqrt(res);
}

double DSDLIST::diff_product(int j) const
{ // Product of terms x[j] - x[k] with j != k

	double con = val[j];
	double result = 1.0;
	for (int k = 0; k < sz; k++)
	{
	    if (k!= j)
		result *= con - val[k];
	}

	return result;
}

// Statistical functions
double mean(const DSDLIST& dlist)
{ // Mean value

	return avg(dlist);
}

double variance(const DSDLIST& dlist)
{ // Variance

	double result = 0.0;
	double tmp;
	double m = avg(dlist);	// Same result as mean(), but more efficient!
	for (int j = 0; j < dlist.sz; j++)
	{
		tmp = dlist.val[j] - m;
		result += tmp*tmp;
	}

	if (dlist.sz > 1)
	   return result / double (dlist.sz - 1);

	return UNDEFINED;
}

double std(const DSDLIST& dlist)
{ // Standard deviation = sqrt(variance(dlist))

    if (dlist.sz < 2 )
	return UNDEFINED;

	return sqrt(variance(dlist));
}

double sqr(const DSDLIST& dlist)
{ 	// square of dlist
	double total = 0;
	double tmp;

	for (int j = 0; j < dlist.sz; j++)
	{
		tmp = dlist.val[j];
		total += tmp*tmp;
	}

	if (dlist.sz > 1)
	   return total;

	return UNDEFINED;
}

DSDLIST DSDLIST::operator - () const
{ // Unary minus

	DSDLIST res(sz);
	for (int j = 0; j <= sz - 1; j++)
		res.val[j] = - val[j];

	return res;
}

DSDLIST& DSDLIST::operator = (const DSDLIST &arr2)
{
        if(this == &arr2)
                return *this;

        if (val != NULL)
                delete [] val;

	 // Only now can we give size a value
	 int size = arr2.sz;
	 all_mem(size);
	 sz = arr2.sz;
	 for (int j = 0; j < sz; j++)
	      val[j] = arr2.val[j];

	return  *this;
}

DSDLIST& DSDLIST::operator = (double d)
{

	int dim = sz;

        if (val != NULL)
                delete [] val;

	all_mem(dim);
	sz = dim;
	for (int j = 0; j < sz; j++)
	     val[j] = d;

	return *this;
}


DSDLIST& DSDLIST::operator *= (double d)
{

	for (int j = 0; j < sz; j++)
		 val[j] *= d;

	return *this;
}


DSDLIST DSDLIST::operator + (const DSDLIST &lst2) const
{ // Add the elements of two arrays to form a new array
  // The lengths of the arrays must be the same. If badly    ructed
  // arrays are used you will get rubbish

    // Preconditions
    DSDLIST res(UNDEFINED); // An undefined array

    if (sz != lst2.sz)
       return res;

    DSDLIST tmp(sz);

	for (int i = 0; i < sz; i++)
		tmp.val[i] = val[i] + lst2.val[i];

    return tmp;
}

DSDLIST DSDLIST::operator + (double d) const
{ // Add offset to each element of array
        DSDLIST res(sz);

        for (int i = 0; i < sz; i++)
                res[i] =  val[i] + d;

        return res;
}         
                 
DSDLIST DSDLIST::operator - (const DSDLIST& d2) const
{ // Subtract two arrays. This is NOT implemented by a combination of
  // unary minus and addition; thus, a - b = a + (-b). We could have used
  // the more straightforward and efficient approach a - b

	DSDLIST tmp = - d2;
	return DSDLIST ((*this) + tmp);
}

DSDLIST& DSDLIST::operator += (double d)
{
        for (int i = 0; i < sz; i++)
            val[i] += d;

        return *this;
}

DSDLIST& DSDLIST::operator /= (double d)
{
      // Precondition: d must be non-zero 
        if (d == 0.0)       // Unable to divide by zero
                return *this;

        for (int i = 0; i < sz; i++)
              val[i] /= d;

        return *this;
}               
     
          
DSDLIST operator * (const DSDLIST& darr, double d)
{
     int s = darr.sz;
     DSDLIST res(s);
     for (int i = 0; i < s; i++)
	   res.val[i] = darr.val[i] * d;

     return res;
}

DSDLIST operator * (double d, const DSDLIST& darr)
{ // Multiply a double by an array. No error checking is needed
  // because it is done in 'DSDLIST * d' operator stuff

	DSDLIST res(darr * d);
	return res;
}

DSDLIST operator - (double d, const DSDLIST& darr)
{ // Presubtraction of double d


     DSDLIST res(darr.sz);
     for (int i = 0; i < darr.sz; i++)
	   res.val[i] = d - darr.val[i];

     return res;
}

DSDLIST operator - (const DSDLIST& darr, double d)
{ // Postsubtraction of double d

     DSDLIST res(darr.sz);
     for (int i = 0; i < darr.sz; i++)
	   res.val[i] = darr.val[i] - d;

     return res;
}

DSDLIST DSDLIST::operator ^ (const DSDLIST& arr2) const
{ // Concatenate two DSDLIST's

	// Concatenation implies a new array with length equal to
	// the sum of the lengths of the separate arrays
	DSDLIST res(sz + arr2.sz);

	int offset = 0;
	for (offset = 0; offset < sz; offset++)
		res.val[offset] = val[offset];

	for (int j = 0; j < arr2.sz; j++)
		res.val[sz + j] = arr2.val[j];

	return res;

}

double& DSDLIST::operator [] (int j)
{
	if (check_range(j) == TRUE)
	   return val[j];
	else
	   return val[sz];	// We created one extra double just for this case!
}

double& DSDLIST::operator [] (int j) const
{
	if (check_range(j) == TRUE)
	   return val[j];
	else
	   return val[sz];	// We created one extra double just for this case!
}

// Modifier functions
void DSDLIST::scale(double d)
{ // Scale all elements by a factor

	for (int j = 0; j < sz; j++)
	    val[j] = d*val[j];
}

void DSDLIST::subtract(double d)
{ // Subtract a DSDLIST from double d (d - *this)

	for (int j = 0; j < sz; j++)
	    val[j] = d - val[j];
}

void swap(DSDLIST& dlist1, DSDLIST& dlist2)
{ // Swap two DSDLIST instances

	DSDLIST tmp = dlist1;
	dlist1 = dlist2;
	dlist2 = tmp;
}

DSDLIST DSDLIST::reverse() const
{ // Reverse indexing order (the last will be first)

	DSDLIST result(sz);

	for (int j = 0; j < sz; j++)
	    result.val[j] = val[sz - j -1];

	return result;
}

void DSDLIST::set_to_one()
{
	for (int j = 0; j < sz; j++)
	    val[j] = 1;
}

void DSDLIST::set_to_zero()
{
	for (int j = 0; j < sz; j++)
	    val[j] = 0;
}



// Comparing arrays with doubles (used in linear and nonlinear optimisation)
// In general, comparing an array with a double entails comparing all the former's elements
// Most operators are self-explanatory.
BOOLEAN DSDLIST::operator == (double d) const
{

	BOOLEAN result = TRUE;
	for (int j = 0; j < sz; j++)
	{
	     if (equal(val[j], d) == FALSE)
	     {
		result = FALSE;
		break;
	     }
	}

	return result;
}

BOOLEAN DSDLIST::operator != (double d) const
{
	if (*this == d)
	   return FALSE;

	return TRUE;
}

BOOLEAN DSDLIST::operator <= (double d) const
{


	BOOLEAN result = TRUE;
	for (int j = 0; j < sz; j++)
	{
	     if (val[j] >  d)
	     {
		result = FALSE;
		break;
	     }
	}

	return result;
}

BOOLEAN DSDLIST::operator >= (double d) const
{

	BOOLEAN result = TRUE;
	for (int j = 0; j < sz; j++)
	{
	     if (val[j]  < d)
	     {
		result = FALSE;
		break;
	     }
	}

	return result;
}


BOOLEAN DSDLIST::operator <  (double d) const
{
	if (*this >= d)
	   return FALSE;

	return TRUE;
}


BOOLEAN DSDLIST::operator > (double d) const
{
	if (*this <= d)
	   return FALSE;

	return TRUE;
}

BOOLEAN DSDLIST::non_negative() const
{
	if (*this >= 0.0)
	   return TRUE;

	return FALSE;
}

BOOLEAN DSDLIST::non_positive() const
{
	if (*this <= 0.0)
	   return TRUE;

	return FALSE;
}

BOOLEAN DSDLIST::positive() const
{
	if (*this > 0.0)
	   return TRUE;

	return FALSE;
}

BOOLEAN DSDLIST::negative() const
{
	if (*this < 0.0)
	   return TRUE;

	return FALSE;
}

ostream& operator << (ostream &s, const DSDLIST& arr2)
{
	s << "(";
	for (int i= 0; i < arr2.sz - 1; i++)
		s << arr2.val[i] << ", ";

	s << arr2.val[arr2.sz - 1] << ")\n";
	return s;
}
