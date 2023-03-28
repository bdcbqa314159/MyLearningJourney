// BCImpl.hpp
//
// Classes that model boundary conditions
//
// (C) Datasim Education BV 2008
//

#include "Ode.hpp"

	class BCImpl
	{
	public:
		virtual void modify(Fdm& fdm) = 0;

	};

	class Dirichlet : public BCImpl
	{
	private:
		double a;
	public:
		Dirichlet(double alpha) { a = alpha; }
		void modify(Fdm& fdm)
		{
			fdm.A(fdm.A.MinRowIndex(), fdm.A.MinColumnIndex()) = 1.0;

		}

	};

	class Neumann : public BCImpl
	{
	private:
		double a;
	public:
		Neumann(double alpha) { a = alpha; }
		void modify(Fdm& fdm)
		{
			fdm.A(fdm.A.MaxRowIndex(), fdm.A.MaxColumnIndex()) = 1.0;
			fdm.A(fdm.A.MaxRowIndex(), fdm.A.MaxColumnIndex()-1) = -1.0;
		}

	};
