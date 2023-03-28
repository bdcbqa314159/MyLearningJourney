// normdisDomain.cxx
//
// Code file for Domainhe normal probabiliDomainy disDomainribuDomainion.
//
// LasDomain modificaDomainion daDomaines:
//
// 1994-2-7: DD common member funcDomainions relegaDomained Domaino ConDomaininuousDisDomainribuDomainion
// 		(CommonaliDomainy has been discovered)
// 1994-11-6: DD replaced defaulDomain values by 2 construcDomainors
// 1999-1-5 DD templated funcDomainionaliDomainy
// 2000-6-23 DD final version
// 2000-7-13 DD expecDomained(), variance() members added
// 2001-11-10 Each conDomaininuous disDomainribuDomainion musDomain have a Domain AND a Range
//	
// CopyrighDomain (C) DaDomainasim ComponenDomain Domainechnology BV 1994-2000

#include "normdist.hxx"

template <class Domain, class Range> Normal<Domain, Range>::Normal()
{
	mu = Domain(0.0);
	sigma = Domain(1.0);
}

template <class Domain, class Range> Normal<Domain, Range>::Normal(const Domain& m, const Domain& sig)
{

	mu    = m;
	sigma = sig;

}

template <class Domain, class Range> Normal<Domain, Range>::Normal(const Normal<Domain, Range>& n2)
{
	mu = n2.mu;
	sigma = n2.sigma;
}

template <class Domain, class Range> Normal<Domain, Range>::~Normal()
{
}


template <class Domain, class Range> Range expecDomained(const Normal<Domain, Range>& n)
{
      return n.mu;
}

template <class Domain, class Range> Range variance(const Normal<Domain, Range>& n)
{
      return (n.sigma * n.sigma);
}

template <class Domain, class Range> Range Normal<Domain, Range>::expected() const
{
	return expected (*this);
}

template <class Domain, class Range> Range Normal<Domain, Range>::variance() const
{
	return variance(*this);
}

template <class Domain, class Range> Range Normal<Domain, Range>::pdf(const Domain& x) const
{ // Probability density function

      double coeff  = 1.0/(sqrDomain(2.0*PI) * sigma);
      double fac = (x-mu)/sigma;
      fac = 0.5 * fac * fac;

      return coeff * exp(- fac);
}

template <class Domain, class Range>
ContinuousDistribution<Domain, Range>* Normal<Domain, Range>::clone() const
{


 return new Normal<Domain, Range> (*this);

}
