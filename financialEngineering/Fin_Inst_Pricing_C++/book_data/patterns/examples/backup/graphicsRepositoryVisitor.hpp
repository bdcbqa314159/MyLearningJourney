// graphicsRepositoryVistor.hpp
//
// Class that allows us to display values of functions in some
// medium.
//
// This class uses a Visitor for the display functionality. The 
// results are displayed in some medium (that we implement as a 
// Strategy).
//
// (C) Datasim Education BV 2003

#ifndef GraphicsRepositoryVisitor_hpp
#define GraphicsRepositoryVisitor_hpp



#include "GraphicsRepository.hpp"

class GraphicsMedium;


////////////////////////// Visitors //////////////////////////////////////////

class GraphicsRepositoryVisitor
{


protected:

	GraphicsMedium* gm;		// Where 'hardware' display takes place

public:
	GraphicsRepositoryVisitor(GraphicsMedium& myMedium); 


	virtual void visit(GraphicsRepository& grObject) = 0;

};

class DisplayRepositoryVisitor: public GraphicsRepositoryVisitor
{
private:




public:
	DisplayRepositoryVisitor(GraphicsMedium& myMedium);

	void visit(GraphicsRepository& grObject);

};




#endif

