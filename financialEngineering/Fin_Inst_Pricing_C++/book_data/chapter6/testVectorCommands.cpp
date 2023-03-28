// testVectorCommands.cpp
//
// Testing the Vector 'command' functions
//
// Some 'command' type functions that are useful in some applications. Most functions
// are void and this promotes Efficiency. Usability is also enhanced. 
// 
/*
template <class V, class I> void scale(Vector<V,I>& v, const V& a); // v * a
template <class V, class I> void scale(const V& a, Vector<V,I>& v); // a * v

template <class V, class I> void add(Vector<V,I>& v, const V& a); // v + a
template <class V, class I> void add(const V& a, Vector<V,I>& v); // a + v

template <class V, class I> void 
			scaleAndOffset(Vector<V,I>& v, const V& a, const V& b); // (a * v) + b	

template <class V, class I> void subtract(Vector<V,I>& v, const V& a); // v - a
template <class V, class I> void subtract(const V& a, Vector<V,I>& v); // a - v

template <class V, class I> void divide(Vector<V,I>& v, const V& a); // v / a

template <class V, class I> void minus(Vector<V,I>& v); // -v (unary minus)

*/
// (C) Datasim Component Technology BV 2004

#include "vector.cpp"
#include "arraymechanisms.cpp"

int main()
{
	Vector<double, int> v(4, 1);	// Size 4, start index 1

	double a = 2.0;
	double b = 1.0;

	assign(v, a);
	print (v);

	scale (v, 2.0);
	scale (v, 0.5);
	cout << "Scale\n";
	print (v);

	cout << "Scale and Offset\n";
	scaleAndOffset(v, a, b);
	print (v);

	cout << "Subtract\n";
	subtract(v, b);
	print (v);

	cout << "Divide\n";
	divide (v, a);
	print (v);

	cout << "Minus\n";
	toggleSign(v);
	print (v);

	cout << "Subtract II\n";
	subtract(b, v);
	print (v);


	return 0;
}
