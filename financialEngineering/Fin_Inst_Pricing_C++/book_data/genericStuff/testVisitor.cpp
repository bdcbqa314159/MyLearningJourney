// testVisitor.cpp
//
// (C) Datasim Education BV 2004

#include "genericVisitor.hpp"


int main()
{
	MyInstrumentVisitor vis;

	Option opt;
	Instrument* i = &opt;

	i -> accept(vis);

	return 0;
}
