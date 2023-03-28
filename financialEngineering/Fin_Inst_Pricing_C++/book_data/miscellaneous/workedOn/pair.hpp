// pair.hpp
//
// (C) Datasim Component Technology 2000 BV
//

#ifndef pair_HPP
#define pair_HPP

template <class F, class S> class pair
{

public:
	
		F first;
		S second;

public:
	pair() { f = F(); s = S();}
	pair(const F& First, const S& Second) { first = First; second = Second;}
};

#endif