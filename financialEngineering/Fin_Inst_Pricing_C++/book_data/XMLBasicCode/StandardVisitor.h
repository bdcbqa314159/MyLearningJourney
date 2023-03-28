// 26 September 2002 - MB - Initial code.

#ifndef StandardVisitor_h
#define StandardVisitor_h

//#include "..//DPS2//PropertySet.h"
#include <vector>
#include <string>
using namespace std;

// Property set visitor base class for standard types.
class StandardVisitor
{
public:
	// Property types.
	typedef PropertySet<string, StandardVisitor> TPropertySet;
	typedef vector<double> TDoubleVector;
	typedef vector<int> TIntVector;
	typedef vector<long> TLongVector;
	typedef vector<short> TShortVector;
	typedef vector<bool> TBoolVector;
	typedef vector<string> TStringVector;
	typedef vector<TPropertySet> TPropertySetVector;
	
	// Visit functions.
	template<class Value>
	void Visit( Property<string, Value, StandardVisitor> & prop ) 
	{
		string name = prop.GetKey();
		Value & value = prop.GetValueReference();
		Visit(name, value);
	}

	// Visit functions.
	virtual void Visit( string & key, double & d ) {}
	virtual void Visit( string & key, int & i ) {}
	virtual void Visit( string & key, long & l ) {}
	virtual void Visit( string & key, short & s ) {}
	virtual void Visit( string & key, bool & b ) {}
	virtual void Visit( string & key, string & value ) {}
	virtual void Visit( string & key, TPropertySet & set ) {}
	virtual void Visit( string & key, TDoubleVector & l ){};
	virtual void Visit( string & key, TIntVector & l ){};
	virtual void Visit( string & key, TLongVector & l ){};
	virtual void Visit( string & key, TShortVector & l ){};
	virtual void Visit( string & key, TBoolVector & l ){};
	virtual void Visit( string & key, TStringVector & l ){};
	virtual void Visit( string & key, TPropertySetVector & l ){};
	
};

#endif // StandardVisitor_h