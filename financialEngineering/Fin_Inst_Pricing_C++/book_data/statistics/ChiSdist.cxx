// chisdist.cxx
//
// Last modification dates:
//
// 1994-2-7: DD Commonality relegated to ContinuousDistribution
// 1999-1-5: DD templated functionality
// 2000-6-23 DD finsal version
//
// Copyright (C) Datasim Education BV 1994-2000

#include "chisdist.hxx"


template <class T> ChiSquare<T>::ChiSquare(int degfree): Gamma(0.5, degfree * 0.5)
{
  
}

