// dlist.hxx
//
// Class definition of Double precision LIST.
// This class represents an array of double precision numbers. In
// general all elements of the array need to be stored. There are
// however, cases in which many of the elements of the list are zero
// (the so-called sparse vectors and matrices), but DLIST should NOT be
// used for these cases.
// We adopt the following Programming by Contract rule: if the client tries
// to create a DLIST object with a negative number of elements, the number of
// elements will be assigned to 1. The same situation holds when we try to create
// an array but there is not enough memory; in other words, an array of length 1 is
// created.
//  
// The main responsibilities are;
//
//      1. It acts as a service class to other classes (e.g. polynomials, matrices)
//      2. Hides memory allocation from client classes
//      3. Hides indexing problems from other classes
//      4. It models 'static' arrays (it does not grow)
//	5. It has facilities for basic linear algebra (BLAS).
// 	6. DLIST objects can be used in optimisation problems.
//
// In short, client classes can perform their duties without being
// involved in low-level details.
//
// ** DSDLIST's server classes: None
//
// (C) Datasim BV 1991 - 1994.

#ifndef DSDLIST_HXX
#define DSDLIST_HXX

#include "constant.hxx"

class DSDLIST
{

private:

        double* val;                                                // Is the pointer to an array of doubles
        int sz;                                                     // Holds the size of an array of doubles

        void init();                                                // Initialise state to NULL and zero values
	void def(double val = 0.0);                                 // Assign all elements of array to value val
        void all_mem(int& j);                                       // Allocate a chunk of memory
        BOOLEAN check_range(int j) const;                           // Is the index valid?

public:
	// Constructors
        DSDLIST (int n = 1, double val = 0.0);                      // Create an array of given length a
        DSDLIST (const DSDLIST& dlist2);                            // Copy initializer
        DSDLIST (double d);                                         // Array of length 1 with first value = d
        DSDLIST (double d, const DSDLIST& darr);                    // Array which is a multiple of darr
        DSDLIST (double start, double offset, int n);               // Array of length n with values at a certain offset
        DSDLIST (double start, int n, double end);                  // Array of length n with values in range [start, end]
	DSDLIST (const DSDLIST& x, const DSDLIST& y, double alpha); // Convex combination of x and y
	// Destructor
        ~DSDLIST();                                                 // Deallocate memory

	// Accessing Functions
        int size() const;                                           // The size of the array

	// Operator Overloading
        DSDLIST& operator =  (const DSDLIST& d2);                   // Assignment operator
        DSDLIST& operator =  (double d);                            // Fill array with value double
        DSDLIST& operator += (double d);                            // Add d to every element in array
        DSDLIST& operator *= (double d);                            // Multiply current array by d
	DSDLIST& operator /= (double d);                            // Divide every element in array by d

        DSDLIST  operator -  ()                  const;             // Unary minus
        DSDLIST  operator +  (const DSDLIST& d2) const;             // Add two arrays
        DSDLIST  operator +  (double offset)     const;             // Add d2 to each element
        DSDLIST  operator -  (const DSDLIST& d2) const;             // Subtract two arrays
        
      //DSDLIST operator *= (double d);                             // Multiply by d every element in array

        friend DSDLIST operator *  (const DSDLIST& darr, double d); // Multiply each element of array by d
        friend DSDLIST operator *  (double d, const DSDLIST& darr); // Multiply each element of array by d
        friend DSDLIST operator - (double d, const DSDLIST& darr);  // Presubtraction of double d
	friend DSDLIST operator - (const DSDLIST& darr, double d);  // Postsubtraction of double d
        DSDLIST operator  ^  (const DSDLIST& d2) const;             // Concatenate two DSDLISTs
        double& operator [] (int);                                  // Indexing operator
        double& operator [] (int) const;                            // Indexing operator
        void    set_val(int j, double d);                           // Assignment of element j to value d

	// Iterator functions which give information on the elements of the vector
        friend DSDLIST abs(const DSDLIST& dlist);                   // The array with all positive values
        friend double  min(const DSDLIST& dlist);                   // Smallest element of array
        friend double  max(const DSDLIST& dlist);                   // Largest element of array
	friend double  avg(const DSDLIST& dlist);                   // Average value of array
	friend double  sum(const DSDLIST& dlist);                   // Sum of all elements of array
	friend double  product(const DSDLIST& dlist);               // Product of elements of array
	friend double  sqr(const DSDLIST& dlist);		    // Square of list
	DSDLIST hadamard(const DSDLIST& dlist2) const;              // Hadamard product of two vectors
        DSDLIST absolute() const;                                   // Array with all positive values
        DSDLIST percentage() const;                                 // Array of percentages
        DSDLIST scurve() const;                                     // Index has the sum of the values with a lower index

        int index_min() const;                                      // Index of array having minimum value
        int index_max() const;                                      // Index of array having maximum value
        int index_absmin() const;                                   // Index of array having absolute minimum value
        int index_absmax() const;                                   // Index of array having absolute maximum value
	friend int count(const DSDLIST& dlist);                     // The number of non-zero elements in the array

	// Modifier functions
	void    scale(double d);                                    // Scale all elements by a factor d
	void    subtract(double d);                                 // Subtract a DSDLIST from double d (d - *this)
	void    swap(DSDLIST& dlist1, DSDLIST& dlist2);             // Swap two DSDLIST instances
	DSDLIST reverse() const;                                    // Reverse indexing order (the last will be first)
	void    set_to_one();					    // Set all elements to one
	void    set_to_zero();					    // Set all elemets to zero

	// Basic vector algebra (BLAS)
	double inner_product(const DSDLIST& dlist2) const;          // Inner product of two dlists
	double inner_product(const DSDLIST& dlist2, const DSDLIST& dlist3) const;
		// Triple inner product
	double inf_norm(const DSDLIST& dlist) const;                // The L-infinity norm
	double inf_norm()                     const;                // The L-infinity norm
	double one_norm(const DSDLIST& dlist) const;                // The L-1 norm (sum of absolute values)
	double one_norm()                     const;                // The L-1 norm (sum of absolute values)
	double two_norm(const DSDLIST& dlist) const;                // The L-2 (Frobenius) norm
	double two_norm()                     const;                // The L-2 (Frobenius) norm
	double diff_product(int j)            const;                // Product of terms x[j] - x[k] with j != k

	// Statistical functions
	friend double mean(const DSDLIST& dlist);                   // Mean value
	friend double variance(const DSDLIST& dlist);               // Variance
	friend double std(const DSDLIST& dlist);                    // Standard deviation = sqrt(variance())

	// Comparing arrays with doubles (used in linear and nonlinear optimisation)
	// In general, comparing an array with a double entails comparing all the former's elements
	BOOLEAN operator == (double d) const;
	BOOLEAN operator != (double d) const;
	BOOLEAN operator <= (double d) const;
	BOOLEAN operator >= (double d) const;
	BOOLEAN operator <  (double d) const;
        BOOLEAN operator >  (double d) const;
	BOOLEAN non_negative() const;
	BOOLEAN non_positive() const;
	BOOLEAN positive() const;
	BOOLEAN negative() const;

	// Input/Output functions
        friend ostream &operator << (ostream &, const DSDLIST& dlist);  // Standard output
};

#endif   // DSDLIST_HXX

