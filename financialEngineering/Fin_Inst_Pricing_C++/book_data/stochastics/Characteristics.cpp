
/****************************************************************
 *                                                              *
 *           Characteristics.cpp -- by R. Mirani -- 1/5/2002             *
 *  Contains several options for the coefficients in the SDE's  *
 *                                                              *
 ****************************************************************/

#include "Characteristics.hpp"


double a1(double t)
{ return (A); }

double a1_(double t)
{ return (A*(1.5-exp(-t))); }

double a2(double t)
{ return (A); }

double a3(double t)
{ return (-A); }

double a3_(double t)
{ return (-A*(1.5-exp(-t))); }

double b1(double t)
{ return (B); }

double b1_(double t)
{ return (B*(1.5-exp(-t))); }

double b2(double t)
{ return (B); }

double b3(double t)
{ return (B); }

double b3_(double t)
{ return (B*(1.5-exp(-t))); }

double c1(double t)
{ return 0; }

double c1_(double t)
{ return 0; }

double c2(double t)
{ return 0; }

double c3(double t)
{ return (-C);}

double c3_(double t)
{ return (-C*(1.5-exp(-t)));}