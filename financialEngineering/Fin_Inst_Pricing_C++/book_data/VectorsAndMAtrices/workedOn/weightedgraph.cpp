// weightedgraph.cpp
//
// Weighted graph (directed/undirected)
//
// (C) Datasim Education BV 1992-2001
//
// Modification dates:
// 
// 15-5-1995	MW	Large parts copied of allready existing class graph
// 2001-4-15 DD New structure. Also got rid of that messing around 
// with long stuff.
// 2001-4-17 DD eliminated the indirect indexing array object. Now 
// the input index numbers corresponding directly to the indexs in 
// the node array.
// DD 2003-1-1 Clean up a bit
//

#include <queue>		// STL
#include <list>
#include "weightedgraph.hpp"

// Initialization of static object
template <class I, class T, class W> W WeightedGraph<I,T,W>::uw = W();

// Constructors & destructor

template <class I, class T, class W> WeightedGraph<I,T,W>::WeightedGraph()
{	// Graph of one node

	// Create a square matrix of size 1
	am = Matrix<W,I>(1,1);
	vc = Array<T,I>(1);
	clear();	
}

template <class I, class T, class W> WeightedGraph<I,T,W>::WeightedGraph(const Array<T,I>& array)						
{	// Graph of n nodes


	// Initialise the array. The values in the arrays can be modified later 
	// with the vertex() modifier function.
	vc = array;

	am = Matrix<W,I> (array.Size(), array.Size());	// Square matrix

	// Set all paths to undefined weight
	clear();	

}

template <class I, class T, class W> WeightedGraph<I,T,W>::WeightedGraph(const WeightedGraph<I,T,W>& graph)	
{	// Copy constructor

	am = graph.am;
	vc = graph.vc;
}

template <class I, class T, class W> WeightedGraph<I,T,W>::~WeightedGraph()
{	// Destructor

	// Delegated
}

// Selectors

template <class I, class T, class W> size_t WeightedGraph<I,T,W>::degree() const	
{	// Get the degree of a graph (number of nodes in graph)

	// Get horizontal or verical dimension of the 
	// adjacency matrix and return it.

	return am.Rows();
}

template <class I, class T, class W> size_t WeightedGraph<I,T,W>::degree(const I& i) const	
{	// Get the degree of node identified by i

	return degreein(i) + degreeout(i);
}

template <class I, class T, class W> size_t WeightedGraph<I,T,W>::degreein(const I& i) const
{	// Get the in number of incoming nodes at i


	// All elements on column i that do not have value undefined
	// weight are incomming edges from node i.
	size_t deg=0;
	for(I r=1; r <= am.rows();r++)
	{
		if(am(r,i) != uw)
		  deg++;
	}

	return deg;
}


template <class I, class T, class W> bool WeightedGraph<I,T,W>::isolated (const I& i) const
{	// Isolated node? (no incoming/outgoing vertices)

	if (degree(i) == I(0))
		return true;
	
	return false;
}

template <class I, class T, class W> size_t WeightedGraph<I,T,W>::degreeout(const I& i) const	
{	// Get the in number of outgoing nodes at i	

	// All elements on row i that do not have value undefined
	// weight are outgoing edges from node i.
	size_t deg=0;
	for(I c=1; c <= am.columns();c++)
	{
		if(am(i,c) != uw)
		  deg++;
	}

	return deg;
}


template <class I, class T, class W> bool WeightedGraph<I,T,W>::adjacent(const I& i1,const I& i2) const	
{	// Are vertices at i1 and i2 directly adjacent?


	// Vertex i1 is adjacent with i2 if there exists a path from i1 to i2
	// DD now DIRECTED sense

	if( am(i1,i2) != uw) 
	  return true;

	return false;
}

template <class I, class T, class W> void WeightedGraph<I,T,W>::accessible(const I& di,Array<bool,I>& v) const	
{	// Accesible helper function


	// The trick is to use the depth first algoritm to traverse the graph.
	// We keep an array in which every element represents a node, and its
	// value that knows whether it has been visited or not. When all paths have been
	// explored, and the destination in the array is true, then the node
	// was accessible.

	// Mark this vertex as visited
	v[di] = true;

	// For all vertices, if it is adjacent to the current vertex, 
	// and not visited before, visit it.
	for(I i=1; i <= degree(); i++)
	{
	   if( am(di,i) != uw && v[i] != true)
		 accessible(i,v);
	}
}



template <class I, class T, class W> bool WeightedGraph<I,T,W>::accessible(const I& di,const I& si) const	
{	// Is vertex identified by di reacheable from si

	// Note that we calculate the path internally with longs and not the 
	// abstract indexes. This will improve performance dramatically, since
	// we do not have to map every time from abstract to real indices.

	// Create array of size degree of graph and all values set to false
	// It will serve as a array of nodes visited.
	Array<bool,I> visited(degree(), 1);

	for (I i = visited.MinIndex(); i <= visited.MaxIndex(); i++)
	{
		visited[i] = false;
	}
	
	// Traverse the graph,
	
	accessible(si, visited);

	// If destination was visited return true else false.
	return visited[di];
}


