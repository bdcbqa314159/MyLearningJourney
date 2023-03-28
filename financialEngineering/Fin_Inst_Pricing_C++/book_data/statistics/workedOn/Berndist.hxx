// berndist.hxx
//
// The Bernoulli distribution.
// Used when the sample space consists of 2 possibilities, each with a given
// probability of occurrence.
// Answers such questions as : Does an event occur, e.g. does a car arrive
// in the next second or will a machine break down today? Another case is that 
// of defective or non-defective items coming off a production line.
//
// Copyright (C) Datasim Education BV 1994-2000

#ifndef BERNDIST_HXX
#define BERNDIST_HXX

#include "binodist.hxx"

template <class T, class I> class Bernoulli : public Binomial<T, I>
{

public :
      Bernoulli(const T& prob);
};

#endif
