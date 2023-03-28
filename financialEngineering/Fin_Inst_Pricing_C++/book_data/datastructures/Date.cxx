
       /*****************************************************************
        * Prog. Name : DDATE.CXX                                        *
        * Copyright  : Datasim b.v. 1990                                *
        * Author     : Eric Manshande & Henri Schenau  14-3-1990        *
        * Descr.     : This file contains the class DATE.               *
	*****************************************************************/
 
#include "date.hxx"
 
//	the following initialization of the static class members is not
//	possible before version 2.0 of C++. Instead, they are implicitly
//	defined 0. For DATE::dtype this is ok but for DATE::delim it is
//	not, so be sure to set this to an appropriate value in the main
//	program using the function DATE::set_delim(char).
 
	char DATE::delim = '/';
	DATE_type DATE::dtype = EUROPEAN;
 
void DATE::init(julTy days, julTy months, julTy years)
/*
 *	general init procedure to initialize this date. It calculates
 *	the number of Julian days and sets the pivate member Julian_days
 *	to that value.
 */
{
	Julian_days = j_days(days, months, years);
}

int DATE::year_test(int year)
/*
 *	test the value of year. If the value is between 0 and 99,
 *	return the value + this century (defined in header file).
 *	if the value is between 1000 and 9999, just return the value.
 *	else return 0.
 */
{
        if (year < 0 OR year > 9999)
		return(0);
	else if (year < 100)
                return(century + year);
        else if (year >= 1000)
                return(year);
        else return(0);
}
 
 
int DATE::mm_test(int month)
/*
 *	Test the value of month. If the value is between 1 and 12
 *	return the value, else return 0.
 */
{
        return( (month < 1 OR month > 12) ? 0 : month);
}
 
 
int DATE::mon_test(char* month)
{
        static char* months[] = {"JAN", "FEB", "MAR", "APR",
                                 "MAY", "JUN", "JUL", "AUG",
                                 "SEP", "OCT", "NOV", "DEC",
 
                                 "JANUARY",  "FEBRUARY","MARCH",   "APRIL",
                                 "MAY",      "JUNE",    "JULY",    "AUGUST",
								 "SEPTEMBER","OCTOBER", "NOVEMBER","DECEMBER",
 
 
				 "JANUARI",  "FEBRUARI","MAART",    "APRIL",
				 "MEI",      "JUNI",    "JULI",    "AUGUSTUS",
				 "SEPTEMBER","OKTOBER", "NOVEMBER","DECEMBER",
 
                                 "stop"
                                };
	int i;
        for (i = 0; strcmp(month, months[i]) != 0 AND
                        strcmp(months[i], "stop") != 0; i++)
                ;
		return(strcmp(months[i], "stop") == 0 ? 0 : i % 12 + 1); //
                                        // return monthnumber
}
 
