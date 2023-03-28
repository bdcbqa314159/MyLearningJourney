#include "FileClass.hpp"


FileClass::FileClass():leap(0){;}

FileClass::FileClass(const int & Start):leap(Start - 1){;}

FileClass::~FileClass(){;}

void FileClass::SetAxis(const Vector<double,int> & X,
                        const Vector<Vector<double,int>,int > & Y)
{
	X_Axis = X;
	Y_Axis = Y;
}
	
void FileClass::WriteToFile()
{
	outputfile = fopen("outputfile","w");
	for(int i = X_Axis.MinIndex()+leap; i <= X_Axis.MaxIndex(); i++)
	{
	//	fprintf(outputfile,"\n%f ",X_Axis.Element(i));
		fprintf(outputfile,"\n%f ",X_Axis[i]);

		for(int j = Y_Axis.MinIndex();
		    j <= Y_Axis.MaxIndex();
		    j++)
		{
			fprintf(outputfile,"%f ",Y_Axis[j][i]);
		}
	}
	fclose(outputfile);

}

