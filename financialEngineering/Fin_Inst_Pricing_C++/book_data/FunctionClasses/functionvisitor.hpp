// FunctionVisitor.hpp
//
// Visitor classes for Functions
//
//////////////////// Visitor Classes /////////////////////////////////////////////////////////

#ifndef FunctionVisitor_HPP
#define FunctionVisitor_HPP


#include "detfunction.cpp"
#include "functionset.cpp"


template <class D, class R, class I> class FunctionVisitor
{
private:


public:
	// Constructors and destructor
	FunctionVisitor() {}
	FunctionVisitor(const FunctionVisitor<D,R,I>& drv) {}

	virtual ~FunctionVisitor() {} // Destructor

	// Operator overloading
	FunctionVisitor<D,R,I>& operator = (const FunctionVisitor<D,R,I>& source) {}

	virtual void visit(ScalarFunction<D,R,I>& v) = 0;
	virtual void visit(VectorFunction<D,R,I>& v ) = 0;
	virtual void visit(ScalarValuedFunction<D,R,I>& v) = 0;
	virtual void visit(VectorValuedFunction<D,R,I>& v) = 0;
//	virtual void visit(FunctionSet<D,R,I>& v) = 0;


};

template <class D, class R, class I> class PrintFunctionVisitor : public FunctionVisitor<D,R,I>
{
public:
	// Constructors and destructor
	PrintFunctionVisitor() {}
	PrintFunctionVisitor(const PrintFunctionVisitor<D,R,I>& drv) {}

	virtual ~PrintFunctionVisitor() {} // Destructor

	// Operator overloading
	PrintFunctionVisitor<D,R,I>& operator = (const PrintFunctionVisitor<D,R,I>& source) {}

	void visit(ScalarFunction<D,R,I>& v) { cout << "SF" << endl; }
	void visit(VectorFunction<D,R,I>& v ){ cout << "VF"; }
	void visit(ScalarValuedFunction<D,R,I>& v) { cout << "SVF"; };
	void visit(VectorValuedFunction<D,R,I>& v) { cout << "VVF"; };
//	void visit(FunctionSet<D,R,I>& v) { cout << "FunctionSet"; };

};
#endif

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
