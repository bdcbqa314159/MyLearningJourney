// Vector.hpp
//
// Vector class is an array with mathematical functions.
//
// (C) Datasim Component Technology 1999

#ifndef Vector_hpp
#define Vector_hpp

#include "Array.cpp"


// Default structure is FullArray with default allocator. Default integral type is int.
template <class V, class I=int, class S=FullArray<V> >
class Vector: public Array<V, I, S>
{
private:
public:
	// Constructors & destructor
	Vector();									// Default constructor
	Vector(size_t size);						// Constructor with size. Start index=1.
	Vector(size_t size, I start);				// Constructor with size & start index
	Vector(size_t size, I start, const V& val);	// Constructor with size & start index + value
	Vector(const Vector<V, I, S>& source);		// Copy constructor
	Vector(const Array<V, I, S>& source);		// Copy with an array as argument
	virtual ~Vector();							// Destructor


	// Return the sum of the elements
	// Operators
	Vector<V, I, S>& operator = (const Vector<V, I, S>& source);

	Vector<V, I, S> operator - () const;		// Unary minus

	Vector<V, I, S> operator + (const V& v) const;	// Add v to every element
	Vector<V, I, S> operator - (const V& v) const;	// Subtract v from every element
	Vector<V, I, S> operator * (const V& v) const;	// Multiply every element by v
//	Vector<V, I, S> operator / (const V& v) const;	// Divide every element by v
	
	Vector<V, I, S> operator + (const Vector<V, I, S>& v) const;	// Add the elements
	Vector<V, I, S> operator - (const Vector<V, I, S>& v) const;	// Subtract the elements
//	Vector<V, I, S> operator * (const Vector<V, I, S>& v) const;	// Multiply the elements
//	Vector<V, I, S> operator / (const Vector<V, I, S>& v) const;	// Divide the elements

//	Vector<V, I, S>& operator += (const V& v);	// Add v to every element
//	Vector<V, I, S>& operator -= (const V& v);	// Subtract v from every element
//	Vector<V, I, S>& operator *= (const V& v);	// Multiply every element by v
//	Vector<V, I, S>& operator /= (const V& v);	// Divide every element by v

//	Vector<V, I, S>& operator += (const Vector<V, I, S>& v);// Add the elements
//	Vector<V, I, S>& operator -= (const Vector<V, I, S>& v);// Subtract the elements
//	Vector<V, I, S>& operator *= (const Vector<V, I, S>& v);// Multiply the elements
//	Vector<V, I, S>& operator /= (const Vector<V, I, S>& v);// Divide the elements
};


#endif	// Vector_hpp