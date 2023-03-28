// arraymechanisms.cpp
//
// 2003-8-1 Initial code DD
// 2003-80-6 DD major code review and changes
// (C) Datasim Education BV 2003
//

#ifndef ArrayMechanisms_cpp
#define ArrayMechanisms_cpp

#include "arraymechanisms.hpp"
#include "numericmatrix.cpp"
#include <math.h>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////////////////////
// Sums and averages
template <class V, class I> V sum(const Vector<V,I>& x)
{ // Sum of elements     

		V ans = V(0.0);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += x[j];
		}

		return ans;
} 


template <class V, class I> V sumReciprocals(const Vector<V,I>& x) 
{  // Sum of reciprocals    

		// Precondition (PREC): x is (strictly) positive

		V ans = V(0.0);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += 1.0/x[j];
		}

		return ans;

} 


template <class V, class I> V sumAbsoluteValues(const Vector<V,I>& x) 
{  // Sum of reciprocals    

		V ans = V(0.0);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += fabs(x[j]);
		}

		return ans;

} 

// Mean value == sum() / N 
template <class V, class I> V mean(const Vector<V,I>& x)
{      

	return sum(x) / V(x.Size());

} 

// Weighted arithmetic mean
template <class V, class I> V weightedArithMean(const Vector<V,I>& x, const Vector<V,I>& w)
{      

		// PREC: x and w have the same size; start indexes not necessarily the same
		// PREC: sum(w) is not zero

		V ans = V(0.0);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += w[j] * x[j];
		}

		return ans / sum(w);
} 

// Geometric mean or geometric average 
template <class V, class I> V geometricMean(const Vector<V,I>& x)
{   
	
	V ans = x[x.MinIndex()];
		
	for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); j++)
	{
		ans *= x[j];
	}

	return pow(ans, 1.0 / x.Size() );
} 

// Harmonic mean
template <class V, class I> V harmonicMean(const Vector<V,I>& x)
{      

	// PREC: sumReciprocals(x) not zero

	return V(x.Size()) / sumReciprocals(x);
} 

// Root mean square (RMS)
template <class V, class I> V quadraticMean(const Vector<V,I>& x)
{     

	return sqrt( sumSquares(x) / V(x.Size()) );
} 

// Sum of squares
template <class V, class I> V sumSquares(const Vector<V,I>& x)
{     
		V ans = V(0.0);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += (x[j] * x[j]);
		}

		return ans;
}

/*
// A function returning all of the above values in one foul swoop (performance)
template <class V, class I> SimplePropertySet<string, double> allAverages(const Vector<V,I>& x)
{     

	SimplePropertySet<string, double> result;	// Empty list

	result.add(Property<string, V> ("SUM", sum(x)));
	result.add(Property<string, V> ("SUMREC", sumReciprocals(x)));
	result.add(Property<string, V> ("SUMABSVAL", sumAbsoluteValues(x)));
	result.add(Property<string, V> ("MEAN", mean(x)));
	result.add(Property<string, V> ("GMEAN", geometricMean(x)));
	result.add(Property<string, V> ("HMEAN", harmonicMean(x)));
	result.add(Property<string, V> ("RMS", quadraticMean(x)));
	result.add(Property<string, V> ("SUMSQ", sumSquares(x)));

	return result;


}
*/

/////////////////////////////////////////////////////////////////////////////

// Measures of Dispersion

template <class V, class I> V deviationFromMean(const Vector<V,I>& x)
{


		V m = mean(x);

		
		V ans = V(0.0);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += fabs(x[j] - m);
		}

		return ans / x.Size();

}


template <class V, class I> V standardDeviation(const Vector<V,I>& x)
{

		V m = mean(x);

		
		V ans = V(0.0);
		V tmp;

		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			tmp = x[j] - m;
			ans += tmp*tmp;
		}

		return sqrt(ans / V(x.Size()));


}


template <class V, class I> V variance(const Vector<V,I>& x)
{

	V s = standardDeviation(x);

	return s*s;

}


/*
// A function returning all of the above values in one foul swoop (performance)
template <class V, class I> SimplePropertySet<string, double> allDispersions(const Vector<V,I>& x)
{      

	SimplePropertySet<string, double> result;	// Empty list

	result.add(Property<string, V> ("MDEV", deviationFromMean(x)));
	result.add(Property<string, V> ("STD", standardDeviation()));
	result.add(Property<string, V> ("VARIANCE", variance(x)));

	return result;



}
*/

