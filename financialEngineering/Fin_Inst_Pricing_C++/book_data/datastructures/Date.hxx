                    
        /*===============================================================
        * Prog. Name  : DDATE.HXX                                       *
        * Copyright   : Datasim b.v. 1990                               *
        * Author      : Eric Manshande & Henri Schenau  14-3-1990       *
        * Descr.      : This file contains the class definition for 	*
		*               class DDATE.									*
		* Classes used: DYNSTR									*
		===============================================================*/



#ifndef DDATE_HXX
#define DDATE_HXX

//#include "system.h"		// system dependent information
//#include "d_dyn_st.hxx"
#include "dynstr.hxx"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <iostream.h>
#include "constant.hxx"

#ifdef ULTRIX
	#include <sys/types.h>
	#include <sys/timeb.h>
#endif

#define OR	||
#define AND	&&
 
typedef	unsigned long	julTy;
static const julTy century = 1900;
 
enum DATE_type	{STD,		// d[d]-mon-yy[yy]
		 EUROPEAN,	// d[d]-m[m]-yy[yy]
		 ANSI,		// yy[yy]-m[m]-d[d]
		 AMERICAN	// m[m]-d[d]-yy[yy]
};
 
 
class DATE	{
 private:
	julTy Julian_days;		// number of Julian days
	static DATE_type dtype;	// type of DATE currently working with
	static char delim;		// delimiter used in output DATEs

	void init(julTy days, julTy months, julTy years); // general init function
	julTy j_days(julTy days, julTy months, julTy years); // calc #Julian days
		// test functions
	int year_test(int year);	// return year (999<year<=9999), or 0
	int mm_test(int month);		// return month (1<=month<=12), or 0
	int mon_test(char* month);	// test month-string, return monthnumber
	int day_test(int day, int month, int year);// test if day in month and year
 
 public:
		// Accessing functions
	DATE(void);			// default constructor = date today
	DATE(DATE&);			// copy in initialization
	DATE(julTy days);		// construct DATE from Julian days
	DATE(int days);		// 		''
	DATE(char* DATEstring);	// construct DATE from string
	DATE(DYNSTR dDATEstring);// construct DATE from a dynamic string
	DATE(float acad_date);		// from float (used in AutoCad)
	DATE(int day, int month, int year);	// Day, month, year
 		// set functions
	void set_DATE_type(DATE_type t);// set static var dtype
	void set_delim(char delimiter);	// set static var delim (which is the 
					// delimiter for outputting DATEs) to
					// 'delimiter'
 		// Return functions
	int ret_year(void) const;	// return year of this DATE
	int ret_month(void) const;	// return monthnumber (1..12) of this DATE
	int ret_day(void) const;	// return daynumber (1..31) of this DATE
	void jul_to_greg(julTy& d, julTy& m, julTy& y);
					// give Gregorian date 
		// Comparison functions
	BOOLEAN operator==(DATE DATE_2);	// compare DATEs, TRUE if same days
	BOOLEAN operator!=(DATE DATE_2);	// compare DATEs, TRUE if not the same day
	BOOLEAN operator>(DATE DATE_2);	// DATE is later than DATE_2
	BOOLEAN operator<(DATE DATE_2);	// DATE is earlier than DATE_2
	BOOLEAN operator>=(DATE DATE_2);	// DATE is later than DATE_2
	BOOLEAN operator<=(DATE DATE_2);	// DATE is earlier than DATE_2
		// Arithmetic functions
	DATE& operator=(const DATE& DATE_2);	// copy
	friend DATE operator+(DATE d1, DATE d2);// add two values
	DATE operator-(int days);	// subtract days from DATE
	DATE operator-(julTy days);	//        ''
	DATE operator++();		// add 1 day to DATE
	DATE operator--();		// subtract one day from DATE
	DATE operator+=(julTy days);	// add days to this DATE
	DATE operator+=(int days);	// add days to this DATE
	DATE operator-=(julTy days);	// subtract days from this DATE
	DATE operator-=(int days);	// subtract days from this DATE
	DATE add_months(long months);	// return this DATE + #months
	DATE add_years(long years);	// return this DATE + #years
	DATE sub_months(long months);	// return this DATE - #months
	DATE sub_years(long years);	// return this DATE - #years
	DATE add_period(julTy days, julTy months = 0, julTy years = 0);
					// return this DATE plus a period of time
	DATE sub_period(julTy days, julTy months = 0, julTy years = 0);
					// return this DATE minus a period of time
	long difference(DATE DATE_2);	// give difference in days between DATE's
	long operator - (DATE d2);
		// Conversion and output functions
	DYNSTR to_dstring(char* s = 0);	// convert this DATE to dynamic string
	char* to_string(char* s = 0);	// convert this DATE to C-string
	void print(void);	// print the DATE
	friend ostream& operator << (ostream& os, const DATE& dat);
};

#endif
