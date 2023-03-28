// arraymechanisms.hpp
// moments?
// another version, see merge file

///////////////////////////////////////////////////////////////////////////////////////////////
// Sums and averages
template <class V, class I> V sum(const Vector<V,I>& x); // Sum of elements
template <class V, class I> V sumReciprocals(const Vector<V,I>& x); // Sum of reciprocals


// Mean value == sum() / N 
template <class V, class I> V Mean(const Vector<V,I>& x); 

// Weighted arithmetic mean
template <class V, class I> V weightedArithMean(const Vector<V,I>& x, const Vector<V,I>& w); 

// Geometric mean or geometric average 
template <class V, class I> V geometricMean(const Vector<V,I>& x); 

// Harmonic mean
template <class V, class I> V harmonicMean(const Vector<V,I>& x); 

// Root mean square (RMS)
template <class V, class I> V RMS(const Vector<V,I>& x); 

// Sum of squares
template <class V, class I> V sumSquares(const Vector<V,I>& vector);
////////////////////////////////////////////////////////////////////////////////////////////////


// Measures of Dispersion

// Sum of absoute values of ABS(X - Mean(X))
template <class V, class I> V rthMomentMean(const Vector<V,I>& vector, const I& r);

template <class V, class I> V deviationFromMean(const Vector<V,I>& vector);

// Mean Deviation (MD)
template <class V, class I> V MD(const Vector<V,I>& vector);


////////////////////////////////////////////////////////////////////////////////////////////////


// Moments, Skewness and Kurtosis

// The rth moment
template <class V, class I> V rthMoment(const Vector<V,I>& vector, const I& r);

// The rth moment about the Mean m(r)
template <class V, class I> V rthMomentMean(const Vector<V,I>& vector, const I& r);

// The rth moment about an origin A
template <class V, class I> V rthMomentMean(const Vector<V,I>& vector, const I& r, const V& A);

// Moment coefficient of kurtosis == m(4)/(m(2)*m(2))
template <class V, class I> V momentCoeffKurtosis(const Vector<V,I>& vector);

///////////////////////////////////////////////////////////////////////////////////////////////////

// Functions for Operations Research

// Comparing vectors with each other

// Are all elements of a vector positive?
template <class V, class I> bool positive(const Vector<V,I>& vector);

// Positive matrix?
template <class V, class I> bool positive(const NumericMatrix<V,I>& vector);

// Is v1 < v2?
template <class V, class I> bool operator < (const Vector<V,I>& v1, const Vector<V,I>& v2);

// Is v1 <= v2?
template <class V, class I> bool operator <= (const Vector<V,I>& v1, const Vector<V,I>& v2);

// Is v1 == v2?
template <class V, class I> bool operator == (const Vector<V,I>& v1, const Vector<V,I>& v2);
