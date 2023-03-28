#include "Vector.hpp"

class LinRegr{

public:

	LinRegr(const int & start,const int & stop);	// constructor
	
	~LinRegr();	                                  // destructor
	
	void compute(const Vector<double,int> & X,
	             const Vector<double,int> & Y,
	             double & a,
	             double & b);

	

private:
	const int I_start;
	const int I_stop;	
	const int I_size;
};