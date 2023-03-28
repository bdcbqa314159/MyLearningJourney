// tstXmlWriter.cpp
//
// Testing XML Writer 
//
// (C) Datasim Education BV 2003
//

#include "xmlwriter.cpp"


int main()
{

	XmlWriter<string, double> xmlW;



	xmlW.Save ("AA");

	return 0;
}