template <class I, class T, class W> void WeightedGraph<I,T,W>::dftraverse(const I& si,Array<bool,I>& v,void (*f)(const T& v)) const
{	// Depth first traversal

	// The trick is to use the depth first algoritm to traverse the graph.
	// We keep an array in which every element represents a node, and its
	// value whether it has been visited or not. 
	// RECURSIVE CALLS.

	// Visit the current vertex and mark this vertex as visited 
	f( vc[si] );
	v[si] = true;
	

	// For all vertices, if it is adjacent to the current vertex, 
	// and not visited before, visit it. (recursively)


	// For all elements in that array
	for(I i = vc.MinIndex(); i <= vc.MaxIndex(); i++)
	{
	   if( adjacent(si, i) == true && v[i] != true)
		 dftraverse(i,v,f);
	}
}

template <class I, class T, class W> void WeightedGraph<I,T,W>::dftraverse(const I& i,void (*f)(const T& v)) const	
{	// Depth first traversal

	// Create array of size degree of graph and all values set to false.
	// It will serve as a array of nodes visited.
	Array<bool,I> visited(vc.Size(), 1);
	for (I ii = visited.MinIndex(); ii <= visited.MaxIndex(); ii++)
	{
		visited[ii] = false;
	}

	// Traverse the graph, from si, with the array of 
	// visited elements and client defined function f
	dftraverse(i,visited,f);
	
}


template <class I, class T, class W> void WeightedGraph<I,T,W>::bftraverse(const I& i,void (*f)(const T& v)) const	
{	// Breadth first traversal


	// The idea is to traverse the graph, starting at a specified vertex.
	// After all adjacent vertices have been visited, We visit all adjacent
	// vertices of the next vertex, until all vertices have been visited.

	// Create a visited array


	Array<bool, I> visited(vc.Size(),1);
	for (I ii = visited.MinIndex(); ii <= visited.MaxIndex(); ii++)
	{
		visited[ii] = false;
	}

	std::queue<I> que;

	// Visit vertex, add it to the already visited vertices, and enqueue it.
	f(vc[i] );
	visited[i] = true;		
	que.push(i);

	// While there is any queue object
	while(que.empty() == false)		
	{
	   // Get next vertex to investigate from the queue and calculate 
	   // calculate abd visit all vertices adjacent to this vertex
	   // I current=queue.dequeue();	
	
		I current = que.front();	// Least recently inserted (visit this)
		que.pop();

	   // For all adjacent vertices, if not visited before, visit and enqueue.
	   for(I v= vc.MinIndex(); v <= vc.MaxIndex(); v++)
	   {
		  if(adjacent(current,v) == true &&  visited[v] == false)
		  {
		    f( vc[v] );
			visited[v] = true;
			que.push(v);
		  }
	   }
	}	
}


template <class I, class T, class W> T WeightedGraph<I,T,W>::vertex(const I& i) const
{	// Get the contents of vertex identified by i

	return vc[i];
}

// Modifiers

template <class I, class T, class W> void WeightedGraph<I,T,W>::vertex(const I& i,const T& v)
{	// Set the vertex identified by i to v

	vc[i] = v;
}

template <class I, class T, class W> void WeightedGraph<I,T,W>::path(const I& si,const I& di, const W& w)	
{	// Define a path of weight w

	am(si,di) = w;
}

template <class I, class T, class W> void WeightedGraph<I,T,W>::unpath(const I& si, const I& di)	
{	// Remove a path

	
	am(si,di) = uw;
}

template <class I, class T, class W> void WeightedGraph<I,T,W>::clear()
{	// Clear all paths between nodes


	// Loop through all components of the matrix and
	// set them to the undefined weight.
	for(I r=1; r <= am.Rows(); r++)
	{
	  for(I c=1; c <= am.Columns(); c++)
	  {
	  	am(r,c) = uw;
	  }
	}
}


// Operator overloading

template <class I, class T, class W> WeightedGraph<I,T,W>& WeightedGraph<I,T,W>::operator = (const WeightedGraph<I,T,W>& graph)
{	// Assign a graph to myself

	am = graph.am;
	vc = graph.vc;

	return *this;
}

template <class I, class T, class W> void WeightedGraph<I,T,W>::debug_print()
{

	for(I r=1; r <= am.Rows(); r++)
	{
		cout<<r<<"\t";
		for(I c=1; c <= am.Columns(); c++)
		  cout<<am(r,c)<<" ";
			
		cout<<endl;
	}
}