////////////////////////////////////////////////////////////////////////////////////////////////


// Moments, Skewness and Kurtosis

// The rth moment about the value 0.0
template <class V, class I> V rthMoment(const Vector<V,I>& x, const I& r)
{      

	return rthMoment(x, r, 0.0);

}

// The rth moment about the Mean m(r) as a special origin
template <class V, class I> V rthMomentMean(const Vector<V,I>& x, const I& r)
{      

		return rthMoment(x, r, mean(x));
}

// The rth moment about an origin A
template <class V, class I> V rthMoment(const Vector<V,I>& x, const I& r, const V& A)
{      


		V ans = V(0.0); V pr = V(r);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += pow(x[j] - A, pr);
		}

		return ans / x.Size();


}

template <class V, class I> V rthMoment(const Vector<V,I>& x, const Vector<V,I>& freq, const I& r, const V& A)
{


		V ans = 0.0;
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += freq[j] * pow(x[j] - A, V(r));
		}

		return ans / x.MaxIndex();

}

// Mode: either the middel element or the mean of the two middle elements 
template <class V, class I> V median(const Vector<V,I>& x)
{

	std::vector<V> v = createSTLvector(x);

//	:RandomAccessIterator it1 = v.begin();
//	RandomAccessIterator it2 = v.begin();


	std::stable_sort(v.begin(), v.end());

//	for (int i = 0; i < v.size(); i++)
//	{ 
//		cout << v[i] << ", ";
//	}

	// Now v is sorted

	int N = v.size();

//	V ans;

	if ((N/2)*2 == N)	// Even list
	{
		return (v[N/2] + v[(N/2) - 1]) * V(0.5);
	}
	else
	{
		return v[N/2];
	}

}

// The element in x that occurs with the greatest frequency
template <class V, class I> V mode(const Vector<V,I>& x)
{
	return 0.0; // TEMP
}


template <class V, class I> V skewness(const Vector<V,I>& x)
{

	return (mean(x) - mode(x)) / standardDeviation(x);

}

// Moment coefficient of kurtosis == m(4)/(m(2)*m(2))
template <class V, class I> V momentCoeffKurtosis(const Vector<V,I>& x)
{    


	return rthMomentMean(x, 4) / variance (x);

}


////////////////////////////////////////////////////////////////////////////////////////////////////

// Extremum operations on vectors

template <class V, class I> V maxValue(const Vector<V,I>& x)
{      

		return lInfinityNorm(x);
}

template <class V, class I> V minValue(const Vector<V,I>& x)
{      

		V ans = x[x.MinIndex()];
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); j++)
		{
			if (ans > x[j])
				ans = x[j];
		}

		return ans;
}

// Max and min of the absolute values
template <class V, class I> V maxAbsValue(const Vector<V,I>& x)
{      
		V ans = fabs(x[x.MinIndex()]);
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); j++)
		{
			if (ans < fabs(x[j]))
				ans = fabs(x[j]);
		}

		return ans;
}

template <class V, class I> V minAbsValue(const Vector<V,I>& x)
{     

		V ans = fabs(x[x.MinIndex()]);
		
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); j++)
		{
			if (ans > fabs(x[j]))
				ans = fabs(x[j]);
		}

		return ans;
}

// Index of max and min values 
template <class V, class I> I indexMaxValue(const Vector<V,I>& x)
{      	
		I index = x.MinIndex();
		V ans =	x[x.MinIndex()];
	
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); j++)
		{
			if (ans < x[j])
			{
				index = j;
				ans = x[j];
			}
		}

		return index;


}

template <class V, class I> V indexMinValue(const Vector<V,I>& x)
{     

		I index = x.MinIndex();
		V ans =	x[x.MinIndex()];
	
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); j++)
		{
			if (ans > x[j])
			{
				index = j;
				ans = x[j];
			}
		}

		return index;
}

template <class V, class I> I indexMaxAbsValue(const Vector<V,I>& x)
{     

		I index = x.MinIndex();
		V ans =	fabs(x[x.MinIndex()]);
	
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); j++)
		{
			if (ans < fabs(x[j]))
			{
				index = j;
				ans = fabs(x[j]);
			}
		}

		return index;

}


