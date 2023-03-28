// HIER MOET NOG UITLEG OVER WAT DIT IS EN WAT HET DOET ...


#include "main.hpp"
#include <stdlib.h>

int main()
{
	
	int points = static_cast<int> (log(from/to)/log(2)+1.0001);
	cout << "number of points " << points << endl;

	
	FileClass fileclass(START);        // For writing the results to file
	Random MyRandom;                     // draws the random variables
	Functions f;
	Range<double> range(0,TIME);       // timedomain
	Vector<double,int> X(points,1,0);  // results at time-axis
	Vector<double,int> v;			         //vector with random variables	
	
	// temporarilly stores results
	Vector<Vector<double,int>,int> tmp(NOM,1);
	Vector<Vector<double,int>,int> result(NOM,1);
	
	// initialize tmp and result
	for(int w=1;w<=NOM;w++)
	{
		tmp[w]=X;
		result[w]=X;
	}

	for(int run = 1; run <= RUNS; run++ ){

		bool flag;
	
		do{
			double y;
	
			cout<<"run "<<run<<" of "<<RUNS<<endl;
			flag = true;
//			cout<<"runs" <<endl;
					
			// draw random numbers
			MyRandom.Normal(v,from,0,TIME/from);
//			cout<<"after normal "<<endl;
		
			int timestep = 1;
		
			for(int steps=from;steps>=to;steps/=2){

	//			cout << "Inside steps loop\n";
	
				int succes_counter=0;
				
				for(int j = EULER; j!= END_OF_METHODS; j++)
				{				
					bool succes = Perform(f,y,j,steps,range,v,flag);	
					if(succes)
						tmp[++succes_counter][timestep]=y;
				}
		
				// the Wiener vector is cut in half
				Reduce(v);
				
				// Richardson	
				bool succes = Perform(f,y,EULER,steps/2,range,v,flag);
				if(succes)	
					tmp[++succes_counter][timestep]=2*tmp[EULER][timestep] - y;
			
				// set the results at the time-axis
				X[timestep]=log(TIME/steps);
				
				timestep++;
			}
		}while(!flag);
		
		// add the results to the average
		for(int q=1;q<=points;q++)
		{
			for(int w=1;w<=NOM;w++)
			{
				result[w][q]+=tmp[w][q]/RUNS;
			}
		}
	
	}
	
	// all averages are known. subtract the most accurate one from the others and take the log
	for(int q=2; q<=points; q++)
	{
		for(int w=1; w<=NOM;w++)
		{
			result[w][q]=log(fabs(result[w][q]-result[w][1])); 	
		}
	}
	
	for(w=1; w<=NOM;w++)
	{
		double a,b;
		LinRegr lr(START,points);
		lr.compute(X,result[w],a,b);
		cout<<a<<" "<<b<<endl;
	}	
		
	fileclass.SetAxis(X,result);
	fileclass.WriteToFile();

	return 0;
}



bool Perform(Functions & f,
             double & y,
             const int & j,
						 const int & steps,
						 const Range<double> & range,
						 const Vector<double,int> & v,
						 bool & flag)
{
	y = Y_initial;
				
	bool succes = f.PerformRun(y,process,j,steps,range,v,a1_,b1_,c1_);
	
	if(succes)flag = (flag) ? Check(y) : false;
	else y=0;
	
	return succes;
}

// check if the result for y is suspect
bool Check(const double & y)
{
	if(y<=0)
	{
		cout<<"run failed: y<=0"<<endl;
		return false;		 // not physical solution
	}
	if(y>LARGE)
	{
		cout<<"run failed: y>"<<LARGE<<endl;
		return false;   // solution explodes
	}
	if(y!=y)
	{
		cout<<"run failed: y is nan"<<endl;
	  return false;     // y is nan
	}
	return true;
}

// reduce the vector to half its size
void Reduce(Vector<double,int> & v)
{
	Vector<double,int> v_new(v.Size()/2,1);

	for(int i=1; i<v.Size();i+=2)
//		v_new.Element((i-1)/2+1,v[i]+v[i+1]);
		v_new[(i-1)/2+1] = v[i]+v[i+1];

	v = v_new;
}