int DATE::day_test(int day, int month, int year)
/*
 *	Test if the given day (which is a month-day-number) is a valid
 *	day in the given month and year. It checks for leapyears, etc.
 *	If it is valid, return the given day, else return 0.
 */
{
        static int numdays[] =			// number of days in month
                { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (day < 1 OR month < 1 OR month > 12 OR year == 0)
		return(0);
	else if (month == 2)
                        if ((year % 4 != 0) OR (year % 100 == 0 AND year % 400 != 0))
                                return(day <= 28 ? day : 0);
                        else
                                return(day <= 29 ? day : 0);
	else
		return(day <= numdays[month - 1] ? day : 0);
}
 
 
DATE::DATE(DATE& DATE_2)
/*
 *	copy initializer.
 */
{
	Julian_days = DATE_2.Julian_days;	// same date
}
 
DATE& DATE::operator=(const DATE& DATE_2)
/*
 *	this function takes care of assigning date_2 to this DATE and
 *	returns this DATE for multiple assignement. If this DATE and
 *	DATE_2 are the same objects, just return this DATE.
 */
{
	if (this != &DATE_2)			// beware of d = d;
		Julian_days = DATE_2.Julian_days;

	return *this;				// for multiple assignment
}


DATE::DATE(void)
/*
 *	This is the default constructor. The DATE is initialized
 *	with the system date at the moment of creation. This function
 *	uses ansi-C structures and functions and should be machine 
 *	independent.
 */
{
        time_t local_time;              // type to hold time
        struct tm *t_ptr;               // struct to contain time, date etc
 
        local_time = time((long*) 0);        // get time (and date) from system
        t_ptr = localtime(&local_time); // convert to struct
        julTy yy_t = year_test(t_ptr->tm_year);	// test year, month and day
        julTy mm_t = mm_test(t_ptr->tm_mon + 1);
        julTy dd_t = day_test(t_ptr->tm_mday, mm_t, yy_t);
        init(dd_t, mm_t, yy_t);	// calculate Julian days
}

 
DATE::DATE(julTy days)
/*
 *	construct a DATE from a number of Julian days.
 */
{
	Julian_days = days;
}
 
 
DATE::DATE(int days)
/*
 *	construct a DATE from a number of Julian days.
 */
{
	Julian_days = days;
}
 
 
DATE::DATE(float acad_time)
/*
 *	construct a DATE from an AutoCAD date (time, a floating point).
 *	The Autocad date can have two formats: A Julian date format
 *	used for the DATE variable and the calender and clock format 
 *	used for CDATE. 
 *	Julian format:			<Julian date>.<fraction>
 *	Calender and clock format:	   <YYYYMMDD>.<HHMMSSmsec>
 */
{
        long help;                      // to store intermediate results
        int dd, mm, yyyy;               // days months and years
 
        if (acad_time < 19000000)       // Julian date format
                Julian_days = (julTy)(acad_time); // throw away the fraction
        else {				// calender and clock format
                help = (julTy)(acad_time);
                dd = help % 100;	// month-day
                help /= 100;
				mm = help % 100;	// month
                help /= 100;
                yyyy = help;		// year
                init(dd, mm, yyyy); // calculate #Julian days
        }
}
 
 
DATE::DATE(char* date_string)
/*
 *	construct a DATE from a standard-C++ character string.
 */
{
	DYNSTR DATE_string(date_string);	// construct dynamic string
	*this = DATE(DATE_string);		// call other constructor
}
	
 
DATE::DATE(DYNSTR DATE_string)
/*
 *	construct a DATE from a dynamic string. The format depends
 *	on the static variable dtype. When the given string does not
 *	match the format, a DATE with 0 Julian days will be returned.
 */
{
        static char separators[] = {'.', '/', ':', '\\', '-', '_'};
		static int len = sizeof(separators);
	char* delim = " ";			// space character
 
        for (int i = 0; i != len; i++) {        // replace all separators
						// with space
                char sep_str[2];                // make separator string
                sep_str[0] = separators[i];
                sep_str[1] = '\0';
                DYNSTR dsep(sep_str);
				for (int pos = DATE_string.strindex(dsep); pos != -1
		    AND *delim != separators[i] ; ) {
				DATE_string.strsub(pos, 1, delim); // replace
					pos = DATE_string.strindex(dsep);
				}
        }
 
		DATE_string = DATE_string.uppercase();// string to uppercase
		DATE_string = DATE_string.trim();     // rem. lead. and trail. blanks
		DATE_string = DATE_string.compress(); // rem. multiple tabs and spaces
 
        int dd_t = 0, mm_t = 0, yy_t = 0;
 
        switch (dtype) {
        case EUROPEAN: 			// d[d]-mm-yy[yy]
				DATE_string = DATE_string.stripint(dd_t, *delim); //get day
				DATE_string = DATE_string.stripint(mm_t, *delim); //get month
				yy_t = DATE_string.strintconv();		//get year
	
                yy_t = year_test(yy_t);                         // test year
                mm_t = mm_test(mm_t);                           // test month
                dd_t = day_test(dd_t, mm_t, yy_t);              // test day
                break;
        case AMERICAN:                       // m[m]-d[d]-yy[yy]
				DATE_string = DATE_string.stripint(mm_t, *delim); //get month
				DATE_string = DATE_string.stripint(dd_t, *delim); //get day
				yy_t = DATE_string.strintconv();		//get year
 
                yy_t = year_test(yy_t);                         // test year
                mm_t = mm_test(mm_t);                           // test month
				dd_t = day_test(dd_t, mm_t, yy_t);              // test day
                break;
        case ANSI:                       // yy[yy]-m[m]-d[d]
				DATE_string = DATE_string.stripint(yy_t, *delim); //get year
				DATE_string = DATE_string.stripint(mm_t, *delim); //get month
				dd_t = DATE_string.strintconv();		//get day
 
                yy_t = year_test(yy_t);                         // test year
                mm_t = mm_test(mm_t);                           // test month
                dd_t = day_test(dd_t, mm_t, yy_t);              // test day
                break;
        case STD:       ;               // no break, see default:
        default :                       // default = STD: d[d]-Mon-yy[yy]
			char* mon_t = 0;
				DATE_string = DATE_string.stripint(dd_t, *delim); // get day
				DATE_string = DATE_string.stripstr(mon_t,*delim); // get month
			yy_t = DATE_string.strintconv();
 
                yy_t = year_test(yy_t);                         // test year
                mm_t = mon_test(mon_t);                         // test month
                dd_t = day_test(dd_t, mm_t, yy_t);              // test day
 
                break;
        }
	init(dd_t, mm_t, yy_t);
}

 
DATE::DATE(int day, int month, int year)
{ // Day, month, year

	Julian_days = j_days(day, month, year);
}

julTy DATE::j_days(julTy day, julTy month, julTy year)
/*
 *	return the number of Julian days from the given Gregorian date
 *	( in the variables day, month and year). If a wrong date is given, 
 *	it will return 0.	 Algorithm 199 from Communications
 *	af the ACM Volume6, No.8, (Aug. 1963) p.144. Gregorian calender
 *	started September 14, 1752. The algorithm is only valid for
 *	dates from this calender, other dates may result in invalid Julian 
 *	days.
 */
{
	julTy c, ya;
 
        if (day == 0 OR month == 0 OR year == 0)	// wrong date.
                return(0);
        else {		// valid date, algorithm to convert to Julian days. 
		if (month > 2)
			month -= 3;
		else {
			month += 9;
			year--;
		}
		c = year / 100;
		ya = year - 100 * c;
		return(((146097 * c) >> 2) + ((1461 * ya) >> 2) +
			(153 * month + 2) / 5 + day + 1721119);
	}
}
	
 
void DATE::jul_to_greg(julTy& day, julTy& month, julTy& year)
/*
 *	get the Gregorian date (returned in the referenced variables
 *	day, month and year) from the number of Julian days (member
 *	Julian_days) from this date. Algorithm 199 from Communications
 *	af the ACM Volume6, No.8, (Aug. 1963) p.144. If the number of
 *	Julian days = 0, return January 1, 1900. Gregorian calender started
 *	September 14, 1752. 
 */
{
	if (Julian_days == 0) {			// return January 1, 1900
		day = 1; month = 1; year = 1900;
		return;
	}
	else {					// This is the algorithm.
		julTy j = Julian_days - 1721119l;
		year = (julTy)(((j << 2) - 1) / 146097l);
		j = (j << 2) - 1 - 146097l * year;
		day = (julTy)(j >> 2);
		j = ((day << 2) + 3) / 1461;
		day = (julTy)((day << 2) + 3 - 1461 * j);
		day = (day + 4) >> 2;
		month = (5 * day - 3) / 153;
		day = 5 * day - 3 - 153 * month;
		day = (day + 5) / 5;
		year = (julTy)(100 * year + j);
		if (month < 10)
			month += 3;
		else {
			month -=9;
			year++;
		}
	}
}
 
 
void DATE::set_DATE_type(DATE_type t)
/*
 *	Set the static vaiable (class-variable) dtype to t.
 *	dtype indicates the current DATE-format for in- and
 *	output of DATEs. For the values (and the corresponding
 *	formats) see the header file DATE.hxx (DATE_type is an enum).
 */
{
	dtype = t;
}


void DATE::set_delim(char d)
/*
 *	set the static variable (classvariable) delim to d.
 *	Before version 2.00 of C++ this function must be used as follows:
 *		DATE foo;		// construct a DATE
 *		foo.set_delim('/');	// set delimiter for all DATE objects to /
 *	after version 2.00 it can be used as follows:
 *		DATE::set_delim('/');	// set delimiter to / for all DATE objects
 */
{
	delim = d;
}


int DATE::ret_year(void) const
/*
 *	return the year of this DATE.
 */
{
	julTy d=0, m=0, y=0;
	jul_to_greg(d, m, y);
	return(y);
}


int DATE::ret_month(void) const
/*
 *	return the monthnumber of this date. It will be between 1 and 12.
 */
{
	julTy d=0, m=0, y=0;
	jul_to_greg(d, m, y);
	return(m);
}


int DATE::ret_day(void) const
/*
 *	return the daynumber of this date. It will be between 1 and 31.
 */
{
	julTy d=0, m=0, y=0;
	jul_to_greg(d, m, y);
	return(d);
}
 
 
BOOLEAN DATE::operator==(DATE DATE_2)
/*
 *	compare two DATEs. Return TRUE if they are on the same day,
 *	else return FALSE (so the objects need not be the same).
 */
{
	return(Julian_days == DATE_2.Julian_days ? TRUE : FALSE);
};
		
 
BOOLEAN DATE::operator!=(DATE DATE_2)
/*
 *	compare two DATEs. Return TRUE if they are not on the same day,
 *	else return FALSE.
 */
{
	return(Julian_days != DATE_2.Julian_days ? TRUE : FALSE);
}
 
BOOLEAN DATE::operator>(DATE DATE_2)
/*
 *	if this DATE is later than DATE_2, return TRUE else return FALSE.
 */
{
	return(Julian_days > DATE_2.Julian_days ? TRUE : FALSE);
}
 
BOOLEAN DATE::operator<(DATE DATE_2)
/*
 *	if this DATE is earlier than DATE_2, return TRUE else return FALSE.
 */
{
	return(Julian_days < DATE_2.Julian_days ? TRUE : FALSE);
}
 
 
BOOLEAN DATE::operator>=(DATE DATE_2)
/*
 *	if DATE_2 is earlier than this DATE, return TRUE else return FALSE.
 */
{
	return(Julian_days >= DATE_2.Julian_days ? TRUE : FALSE);
}
 
BOOLEAN DATE::operator<=(DATE DATE_2)
/*
 *	if DATE_2 is later than this DATE, return TRUE, else return FALSE
 */
{
	return(Julian_days <= DATE_2.Julian_days ? TRUE : FALSE);
}
 

DATE DATE::operator+=(julTy nr_days)
/*
 *	add number of days to this DATE and return it. This is changed!
 */
{
	Julian_days += nr_days;
	return(*this);
}
 
DATE DATE::operator+=(int nr_days)
/*
 *	add number of days to this DATE and return it. This is changed!
 */
{
	Julian_days += nr_days;
	return(*this);
}
 
DATE DATE::operator-=(julTy nr_days)
/*
 *	subtract number of days from this DATE and return it. This is changed!
 */
{
	Julian_days -= nr_days;
	return(*this);
}
 
DATE DATE::operator-=(int nr_days)
/*
 *	subtract number of days from this DATE and return it. This is changed!
 */
{
	Julian_days -= nr_days;
	return(*this);
}
 
 
DATE DATE::operator++()
/*
 *	add 1 day to this DATE and return it. This is changed!
 */
{
	Julian_days++;				// one day later
	return(*this);				// return day later
}
 
 
DATE DATE::operator--()
/*
 *	subtract one day from this DATE and return it. This is changed!
 */
{
	Julian_days--;
	return(*this);
}
 
 
DATE operator+(DATE d1, DATE d2)
/*
 *	add two values. The values can be DATEs or one of them can
 *	be a number. If one of them is a number, the number will be
 *	converted to a DATE (implicit type onversion via a constructor).
 *	This is a friend function so d1 can be a number or d2 can be a
 *	number. In this way it possible to state:
 *	DATE d = DATE("1-1-1977") + 5;	// implicit conversion of 5 to DATE
 *		as well as:
 *	DATE d = 5 + DATE("1-1-1977");	// implicit conversion of 5 to DATE
 */
{
	julTy tot_days = d1.Julian_days + d2.Julian_days;
	DATE d(tot_days);
	return(d);
}
 
DATE DATE::operator-(int nr_days)
/*
 *	return this DATE minus the number of days. This is not changed!
 */
{
	DATE d(Julian_days);
	d.Julian_days -= nr_days;
	return(d);
}
 
 
DATE DATE::operator-(julTy nr_days)		// subtr. nr_days from DATE
/*
 *	return this DATE minus the number of days. This is not changed!
 */
{
	DATE d(Julian_days);
	d.Julian_days -= nr_days;
	return(d);
}
 
 
DATE DATE::add_period(julTy days, julTy months, julTy years)
/*
 *	add a period of time to this (which itself will not be changed) DATE
 *	and return that DATE. The period of time can be any number of days,
 *	months and years. First the number of years is added (if specified)
 *	then the number of months (if specified) and finaly the number of 
 *	days. So:
 *	DATE d = DATE("28-2-1980").add_period(3, 13, 1);
 *	results in March 31, 1982.
 */
{
	julTy nday, nmonth, nyear;
		
	jul_to_greg(nday, nmonth, nyear); // calc Greg. cal. from This DATE
	nmonth += months;		// add months
	nyear += ((nmonth - 1) / 12);	// how many years from months ?
	nmonth = (nmonth - 1) % 12 + 1;	// remaining months (1..12)
	nyear += years;			// add years
	while (day_test(nday, nmonth, nyear) == 0) // day still valid in month?
		nday--;			// no, subtract one monthday	
 
	julTy total_days = days + j_days(nday, nmonth, nyear); // total Julian days
	DATE d(total_days);		// construct new DATE
	return(d);			// return new DATE
}
 
 
DATE DATE::sub_period(julTy days, julTy months, julTy years)
/*
 *	subtract a period of time from this (which will not be changed) DATE
 *	and return that DATE. The period of time can be any number of days,
 *	months and years. First the number of years is subtracted (if speci-
 *	fied) then the number of months (if specified) and finaly the number of
 *	days. So:
 *	DATE d = DATE("1-3-1980").sub_period(3, 13, 1);
 *	results in January 29, 1978.
 */
{
	julTy nday, nmonth, nyear;
 
	jul_to_greg(nday, nmonth, nyear); // calc Greg cal. from this DATE
	nyear -= (months / 12);		// how many years in months ?
	months %= 12;			// remaining months;
	if (months >= nmonth) {		// more than months in this DATE
		nyear--;		// one year earlier
		nmonth = 12 + nmonth - months;	// remaining months
	}
	else nmonth -= months;
	nyear -= years;
	while (day_test(nday, nmonth, nyear) == 0) // day still valid in month?
		nday--;			// no, subtract one monthday	
 
	julTy total_days = j_days(nday, nmonth, nyear) - days;
	DATE d(total_days);
	return(d);
}
	
 
DATE DATE::add_months(long months)
/*
 *	this function will return a DATE which is a number of months later
 *	than this date. If 'months' is negative, the returned DATE will be
 *	earlier than this DATE. This DATE itself wil not be changed.
 */
{
	if (months > 0)			// positive number of months ?
		return( this->add_period(0, months, 0) ); // add months
	else				// negative number of months
		return( this->sub_period(0, months * -1, 0) ); // subtract
}
 
 
DATE DATE::add_years(long years)
/*
 *	this function will return a DATE which is a number of years later
 *	than this date. If 'years' is negative, the returned DATE will be
 *	earlier than this DATE. This DATE itself wil not be changed.
 */
{
	if (years > 0)			// positive number of years ?
		return( this->add_period(0, 0, years) ); // add years
	else				// negative number of years
		return( this->sub_period(0, 0, years * -1) ); // subtract
}
 
 
DATE DATE::sub_months(long months)
/*
 *	this function will return a DATE which is a number of months earlier
 *	than this date. If 'months' is negative, the returned DATE will be
 *	later than this DATE. This DATE itself wil not be changed.
 */
{
	if (months > 0)			// positive number of months ?
		return( this->sub_period(0, months, 0) ); // subtract months
	else				// negative number of months
		return( this->add_period(0, months * -1, 0) ); // add
}
 
 
DATE DATE::sub_years(long years)
/*
 *	this function will return a DATE which is a number of years earlier
 *	than this date. If 'years' is negative, the returned DATE will be
 *	later than this DATE. This DATE itself wil not be changed.
 */
{
	if (years > 0)			// positive number of years ?
		return( this->sub_period(0, 0, years) ); // subtract years
	else				// negative number of years
		return( this->add_period(0, 0, years * -1) ); // add
}
 
void DATE::print(void)
{
	static char* monthname[] = {
		"January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December"
	};
	julTy day=0, month=0, year=0;
	jul_to_greg(day, month, year);
	switch (dtype) {
	case EUROPEAN: 		// d[d]-mm-yyyy
		printf("%lu%c%lu%c%lu", day, delim, month, delim, year);
		break;
	case ANSI:		// yyyy-mm-d[d]
		printf("%lu%c%lu%c%lu", year, delim, month, delim, day);
		break;
	case AMERICAN:		// mm-d[d]-yyyy
		printf("%lu%c%lu%c%lu", month, delim, day, delim, year);
		break;
	case STD:	;
	default:
		printf("%lu%c%s%c%lu", day, delim, monthname[month - 1],
				delim, year);
		break;
	}
}

long DATE::difference(DATE DATE_2)
/*
 *	returns the difference in days (can be negative) between
 *	this DATE and DATE_2.
 */
{
	long dif;

	if (Julian_days >= DATE_2.Julian_days)		// dif is positive
		dif = Julian_days - DATE_2.Julian_days;	// calculate it
	else						// dif is negative
			// first calc positive difference (type = julTy).
			// then convert to long and make it negative.
		dif = (DATE_2.Julian_days - Julian_days) * -1;
	return(dif);				// return signed difference
}

long DATE::operator - (DATE d)
{


	return difference(d);
}

char* DATE::to_string(char* s)
/*
 *	convert the DATE to a string and return it. If s is 0 (NULL-pointer)
 *	the format depends on the static variable dtype. If s is not 0 it
 *	contains the format-string for the output-string. The format-string
 *	can contain the following elements:
 *	%D	insert day (1..31) in 1 digit if possible, otherwise 2 digits
 *	%DD	insert day (1..31) in 2 digits, first digit may be 0
 *	%M	insert month (1..12) in 1 digit if possible, otherwise 2
 *	%MM	insert month (1..12) in 2 digits, first digit may be 0
 *	%YY	insert yearnumber in 2 digits (year in century)
 *	%YYYY	insert full yearnumber in 4 digits
 *	any other character will be copied to the output string.
 *	for example: 
 * 		date d("31-1-1977");
 *		char* str = d.to_string("[%D]-[%MM]-[%YY]");
 *	will result str to be:
 *		"[31]-[01]-[77]"
 */
{
	static char* monthname[] = {
		"January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December"
	};
	julTy day=0, month =0, year=0;
	jul_to_greg(day, month, year);
	if (s == 0) {
		char *str = new char[20];
		switch (dtype) {
		case EUROPEAN: 		// dd-mm-yy or dd-mm-yyyy if not in this century
			if (year/100 == century/100)
				sprintf(str, "%02lu%c%02lu%c%02lu", day, delim, month, delim, year%100);
			else 	sprintf(str, "%02lu%c%02lu%c%02lu", day, delim, month, delim, year);
			break;
		case ANSI:		// yy-mm-dd or yyyy-mm-dd if not in this century
			if (year/100 == century/100)
				sprintf(str, "%02lu%c%02lu%c%02lu", year%100, delim, month, delim, day);
			else	sprintf(str, "%02lu%c%02lu%c%02lu", year, delim, month, delim, day);
			break;
		case AMERICAN:		// mm-dd-yy or mm-dd-yyyy if not in this century
			if (year/100 == century/100)
				sprintf(str, "%02lu%c%02lu%c%02lu", month, delim, day, delim, year%100);
			else	sprintf(str, "%02lu%c%02lu%c%02lu", month, delim, day, delim, year);
			break;
		case STD:	;
		default:		// dd-mon-yy or dd-mon-yyyy (not in this cent.)
			if (year/100 == century/100)
				sprintf(str, "%02lu%c%s%c%02lu", day, delim, monthname[month - 1],
					delim, year%100);
			else	sprintf(str, "%02lu%c%s%c%02lu", day, delim, monthname[month - 1],
					delim, year);
			break;
		}
		return(str);
	}
	else {					// a format has been given
		char* str = new char[80];	// space for outstring
		int count = 0;			// counter for format string
		int outcnt = 0;			// counter for output string
		while (s[count] != '\0' AND outcnt < 70) { // end of input or output
			if (s[count] == '%') {		// check char
				count++;		// move one char
				switch (s[count++]) {	// scan date expression
				case 'D': 		// D or DD
				   if (s[count] == 'D') { // 2 digits for day
					count++;
					sprintf(str + outcnt, "%02lu", day);
					outcnt = strlen(str);
				   }
				   else {		// 1 digit if possible
					sprintf(str + outcnt, "%lu", day);
					outcnt = strlen(str);
				   }
				   break;
				case 'M':		// M or MM
				   if (s[count] == 'M') { // 2 digits for month
					count++;
					sprintf(str + outcnt, "%02lu", month);
					outcnt = strlen(str);
				   }
				   else	{		// 1 digit if possible
					sprintf(str + outcnt, "%lu", month);
					outcnt = strlen(str);
				   }
				   break;
				case 'Y':		// YY or YYYY
				   if (s[count] != 'Y') // at least 2*Y
					break;
				   else {		// 2nd Y
					count++;	// move one char
					if (s[count] == 'Y' AND	// 3rd Y
					s[count + 1] == 'Y') {	// 4th Y
						count += 2;	// move past Ys
						sprintf(str + outcnt, "%04lu", year);
						outcnt = strlen(str);
					}
					else {		// 2 or 3 Ys
						sprintf(str + outcnt, "%02lu", year%100);
						outcnt = strlen(str);
					}
				   }
				   break;
				default: 		// % with another char
				   count++;		// just skip %
				   break;
				}			// end switch
			}				// end if 
			else {				// no %, copy char to output
				str[outcnt] = s[count];	// and move pointers
				count++;		// move inp. pointer
				outcnt++;		// move output pointer
			}
		}
		str[outcnt] = '\0';			// string terminator
		return(str);				// retun outpustring
	}
}
 
 
DYNSTR DATE::to_dstring(char* s)
/*
 *	convert the DATE to a dynamic string and return it.
 *	The format depends on the static variable dtype (s==0) or on s.
 *	for an explanation of the format-string s see function:
 *	char* DATE::to_string(char* s)
 */
{
	DYNSTR d;
	d = DYNSTR( this->to_string(s) );	// call char* DATE::to_string()
	return(d);				// and convert to DYNSTR
}


ostream& operator << (ostream& os, const DATE& dat)
{

	os << dat.ret_day() << "/" << dat.ret_month() << "/" << dat.ret_year();
	return os;
}