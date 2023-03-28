       /*****************************************************************
        * Prog. Name : DTIME.HXX                                        *
        * Copyright  : Datasim b.v. 1990                                *
        * Author     : Eric Manshande & Henri Schenau  19-3-1990        *
        * Descr.     : This file contains the class definition for class*
        *              DTIME.                                           *
        *****************************************************************/
 
 
 
#ifndef DTIME_HXX
#define DTIME_HXX
 
#include "../include/system.h"
#include "../include/d_dyn_st.hxx"
 #include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#ifdef ULTRIX
	#include <sys/types.h>
	#include <sys/timeb.h>
#endif

#define OR ||
#define AND &&
 
enum dtime_type {HR12, HR24};
 
typedef unsigned long	secTy;
static const unsigned long day_seconds = (24l * 60l * 60l);
 
class dtime	{
 private:
	secTy seconds;			// number of seconds from midnight
	static char delim;		// delimiter used for time-output
	static dtime_type ttype;	// type of dtime currently using
 
	secTy secs(long hours, long minutes, long seconds); // calc #seconds from midnight
	int hour_test(int hour);	// test validity of hour
	int min_test(int minute);	// test             minute
	int sec_test(int seconds);	// test		    seconds
 
 public:
	dtime(void);			// default constructor=time today
	dtime(dtime&);			// copy in initialization
	dtime(secTy secs, long* over = 0); // constr time from number of secs after midnight
	dtime(d_dyn_string ddtimestring); // construct dtime from dyn. string
	dtime(char* dtimestring);	// construct time from a string
 
	void set_delim(char delimiter); // set the static variable delim
	void set_ttype(dtime_type t);	// set static variable ttype
 
	int ret_hour(void);		// return hour of this dtime
	int ret_minute(void);		// return minute (0..59) of dtime
	int ret_second(void);		// return second (0..59) of dtime
 
	void secs_to_dtime(int& h, int& m, int& s, long* over = 0);
					// give time from seconds 
 
	bool operator==(dtime dtime_2);	// return TRUE if on the same time
	bool operator!=(dtime dtime_2);	// return TRUE if not on the same time
	bool operator>(dtime dtime_2);	// time is later than time_2
	bool operator<(dtime dtime_2);	// dtime is earlier than dtime_2
	bool operator>=(dtime dtime_2);	// dtime is later than dtime_2
	bool operator<=(dtime dtime_2);	// dtime is earlier than dtime_2
	dtime& operator=(dtime& dtime_2); // copy
	dtime operator+(dtime dtime_2); // add two dtimes
	dtime operator+(long seconds);
	dtime operator-(dtime dtime_2);	// subtract dtime_2 from this dtime
	dtime operator-(long seconds);	// subtract #seconds from this dtime
	dtime operator++(void);		// add 1 second to dtime
	dtime operator--(void);		// subtract one second from dtime
	dtime operator+=(dtime dtime_2);// add secs seconds to this dtime
	dtime operator+=(long secs);	// add secs seconds to this dtime
	dtime operator-=(dtime dtime_2);// subtract seconds from this dtime
	dtime operator-=(long secs);	// subtract seconds from this dtime
	dtime add_hours(long hours);	// return this dtime + #hours
	dtime add_minutes(long minutes);// return this dtime + #minutes
	dtime sub_hours(long hours);	// return this dtime - #hours
	dtime sub_minutes(long minutes);// return this dtime - #minutes
	dtime add_period(secTy secs, secTy mins = 0, secTy hours = 0);
	dtime sub_period(secTy secs, secTy mins = 0, secTy hours = 0);

	char* to_string(char* format);	// formatted output 
	void print();			// print the time
 
};
 
#endif /* DTIME_HXX */
