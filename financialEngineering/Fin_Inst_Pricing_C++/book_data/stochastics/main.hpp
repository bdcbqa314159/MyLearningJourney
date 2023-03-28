
#include "Characteristics.hpp"
#include "Functions.hpp"
#include "Random.hpp"
#include "range.hpp"
#include "FileClass.hpp"
#include "LinRegr.hpp"
#include <iostream.h>


const int from = 384; // Number of normal random numbers generated
const int to = 12;
const PROCESSES process = SQUARE_ROOT;
const int NOM = PREDICTOR_CORRECTOR + 1;	// number of methods
const double TIME = 1;
const double Y_initial = 1;
const int RUNS = 2; // 1000;
const int START = 3;
const double LARGE = 10000;

// compute result for scheme j
bool Perform(Functions & f,
             double & y,
             const int & j,
						 const int & steps,
						 const Range<double> & range,
						 const Vector<double,int> & v,
						 bool & flag);

// check if value of y is suspect
bool Check(const double & y);

// reduce the Wiener vector to half its size
void Reduce(Vector<double,int> & v);
