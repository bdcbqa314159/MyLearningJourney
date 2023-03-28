#include "Vector.cpp"

class FileClass{

public:

	// constructor
	FileClass();
	
	// constructor
	FileClass(const int & Start);
	
	// destructor
	~FileClass();
	
	// set the contents of the vectors
	void SetAxis(const Vector<double,int> & X,
	             const Vector<Vector<double,int>,int > & Y);
	
	// write values in vectors to file
	void WriteToFile();
	
private:
	FILE * outputfile;
	int leap;
	Vector<double,int> X_Axis;
	Vector<Vector<double,int>,int > Y_Axis;
	
};
