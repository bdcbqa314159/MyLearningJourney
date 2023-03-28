// CnsDistFactory.cpp
//
// Base class for shape factories
//
// 6 november 1998	RD	Started
//	2003-9-12 DD modified for continuous distributions
//
// (C) Datasim Education BV 1998-2003

#include "CnsDistFactory.hpp"

CnsDistFactory::CnsDistFactory()
{ // Default constructor
}

CnsDistFactory::CnsDistFactory(const CnsDistFactory& source)
{ // Copy constructor
}

CnsDistFactory::~CnsDistFactory()
{ // Destructor
}

CnsDistFactory& CnsDistFactory::operator = (const CnsDistFactory& source)
{ // Assignment

	return *this;
}