template <class V, class I> V indexMinAbsValue(const Vector<V,I>& x)
{   

		I index = x.MinIndex();
		V ans =	fabs(x[x.MinIndex()]);
	
		for (I j = x.MinIndex() + 1; j <= x.MaxIndex(); j++)
		{
			if (ans > fabs(x[j]))
			{
				index = j;
				ans = fabs(x[j]);
			}
		}

		return index;

}

// Vector-vector extremum (difference of two vectors)
template <class V, class I> V maxValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{    

	// PREC: A and B have same size (holds for all the following functions too)

	Vector<V, I> vecDiff = vectorA - vectorB;

	return maxValue(vecDiff);

}

template <class V, class I> V minValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{  

	Vector<V, I> vecDiff = vectorA - vectorB;

	return minValue(vecDiff);
}


template <class V, class I> V maxAbsValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{  

	Vector<V, I> vecDiff = vectorA - vectorB;

	return maxAbsValue(vecDiff);
}

template <class V, class I> V minAbsValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{     
	Vector<V, I> vecDiff = vectorA - vectorB;

	return minAbsValue(vecDiff);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////


// Vector and matrix norms

template <class V, class I> V innerProduct(const Vector<V,I>& x, const Vector<V,I>& y)
{      

		// PREC: x and y have same size
		V ans = V(0.0); V pr = V(r);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += x[j] * y[j];
		}

		return ans / vector.Size();

}

template <class V, class I> V l1Norm(const Vector<V,I>& x)
{    

	return sumAbsoluteValues(x);
}

template <class V, class I> V l2Norm(const Vector<V,I>& x)
{      

	return sqrt(sumSquares(x));
}	

template <class V, class I> V lpNorm(const Vector<V,I>& x, const I& p)
{      

		V ans = V(0.0); V myPower = V(p);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			ans += pow(x[j], myPower);
		}

		return pow(ans, V(1.0)/ myPower);


}		


template <class V, class I> V lInfinityNorm(const Vector<V,I>& x)
{     

	return maxAbsValue(x);

}

/*
template <class V, class I> SimplePropertySet<string, double> allNorms(const Vector<V,I>& x)
{

	SimplePropertySet<string, double> result;	// Empty list

	result.add(Property<string, V> ("l1", l1Norm(x)));
	result.add(Property<string, V> ("l2", l2Norm(x)));
	result.add(Property<string, V> ("linf", lInfinityNorm(x)));

	return result;

}
*/

/*
template <class V, class I> SimplePropertySet<string, double> allNorms(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{


	Vector<V,I> vecDiff = vectorA - vectorB;

	return allNorms(vecDiff);
}
*/



// Same vector morms as above except for the difference of two vectors
template <class V, class I> V l1Norm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{   

	Vector vecDiff = vectorA - vectorB;

	return l1Norm(vecDiff);

}

template <class V, class I> V l2Norm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{   

	Vector vecDiff = vectorA - vectorB;

	return l2Norm(vecDiff);
	

}

template <class V, class I> V lpNorm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB, const I& p)
{     

	Vector vecDiff = vectorA - vectorB;

	return lpNorm(vecDiff, p);
	
}	


template <class V, class I> V lInfinityNorm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB)
{   

	Vector vecDiff = vectorA - vectorB;

	return lInfinityNorm(vecDiff);
	

}


template <class V, class I> V L1Norm(const NumericMatrix<V,I>& matrix)
{ // Largest coulmn 

		V ans, rowsum;

		ans = fabs( matrix(matrix.MinRowIndex(), matrix.MinColIndex()) );

		// Get largest value of first column as 'seed'
		for (I k = matrix.MinRowIndex() + 1; k <= matrix.MaxRowIndex(); k++)
		{
			if ( ans < fabs( matrix(k, matrix.MinColIndex() ) ) )
				ans	 = fabs( matrix(k, matrix.MinColIndex() ) );
		}

		
		for (I j = matrix.MinColIndex() + 1; j <= matrix.MaxColIndex(); j++)
		{

			rowsum = V(0.0);	// Row sum init for current column
			for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
			{

				rowsum += fabs(matrix(i, j));
			}

			if (ans < rowsum)
				ans = rowsum;
		}

		return ans;
}

