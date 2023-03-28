// geomdist.cxx
//
// The geometric probability distribution.
//
// Last modification dates:
//
// 1994-2-8 DD Member fucntions documented
// 1999-1-5 DD templated functionality
//	2000-6-24 DD final version 
//
// Copyright (C) Datasim Education BV 1994-2000

#include "geomdist.hxx"

template <class T, class I> Geometric<T, I>::Geometric(const T& prob) : Pascal<T, I>(prob, 1)
{
}

