

/************************************************************************
 *              Random.cpp- by R. Mirani - 1/5/2002                     *
 *                                                                      *
 *   Provides user with iNumber normally distributed random variables   *
 *                                                                      *
 ************************************************************************/ 

#ifndef RANDOM_CPP
#define RANDOM_CPP


#include "Random.hpp"
#include <stdlib.h>
#include <iostream.h>
#include <time.h>
 	
	// constructor
	Random::Random()
	{
//		  t_seed Seed;					// Seed for drand48()
		
//		  InitSeed(Seed);				// initialize seed with clock
	
	//	  RanResetSeed2(&Seed);	// set the Seed
	srand ((unsigned) time (NULL));	// Define seed for random number generator

	cout << "Constructor\n";

	}
	
	// destructor
	Random::~Random()
	{
	
	}
	
	// Fills Vector v with iNumber normally distributed numbers
	void Random::Normal (Vector<double,int> & v,
											 const int & iNumber,
											 const double & Mu,
											 const double & Var)
	{
		//cout << "Normal\n";
	
		int size = iNumber + (iNumber%2);		    // add 1 to iNumber if it is odd
	
		Vector<double, int> tmp(size, 1);		// temporary vector for storing result
		
		double Sd = sqrt(Var); 							    //standard deviation
		
		for( int i=1; i<=size; i+=2 )
		{
			double N1;
			double N2;
			
			PolarMarsaglia (N1,N2); 	// draw U1 and U2 with normal distribution
		
			tmp[i] = N1 * Sd + Mu;
			tmp[i+1] = N2 * Sd + Mu;
		}
	
	v = tmp;		

//	cout << "leaving Normal\n";

	return;
	}

	// Draws two normally distributed random numbers with Polar Marsaglia method
	void Random::PolarMarsaglia (double & N1, double & N2)
	{

		double W;
		double V1, V2;
		srand ((unsigned) time (NULL));	// Define seed for random number generator

		int j = 1;
		do
		{
		//	cout << "Polar Marsaglia\n";

		//	double U1 = drand48();	// Uniform (0,1) random variables
		//	double U2 = drand48();
			srand ((unsigned) time (NULL));	// Define seed for random number generator
	//srand (1);	// Define seed for random number generator
			Vector<double> tarr(10, 1);
	for (int i = 1; i <= 10; i++)
	{

	//	cout << double(rand()) / double(RAND_MAX) << ", ";
		tarr[i] = double(rand()) / double(RAND_MAX);
	}
//	cout << endl;

//			double U1 = double(rand())/double(RAND_MAX);
//			srand (U1);//Define seed for random number generator
			double U1 = double(tarr[1]);

			//double U2 = double(rand())/double(RAND_MAX);
			double U2 = double(tarr[2]);
	//srand ((unsigned) time (NULL));	// Define seed for random number generator

	//		cout <<  "uni run# " << j << ", "  << U1 << ", " << U2 << endl;

	//		int tt;
		//	cin >> tt;



			V1 = 2 * U1 - 1;				// Uniform (-1,1) random variables
			V2 = 2 * U2 - 1;
		
			W = V1*V1 + V2*V2;
		//	cout << "W " << W << endl;
			i++;
		}while( W>1 );
		
		double W_function = sqrt( -2 * log(W) / W );
		
		N1 = V1 * W_function;
		N2 = V2 * W_function;

		return;		
	}

	void Random::InitSeed (t_seed & Seed)
	{

		int i;			    		//iterator
//		t_seed SeedTemp;    //intermediate seed

		for (i =0; i<2; ++i)
		{//the seed generated has 32 bits. It is going to be used in a
 		 //48 bits random number generator. We need two seeds then per
 		 //process

 		 //initialise the seed with the clock
 	//	 RanSetSeed(1);
	
 		 //obtain the seed for each process
 	//	 RanGetSeed ( &SeedTemp );

 //		 Seed.data_i[i] = SeedTemp.data_i[0];
	
 		 //duration of sleep turned from 2 seconds to 4 milliseconds
 		 //sleep(2);

 		}

		return;
	}
	
#endif