template <class V, class I> V FrobeniusNorm(const NumericMatrix<V,I>& matrix)
{      
		V ans = V(0.0);

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColIndex(); j<= matrix.MaxColIndex(); j++)
			{
				tmp = matrix(i, j);
				ans += tmp * tmp;
			}

		}

		return sqrt(ans);
} 

template <class V, class I> V LInfinity1Norm(const NumericMatrix<V,I>& matrix)
{ // Largest row

		V ans, colsum;

		ans = fabs(matrix(matrix(matrix.MinRowIndex(), matrix.MinColIndex()));

		// Get largest value of first row as 'seed'
		for (I k = matrix.MinColIndex() + 1; k <= matrix.MaxColIndex(); k++)
		{
			if (ans < fabs( matrix(matrix.MinRowIndex(), k)) ) )
				ans = fabs( matrix(matrix.MinRowIndex(), k)) );
		}


		for (I i = matrix.MinRowIndex() + 1; i <= matrix.MaxRowIndex(); i++)
		{

			colsum = V(0.0);	// Row sum init for current row
			for (I j = matrix.MinColIndex(); j <= matrix.MaxColIndex(); j++)
			{

				col += fabs(matrix(i, j));
			}

			if (ans < colsum)
				ans = colsum;
		}

		return ans;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

// Other results for vectors and matrces
template <class V, class I> V quadraticForm(const NumericMatrix<V,I>& matrix, const Vector<V,I>& x)
{    

		V ans = V(0.0);

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColIndex(); j<= matrix.MaxColIndex(); j++)
			{
				ans += matrix(i,j) * x[i] * x[j];
			}

		}

		return sqrt(ans);
}

template <class V, class I> V RayleighQuotient(const NumericMatrix<V,I>& A, const Vector<V,I>& x)
{    

	// PREC: Compatibiity, number of columns of A == number of rows of x
	// PREC: inner product does not evaluate to 0.0

	Vector y = A * x;

	return innerProduct(y, x) / innerProduct (x,x);

}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Functions for Operations Research

// Comparing vectors with each other

// Are all elements of a vector positive?
template <class V, class I> bool positive(const Vector<V,I>& x)
{      
		
		V zero = V(0.0);
		
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			if (x[j] <= zero)
				return false;
		}

		return true;

}

template <class V, class I> bool negative(const Vector<V,I>& x)
{    

	V zero = V(0.0);

	for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
	{
			if (x[j] >= zero)
				return false;
	}

	return true;
}


// Positive matrix?
template <class V, class I> bool positive(const NumericMatrix<V,I>& x)
{    

	for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
	{

			for (I j = matrix.MinColIndex(); j<= matrix.MaxColIndex(); j++)
			{
				if (matrix(i,j) < 0.0)
					return false;
			}

	}

	return true;

 }

// Is v1 < v2? etc. 
template <class V, class I> bool operator < (const Vector<V,I>& v1, const Vector<V,I>& v2)
{   


		// Iterate in the matrix; when the condition is NOT true 
		// (the inverse of the inequality) then exit and return false
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			if (v1[j] >= v2[j])
				return false;
		}

		return true;
}


template <class V, class I> bool operator <= (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

		// Iterate in the matrix; when the condition is NOT true 
		// (the inverse of the inequality) then exit and return false
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			if (v1[j] > v2[j])
				return false;
		}

		return true;

}


template <class V, class I> bool operator > (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

		// Iterate in the matrix; when the condition is NOT true
		// (the inverse of the inequality) then exit and return false
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			if (v1[j] <= v2[j])
				return false;
		}

		return true;
}


template <class V, class I> bool operator >= (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

		// Iterate in the matrix; when the condition is NOT true 
		// (the inverse of the inequality) then exit and return false
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			if (v1[j] < v2[j])
				return false;
		}

		return true;
}


template <class V, class I> bool operator == (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

		// Iterate in the matrix; when the condition is NOT true 
		// (the inverse of the inequality) then exit and return false
		for (I j = x.MinIndex(); j <= x.MaxIndex(); j++)
		{
			if (v1[j] != v2[j])
				return false;
		}

		return true;
}


