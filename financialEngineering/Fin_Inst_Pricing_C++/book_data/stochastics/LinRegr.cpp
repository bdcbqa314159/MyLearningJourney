#include "LinRegr.hpp"

LinRegr::LinRegr(const int & start,	
                 const int & stop):I_start(start),
	                                 I_stop(stop),
	                                 I_size(I_stop - I_start + 1){;}
	
LinRegr::~LinRegr(){;}	
	
void LinRegr::compute(const Vector<double,int> & X,
                      const Vector<double,int> & Y,
                      double & a,
                      double & b)
{
	// average values for X and Y
	double x=0,y=0;
	
	// determine average value for x and y	
		for(int i=I_start;i<=I_stop;i++)
	{
		x+=X[i];
		y+=Y[i];
	}
	x /= I_size;
	y /= I_size;

	double x_diff,y_diff;
	double sum_x2=0,sum_xy=0;
			
	for(i=I_start;i<=I_stop;i++)
	{
		x_diff = X[i] - x;	
		y_diff = Y[i] - y;
		
		sum_x2 += x_diff*x_diff;
		sum_xy += x_diff*y_diff;
	}
		
  b = sum_xy/sum_x2;
	a = y - b*x;
		
	return;
}

	



