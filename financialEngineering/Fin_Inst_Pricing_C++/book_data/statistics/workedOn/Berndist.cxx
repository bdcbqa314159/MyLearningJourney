// berndist.cxx
//
//	1992 DD kick-off
//	1999-1-5 DD templated version
//	2000-6-24 DD final version 

// Copyright (c) Datasim Education BV 1992-2000

#include "berndist.hxx"

template <class T, class I> Bernoulli<T, I>::Bernoulli(const T& prob) : Binomial<T, I>(prob, 1)
{

}


