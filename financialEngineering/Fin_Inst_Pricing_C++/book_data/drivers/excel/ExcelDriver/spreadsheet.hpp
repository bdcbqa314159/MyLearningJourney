// spreadsheet.hpp
//
// Simple class for getting Vectors into Excel.
//
// (C) Datasim Education BV 2003

class SpreadSheet
public:

		string sheetName;
		string Ytext;
		string Xtext;
		string mainTitle;

void sendToExcel(const Vector<double, int>& vec)
{ // Draw one graph in an Excel sheet

	// inline
}


void sendToExcel(const list<Vector<double, int> >& vec)
{ // Draw multiple graphs in an Excel sheet

	// inline
}

void sendToExcel(const NumericMatrix<double, int> >& matrix, list<string>& captions)
{ // Print a matrix in Excel cell format. The captions are the names of the columns

	// inline
}
