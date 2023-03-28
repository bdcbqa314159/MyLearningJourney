// LatticeMechanisms.cpp
//
// Generic functions that have to do with lattice classes.
//
// Last modifiction dates:
//
// 2004-1-19 DD Kick-off code and it works
// 2004-1-20 DD Sensitivites, American style checks

// (C) Datasim Education BV 2004
//

#ifndef LatticeMechanisms_cpp
#define LatticeMechanisms_cpp

#include "latticemechanisms.hpp"


// We assume that the lattice object has been created and we
// now give values to the knot points. The lattice objects will
// be modified.

// Forward build up of the tree from the initial root point
template <class V, class I> void modify	(Lattice<V, I>& source,
						const V& rootValue, const V& up, const V& down)
{

	// This is for the binomial method only!!!

	I si = source.MinIndex();
	source[si][source[si].MinIndex()] = rootValue;

	// Loop from the min index to the end index
	for (I j = source.MinIndex() + 1; j <= source.MaxIndex(); j++)
	{

		for (I i = source[j].MinIndex(); i < source[j].MaxIndex(); i++)
		{
			source[j][i] = down * source[j-1][i];
			source[j][i+1] = up * source[j-1][i];

		}

	}

}

template <class V, class I> V traverse	(const Lattice<V, I>& source, const Vector<V,I>& RHS,
						const V& p, const V& discounting, ExerciseType type,Lattice<V, I>& treevalues)
{

	// Make an exact copy of source
	Lattice<V,I> copy(source);


	I ei = copy.MaxIndex();
	copy[ei] = RHS;

	// Loop from the max index to the start (min) index
	for (I j = copy.MaxIndex() - 1; j >= copy.MinIndex(); j--)
	{

		for (I i = copy[j].MinIndex(); i <= copy[j].MaxIndex(); i++)
		{
			
			copy[j][i] = discounting * (p * copy[j+1][i+1] + (1.0-p) * copy[j+1][i]);

		}

	}

	I si = copy.MinIndex();
	return copy[si][copy[si].MinIndex()];


}

template <class V, class I> Lattice<V, I> dividedDifference (const Lattice<V, I>& Y, const Lattice<V, I>& X)
{

		
	// Make an exact copy of source
	Lattice<V,I> copy(Y);


	for (I j = Y.MinIndex(); j <= Y.MaxIndex(); j++)
	{

		for (I i = Y[j].MinIndex(); i < Y[j].MaxIndex(); i++)
		{
			copy[j][i] = (Y[j][i+1] - Y[j][i]) / (X[j][i+1] - X[j][i]);

		}

	}


	return copy;
}


// Discrete payoff functions
template <class V, class I> Vector<V,I> CallPayOff(const V& K, const Vector<V,I>& StockArr)
{

		V tmp;

		Vector<V,I> result (StockArr.Size(), StockArr.MinIndex());

		for (I i = StockArr.MinIndex(); i <= StockArr.MaxIndex(); i++)
		{
			result[i] = 0.0;
			tmp = StockArr[i] - K;
			if (tmp > 0.0)
				result[i] = tmp;
		}

		return result;
}

template <class V, class I> Vector<V,I> PutPayOff(const V& K, const Vector<V,I>& StockArr)
{

		V tmp;

		Vector<V,I> result (StockArr.Size(), StockArr.MinIndex());

		for (I i = StockArr.MinIndex(); i <= StockArr.MaxIndex(); i++)
		{
			result[i] = 0.0;
			tmp = K - StockArr[i];
			if (tmp > 0.0)
				result[i] = tmp;
		}

		return result;
}


// Adjust a lattice for American options; we must tell the strike K and whether it is call or put
template <class V, class I> void modify	(Lattice<V, I>& underlying, Lattice<V, I>& optValues,
						const V& K, const V& prob, OptionType otype)
{

	// Adjust a lattice because we are working with American style
	// Could be a Call or a Put (Strategy)

	// This is for the binomial method only!!!

	// We assume that the European option values have already been calculated

	I si = source.MinIndex();
	source[si][source[si].MinIndex()] = rootValue;

	// Loop from the min index to the end index (optimise later)
	for (I j = underlying.MinIndex(); j <= underlying.MaxIndex(); j++)
	{

		for (I i = underlying[j].MinIndex(); i <= underlying[j].MaxIndex(); i++)
		{
			if (otype == CallOptionType)
			{

				optValues[j][i] = max(max (underlying[j][i] - K, 0.0), optValues[j][i]);
			}

			else // Put
			{

				optValues[j][i] = max(max (K - underlying[j][i], 0.0), optValues[j][i]);
			}
		}

	}

}




#endif
