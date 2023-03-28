// weightedgraph.hpp
//
// Class representing directed weighted graphs. There are parameters:
//
//	T == node set
//	I == used for indexing nodes
//	W == the weights betwen the nodes
//
// This is a fixed size graph and the number of elements (node) must
// be specified at initialisation time. It is not possible to add or
// delete ndoes at run-time.
//
// (C) Datasim Education BV 1992-2003

#ifndef WeightedGraph_HPP
#define WeightedGraph_HPP

#include "matrix.cpp"

template <class I, class T, class W> class WeightedGraph
{ // Weighted graph


private:

	Array<T,I> vc;	// The contents of the nodes an array
	Matrix<W,I> am;	// The adjacency matrix implemented as a matrix
	
	static W uw;

	void accessible(const I& di,Array<bool,I>& v) const;// Helper for accessible
	void dftraverse(const I& si,Array<bool,I>& v,void (*f)(const T& v)) const;// Helper for dftraverse

public:
	// Constructors & destructor
	WeightedGraph();// Graph with one node
	WeightedGraph(const Array<T,I>& array);// Create graph from an array of nodes
	WeightedGraph(const WeightedGraph<I,T,W>& graph);// Copy constructor
	virtual ~WeightedGraph();// Destructor
	

	// Selectors
//	const V& operator () (I row, I column) const;	// Get the element at position

	// Degree selectors
	size_t degree() const;// Get the degree of a graph
	size_t degree(const I& i) const;// Get the degree of node identified by i
	size_t degreein(const I& i) const;// Get the in number of incoming nodes at i
	size_t degreeout(const I& i) const;// Get the in number of outgoing nodes at i
	bool isolated (const I& i) const;// Isolated node? (no incoming/outgoing vertices)

	// Traversals and paths 
	// adjacebt() is for direted graphs only
	bool adjacent(const I& i1,const I& i2) const;// Are vertices at i1 and i2 directly adjacent

	bool accessible(const I& di,const I& si) const;// Is vertex identified by di reacheable from si
  	void dftraverse(const I& i,void (*f)(const T& v)) const;// Depth first traversal
	void bftraverse(const I& i,void (*f)(const T& v)) const;// Breadth first traversal

	// Vertex selectors
	T vertex(const I& i) const;	// Get the content of vertex identified by i

	// Modifiers
//	void operator () (const T& element, const I& row, const I& column);	

	// Vertex modifiers
	void vertex(const I& i,const T& v);// Set vertex identified with i to v

	// Path modifiers
	void path(const I& si,const I& di, const W& w);// Define a path of weight w
	void unpath(const I& si, const I& di);// Remove a path
	void clear();	// Clear all paths between nodes

	// Operator overloading

  	WeightedGraph<I,T,W>& operator = (const WeightedGraph<I,T,W>& graph);

	void debug_print();
};

#endif


