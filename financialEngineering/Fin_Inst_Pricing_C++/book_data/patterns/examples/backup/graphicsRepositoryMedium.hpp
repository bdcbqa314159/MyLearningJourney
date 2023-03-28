// graphicsRepositoryMedium.hpp
//
// Class that allows us to display values of functions in some
// medium.
//
// This class uses a Visitor for the display functionality. The 
// results are displayed in some medium (that we implement as a 
// Strategy).
//
// (C) Datasim Education BV 2003

#ifndef GraphicsRepositoryMedium_hpp
#define GraphicsRepositoryMedium_hpp



#include "GraphicsRepositoryvisitor.hpp"


////////////////////////// Hardware Display Strategies //////////////////////////////////////////


class GraphicsMedium
{
private:

public:
	GraphicsMedium();

	virtual void display (GraphicsRepository& grObject) = 0;

};

class ExcelGraphicsMedium : public GraphicsMedium 
{
private:

public:
	ExcelGraphicsMedium();

	void display (GraphicsRepository& grObject);


};

class DebugGraphicsMedium : public GraphicsMedium 
{
private:

public:
	DebugGraphicsMedium();

	void display (GraphicsRepository& grObject);


};



#endif