template <class V, class I> bool operator != (const Vector<V,I>& v1, const Vector<V,I>& v2)
{  

	if (v1 == v2) 
		return false;

	return true;
}

template <class V, class I> bool operator < (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColIndex(); j<= matrix.MaxColIndex(); j++)
			{
				if (m1(i,j) >= m2(i,j))
					return false;
			}

		}


		return true;
}

template <class V, class I> bool operator <= (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColIndex(); j<= matrix.MaxColIndex(); j++)
			{
				if (m1(i,j) > m2(i,j))
					return false;
			}

		}


		return true;
}


template <class V, class I> bool operator > (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

	if (m2 < m1)
		return true;

	return false;
}


template <class V, class I> bool operator >= (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

		if (m2 <= m1)
			return true;

		return false;

}


template <class V, class I> bool operator == (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColIndex(); j<= matrix.MaxColIndex(); j++)
			{
				if (m1(i,j) != m2(i,j))
					return false;
			}

		}


		return true;
}


template <class V, class I> bool operator != (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

	if (m1 == m2)
		return false;

	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////


// Function Evaluations

/*
template <class V, class I> Vector<V, I> functionValues (V (*f)(const V& x), const Range<V>& range, const I& numSteps)
{ 
	
	Vector<V, I> myMesh = range.mesh(numSteps);

	Vector<V, I> result(myMesh.Size(), myMesh.MinIndex());
	

	for (I i = result.MInIndex(); i <= result.MaxIndex(); i++)
	{

		result[i] = (*f)(myMesh[i]);
	}

	return result;

}
*/



// Utility functions

template <class V> std::vector<V> createSTLvector (const Vector<V,int>& myVector)
{ // Create an STL vector from a general Vector

	std::vector<V> result(myVector.Size());
	for (int i = 0; i < result.size(); i++)
	{

		result[i] = myVector[i+myVector.MinIndex()];
		//cout << "* " << result[i] << "*";
	}

	return result;
}


template <class V> Vector<V, int> createDatasimVector (const std::vector<V>& mySTLvector)
{ // Create a general Vector from an STL vector


	Vector<V, int> result(mySTLvector.size());

	for (int i = 0, j = result.MinIndex(); i < mySTLvector.size(); i++, j++)
	{

		result[j] = mySTLvector[i];
	}

	return result;
}

template <class V, class I> Vector<V, I> cumulativeVector (const std::vector<V>& x)
{ // Cumulative vector c[j] = c[j-1] + x[j]

	Vector<V, int> result(x.Size(), x.MaxIndex());

	result[x.MinIndex()] = x[x.MinIndex()];
	for (int i = x.MinIndex() + 1; i <= x.MaxIndex(); i++)
	{

		result[i] = result[i-1] + x[i];
	}

	return result;
}

template <class V, class I> Vector<V, I> reverse (const Vector<V,I>& x)
{

	Vector<V, I> result(x);

	for (I k = result.MinIndex(); k <= result.MaxIndex(); k++)
	{

		result[k] = x[x.MaxIndex() - k + x.MinIndex()];
	}

	return result;

}



////////////////////// Print Functions /////////////////////////////////////////
template <class V, class I> void print(const Array<V,I>& v)
{

	cout << "\n\nMinIndex: " << v.MinIndex() << " , MaxIndex: " << v.MaxIndex() << endl;

	cout << "\nARR:[";
	for (I j = v.MinIndex(); j <= v.MaxIndex(); j++)
	{
		cout << v[j] << ",";
	
	}

	cout << "]";
}


template <class V, class I> void print(const Matrix<V,I>& m)
{

	cout << "\n\nMinRowIndex: " << m.MinRowIndex() << " , MaxRowIndex: " << m.MaxRowIndex() << endl;
	cout << "MinColumnIndex: " << m.MinColumnIndex() << " , MaxColumnIndex: " << m.MaxColumnIndex() << endl;

	cout << "\nMAT:[";
	for (I i = m.MinRowIndex(); i <= m.MaxRowIndex(); i++)
	{
		cout << "\nRow " << i << " (";
		for (I j = m.MinColumnIndex(); j <= m.MaxColumnIndex(); j++)
		{
			cout << m(i, j) << ",";
		}
		cout << ")";
	}

	cout << "]";
}

#endif