        /*===============================================================
        * Prog. Name : DTIME.CXX                                        *
        * Copyright  : Datasim b.v. 1990                                *
        * Author     : Eric Manshande & Henri Schenau  19-3-1990        *
        * Descr.     : This file contains the class DTIME.              *
        ===============================================================*/
 
 
#include "dtime.hxx"
 
// the following initialization of the static variable dtime::delim will
// not work before version 2.00 of C++, because static variables are
// implicitly defined 0. Version 2.00 requires this initialization. 
// Because a value 0 for the delimiter is invalid, the function 
// set_delim(char d) must be called in the main program with a valid 
// delimiter character d (when before 2.00).
 
// dtime::delim = ':';
 
secTy dtime::secs(long hours, long minutes, long secos)
/*
 *	return the number of seconds after midnight (12:00 AM) from
 *	hours, minutes and seconds. If one of them is < 0 then 
 *	return 0. (=midnight). The number of hours, minutes and seconds
 *	may be any value (> 0).
 */
{
	if (hours < 0 OR minutes < 0 OR secos < 0)
		return(0);
	else {
		minutes += (secos / 60);	// #minutes in seconds
		secos %= 60;			// rest seconds
		hours += (minutes / 60);	// #hours in minutes
		minutes %= 60;			// rest minutes
		hours %= 24;			// discard day-limit
		return(hours * 60l * 60l + minutes * 60l + secos);// total
					// number of seconds after 12:00
	}
}
 
 
int dtime::hour_test(int hour)
/*
 *	test if hours has a valid value. It must be between 0 and 23, 
 *	(so 24 is an invalid value). An invalid hour will give a returnvalue
 *	of -1, a valid value will be returned.
 */
{
	if (hour > 23 OR hour < 0)
		return(-1);
	else 
		return(hour);
}
 
 
 
int dtime::min_test(int minutes)
/*
 *	test if minutes has a valid value. It must be between 0 and 59, 
 *	(so 60 is an invalid value). An invalid value will give a returnvalue
 *	of -1, a valid value will be returned.
 */
{
        if (minutes > 59 OR minutes < 0)
		return(-1);
	else
		return(minutes);
}
 
 
int dtime::sec_test(int secos)
/*
 *	test if seconds has a valid value. It must be between 0 and 59, 
 *	(so 60 is an invalid value). An invalid value will give a returnvalue
 *	of -1, a valid value will be returned.
 */
{
	if (secos > 59 OR secos < 0)
		return(-1);
	else
		return(secos);
}
 
 
dtime::dtime(secTy secs, long* over)
/*
 *	construct a time from a number of seconds. If the number of 
 *	seconds passes a day-limit and the default argument '*over' has
 *	been passed, *over will be set to the number of days past.
 */
{
	if (secs >= day_seconds AND over != 0) 	// past day-limit
						// and par. '*over' passed
		*over = secs / day_seconds;	// #days past
	secs %= day_seconds;			// rest of seconds
	seconds = secs;
}
 
dtime::dtime(dtime& dtime_2)
/*
 *	this constructor is for the copy in initialization. It is not
 *	really necessary to declare this one because a bitwise copy (before
 *	2.00) has the same effect.
 */
{
	seconds = dtime_2.seconds;
}
 
 
dtime::dtime(void)
/*
 *	default constructor. Gives the time at the moment of creation.
 *	because this function uses ANSI structures and function, it 
 *	should be machine independant.
 */
{
        time_t local_time;              // type to hold time
        struct tm *t_ptr;               // struct to contain time, date etc
 
        local_time = time(NULL);        // get time (and date) from system
        t_ptr = localtime(&local_time); // convert to struct 
        int hour_t = hour_test(t_ptr->tm_hour);	// test hour.
        int min_t = min_test(t_ptr->tm_min);	// test minute
        int sec_t = sec_test(t_ptr->tm_sec);	// test second
        seconds = secs(hour_t, min_t, sec_t);	// cal. seconds from midnight
}
 
 
dtime::dtime(d_dyn_string ddtime_string)
/*
 *	construct a dtime from a dynamic string. The format depends
 *	on the static variable ttype. When the given string does not
 *	match the format, a dtime with 0 seconds (midnight) will be returned.
 */
{
        static char seperators[] = {'.', '/', ':', '\\', '-', '_'};
        static int len = sizeof(seperators);
	char* delim = " ";			// space character
 
        for (int i = 0; i != len; i++) {        // replace all seperators
                char sep_str[2];                // make sepeator string
                sep_str[0] = seperators[i];
                sep_str[1] = '\0';
                d_dyn_string dsep(sep_str);
                for (int pos = ddtime_string.strindex(dsep); pos != -1
		    AND *delim != seperators[i] ; ) { 
	                ddtime_string.strsub(pos, 1, delim); // replace
	                pos = ddtime_string.strindex(dsep);
                }
        }
 
	ddtime_string = ddtime_string.uppercase();// string to uppercase
        ddtime_string = ddtime_string.trim();     // rem. lead. and trail. blanks
        ddtime_string = ddtime_string.compress(); // rem. multiple tabs and spaces
 
        int sec_t, min_t, hour_t;
 
        ddtime_string = ddtime_string.stripint(hour_t, *delim); //get hours
        ddtime_string = ddtime_string.stripint(min_t, *delim); //get minutes
        sec_t = ddtime_string.strintconv();		//get seconds
        sec_t = sec_test(sec_t);		// test seconds
        min_t = min_test(min_t);		// test minutes
        hour_t = hour_test(hour_t);		// test hours
	seconds = secs(hour_t, min_t, sec_t);        // calc seconds
}
 
 
dtime::dtime(char* dtime_string)
/*
 *	construct a dtime froma standard-C++ character string.
 */
{
	d_dyn_string ddtime_string(dtime_string);// construct dynamic string
	*this = dtime(ddtime_string);		// call other constructor
}
 
 
void dtime::set_delim(char delimiter)
/*
 *	set the static variable (class variable) delim to delimiter.
 *	This is the delimiter used in output functions for dtime.
 */
{
	delim = delimiter;
}
 
 
void dtime::set_ttype(dtime_type t)
/*
 *	set the static variable (class variable) ttype to t.
 *	ttype Indicates the current dtime-format for in- and out-
 *	put of dtimes. For the values and the corresponding formats
 *	see the header file dtime.hxx.
 */
{
	ttype = t;
}
 
 
int dtime::ret_hour(void)
/*
 *	return the hour of the day from this dtime.
 */
{
	int h, m, s;		// hour, minute and seconds
	secs_to_dtime(h, m, s); // get hour,minute and seconds of day
	return(h);		// return hour of day
}
 
 
int dtime::ret_minute(void)
/*
 *	return the minute (0..59) past last hour from this dtime.
 */
{
	int h, m, s;		// hour, minute and seconds
	secs_to_dtime(h, m, s); // get hour,minute and seconds of day
	return(m);		// return minute
}
 
 
int dtime::ret_second(void)
/*
 *	return the second (0..59) past last minute from this dtime.
 */
{
	int h, m, s;		// hour, minute and seconds
	secs_to_dtime(h, m, s); // get hour,minute and seconds of day
	return(s);		// return second
}
 
 
void dtime::secs_to_dtime(int& hour, int& minute, int& second, long* over)
/*
 *	calculate the time of the day (hour, minute, second) from
 *	the given seconds (which is the number of seconds past midnight).
 *	If the number of seconds is more than seconds in one day, the
 *	parameter 'over' will point to that number of days (seconds div 
 *	day_seconds) if the parameter has been passed (it is a default
 *	argument, default = 0), otherwise it will remain 0 (null pointer).
 */
{
printf("seconds = %lu\n", seconds);
	if (over != 0)			// parameter has been passed
		*over = seconds / day_seconds;	// number of days in seconds
//	seconds %= day_seconds;		// rest seconds
printf("seconds after days subtr. = %lu\n", seconds);
	hour = seconds / 3600;		// calculate hours from midnight
	int h = seconds % 3600;		// rest
	minute = h / 60;		// calc. minutes after 'hour'
	second = h % 60;		// calc seconds after 'minute'
printf("hour = %d\nminute = %d\nsecond = %d\n", hour, minute, second);
}
 
 
bool dtime::operator==(dtime dtime_2)
/*
 *	compare two dtimes. Return TRUE if they are on the same time, 
 *	else return FALSE. They need not be the same objects.
 */
{
	if (seconds == dtime_2.seconds)
		return(TRUE);
	else
		return(FALSE);
};
		
 
bool dtime::operator!=(dtime dtime_2)
/*
 *	compare two dtimes. Return TRUE if they are not on the same time, 
 *	else return FALSE. They need not be the same objects.
 */
{
	if (seconds != dtime_2.seconds)
		return(TRUE);
	else
		return(FALSE);
}
 
 
bool dtime::operator>(dtime dtime_2)
/*
 *	if this dtime is later than dtime_2, return TRUE, else return FALSE.
 */
{
	if (seconds > dtime_2.seconds)
		return(TRUE);
	else
		return(FALSE);
}
 
bool dtime::operator<(dtime dtime_2)
/*
 *	if this dtime is earlier than dtime_2, return TRUE, else return FALSE.
 */
{
	if (seconds < dtime_2.seconds)
		return(TRUE);
	else
		return(FALSE);
}
 
 
bool dtime::operator>=(dtime dtime_2)
/*
 *	if dtime_2 is earlier than this dtime return TRUE, else return FALSE.
 */
{
	if (seconds >= dtime_2.seconds)
		return(TRUE);
	else
		return(FALSE);
}
 
 
bool dtime::operator<=(dtime dtime_2)
/*
 *	if dtime_2 is later than this dtime return TRUE, else return FALSE.
 */
{
	if (seconds <= dtime_2.seconds)
		return(TRUE);
	else
		return(FALSE);
}
 
 
dtime dtime::operator++(void)
/*
 *	add 1 second to this dtime and return it. Discard the overflow
 *	fi there is one.
 */
{
	seconds++;				// one second later
	seconds %= day_seconds;			// discard overflow
	return(*this);				// return second later
}
 
 
dtime dtime::operator--(void)
/*
 *	subtract 1 second from this dtime and return it. Discard an 
 *	underflow if there is one.
 */
{
	seconds = seconds + day_seconds - 1;	// one second earlier
	seconds %= day_seconds;			// discard underflow
	return(*this);				// return second earlier
}
 
 
dtime dtime::operator+(dtime t2)
/*
 *	add two dtimes. If the resulting time passes a day-limit, discard
 *	the overflow. return the added time.
 */
{
	secTy tot_sec = seconds + t2.seconds;	// total # seconds
	tot_sec %= day_seconds;			// discard overflow
	dtime t(tot_sec);			// construct dtime from rest
	return(t);				// return added time
}
 
 
dtime dtime::operator+(long secos)
/*
 *	return this dtime + #seconds. If the resulting time passes a day-limit
 *	discard the overflow. #seconds May be negative.
 */
{
	dtime tmp;
	if (secos >= 0)
		tmp = *this + dtime(secos);	// construct dtime, discard ovf
	else 
		tmp = *this + dtime(secos * -1); // construct dtime
	return(tmp);				// return dtime
}
 
 
dtime dtime::operator-(dtime t2)
/*
 *	subtract dtime_2 from this dtime. If the resulting time passes 
 *	a day-limit, discard the underflow. return the new time.
 */
{
	dtime tmp;				// temporary dtime
	if (*this >= t2)			// result will be pos
		tmp = dtime(seconds - t2.seconds); // subtract seconds and constr.
	else 					// result will be negative
		tmp = dtime(day_seconds - t2.seconds + seconds);
						// make positive and construct
	return(tmp);				// return added time
}
 
 
dtime dtime::operator-(long nr_secs)
/*
 *	return this dtime - #seconds. If the resulting time passes a day-limit
 *	discard the underflow. #seconds May be negative.
 */
{
	dtime tmp;
	if (nr_secs >= 0)			// #seconds is positive
		tmp = *this - dtime(nr_secs);	// construct dtime, discard ovf
	else 					// #seconds is negative
		tmp = *this - dtime(nr_secs * -1); // construct dtime
	return(tmp);				// return dtime
}
 
 
dtime dtime::operator+=(long secos)
/*
 *	add a number of seconds to this dtime and return it. If the
 *	dtime passes a time limit, discard the overflow. The number
 *	of seconds may be positive or negative.
 */
{
	*this = *this + secos;	// call operator+, add seconds
	return(*this);			// return new this dtime
}
 
 
dtime dtime::operator+=(dtime dtime_2)
/*
 *	add dtime_2 to this dtime and return it. If the 
 *	dtime passes a day-limit, the overflow is discarded.
 */
{
	*this = *this + dtime_2;	// add dtime_2 to this dtime
	return(*this);			// return it
}
 
 
dtime dtime::operator-=(dtime dtime_2)
/*
 *	subtract dtime_2 from this dtime (so this dtime will be changed)
 *	and return it. If the dtime passes day-limit, the overflow will
 *	be discarded.
 */
{
	*this = *this - dtime_2;	// call operator-, subtract time
	return(*this);
}
 
 
dtime dtime::operator-=(long secos)
/*
 *	subtract a number of seconds from this dtime (so this dtime will
 *	be changed) and return it. when the time passes a day-limit, the
 *	underflow will be discarded. The number of secons may be positive
 *	or negative.
 */
 {
	*this = *this - secos;	// call operator-, add seconds
	return(*this);			// return new this dtime
}
 
 
dtime& dtime::operator=(dtime& dtime_2)
/*
 *	assign dtime_2 to this dtime. Check ik they are the same objects
 *	(this is not really necessary) and return the new dtime (a reference).
 */
{
	if (this != &dtime_2)			// beware of t = t;
		seconds = dtime_2.seconds;
	return(*this);				// for multiple assignment
}
 
 
void dtime::print()
{
	int hour = 0, min = 0, sec = 0;
	secs_to_dtime(hour, min, sec);
	printf("%02d%c%02d%c%02d", hour, delim, min, delim, sec);
}
 
 
dtime dtime::add_period(secTy secos, secTy mins, secTy hours)
/*
 *	add a period of time to this dtime. The number of seconds can be
 *	any value (may be > 59), the number of minutes can be any value
 *	(may be > 59) and also the number of hours can be any value (may
 *	be > 23). If a day-limit is passed, the overflow will be discarded.
 */
{
	
	dtime tmp = dtime( secs(secos, mins, hours) ); // construct dtime
	tmp = *this + tmp;			// add dtimes
	return(tmp);				// return new time
}
 
 
dtime dtime::sub_period(secTy secos, secTy mins, secTy hours)
/*
 *	subtract a period of time from this dtime. The number of seconds can be
 *	any value (may be > 59), the number of minutes can be any value
 *	(may be > 59) and also the number of hours can be any value (may
 *	be > 23). If a day-limit is passed, the underrflow will be discarded.
 */
{
	dtime tmp = dtime( secs(secos, mins, hours) ); // construct dtime
	tmp = *this - tmp;			// subtract dtime
	return(tmp);				// return new time
}
	
	
dtime dtime::add_hours(long hours)
/*
 *	return a number of hours added to this dtime. If the dtime passes
 *	a day-limit, the overflow will be discarded. The number of hours
 *	may be positive or negative.
 */
{ 
	dtime tmp;			// for temporary result
	if (hours >= 0)			// add positive #hours
		tmp = add_period(0, 0, hours);	// add hours
	else				// add negative #hours
		tmp = sub_period(0, 0, hours * -1); // subtract hours
	return(tmp);			// return result
}
 
 
dtime dtime::sub_hours(long hours)
/*
 *	return a number of hours subtracted from this dtime. If the dtime 
 *	passes a day-limit, the overflow will be discarded. The number of hours
 *	may be positive or negative.
 */
{ 
	dtime tmp;			// for temporary result
	if (hours >= 0)			// subtract positive #hours
		tmp = sub_period(0, 0, hours);	// subtract #hours
	else				// subtract negative #hours
		tmp = add_period(0, 0, hours * -1); // add #hours
	return(tmp);			// return result
}
 
 
dtime dtime::add_minutes(long minutes)
/*
 *	return a number of minutes added to this dtime. If the dtime passes
 *	a day-limit, the overflow will be discarded. The number of minutes
 *	may be positive or negative.
 */
{ 
	dtime tmp;			// for temporary result
	if (minutes >= 0)			// add positive #minutes
		tmp = add_period(0, minutes);	// add #minutes
	else				// add negative #minutes
		tmp = sub_period(0, minutes * -1); // subtract minutes
	return(tmp);			// return result
}
 
 
dtime dtime::sub_minutes(long minutes)
/*
 *	return a number of minutes subtracted from this dtime. If the dtime 
 *	passes a day-limit, the overflow will be discarded. The number of
 *	minutes may be positive or negative.
 */
{ 
	dtime tmp;				// for temporary result
	if (minutes >= 0)			// subtract positive #minutes
		tmp = sub_period(0, minutes); // subtract #minutes
	else					// subtract negative #minutes
		tmp = add_period(0, minutes * -1); // subtract #minutes
	return(tmp);				// return result
}


char* dtime::to_string(char* s)
/*
 *	convert the dtime to a string and return it. If s is 0 (NULL-pointer)
 *	the format depends on the static variable dtype. If s is not 0 it
 *	contains the format-string for the output-string. The format-string
 *	can contain the following elements:
 *	%H	insert hour (0..23) in 1 digit if possible, otherwise 2 digits
 *	%HH	insert hour (0..23) in 2 digits, first digit may be 0
 *	%h	insert hour (1..12) in 1 digit if possible, otherwise 2 digits
 *	%hh	insert hour (1..11) in 2 digits, first digit may be 0
 *	%M	insert minute (0..59) in 1 digit if possible, otherwise 2
 *	%MM	insert minute (0..59) in 2 digits, first digit may be 0
 *	%S	insert second (0..59) in 1 digit if possible, otherwise 2
 *	%SS	insert second (0..59) in 2 digits, first digit may be 0
 *	%AM     insert AM or PM indicator
 *	%PM	insert AM or PM indicator
 *	any other character will be copied to the output string.
 *	for example: 
 * 		dtime d("00:02:09");
 *		char* str = d.to_string("[%h]-[%MM]-[%S]-[%PM]");
 *	will result str to be:
 *		"[12]-[02]-[9]-[AM]"
 */
{
	int hour, minute, second;
	secs_to_dtime(hour, minute, second);
	if (s == 0) {
		char *str = new char[20];
		if (!str) exit(1);
		switch (ttype) {
		case HR12: 		// hh:mm:ss AM  or  hh:mm:ss PM
			if (hour < 12) {	// AM
				if (hour == 0)
					hour = 12;	// 00:MM:SS not possible
				sprintf(str, "%02lu%c%02lu%c%02lu AM", hour, delim, minute, delim, second);
			}
			else		// PM
			 	sprintf(str, "%02lu%c%02lu%c%02lu PM", hour - 12, delim, minute, delim, second);
			break;
		case HR24:		// hh:mm:ss 24 hours
		default:
			sprintf(str, "%02lu%c%02lu%c%02lu", hour, delim, minute, delim, second);
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
				switch (s[count++]) {	// scan time expression
				case 'P': ;		// %AM or %PM ?
				case 'A':
				   if (s[count] == 'M') {
					count++;
					if (hour >= 12)
						sprintf(str + outcnt, "AM");
					else
						sprintf(str + outcnt, "PM");
				   }
				   outcnt = strlen(str);
				   break;
				case 'H': 		// H or HH
				   if (s[count] == 'H') { // 2 digits for hour
					count++;
					sprintf(str + outcnt, "%02lu", hour);
				   }
				   else 		// 1 digit if possible
					sprintf(str + outcnt, "%lu", hour);
				   outcnt = strlen(str);
				   break;
				case 'h': 		// h or hh (1..12)
				   if (s[count] == 'h') { // 2 digits for day
					if (hour < 12) {	// 0..11
						if (hour == 0)
							hour = 12;
						sprintf(str + outcnt, "%02lu", hour);
					}
					else 
						sprintf(str + outcnt, "%02lu", hour);
					count++;
				   }
				   else { 		// 1 digit if possible
					if (hour < 12) {	// 0..11
						if (hour == 0)
							hour = 12;
						sprintf(str + outcnt, "%lu", hour);
					}
					else 
						sprintf(str + outcnt, "%lu", hour);
				   }
				   outcnt = strlen(str);
				   break;
				case 'M':		// M or MM
				   if (s[count] == 'M') { // 2 digits for minute
					count++;
					sprintf(str + outcnt, "%02lu", minute);
					outcnt = strlen(str);
				   }
				   else	{		// 1 digit if possible
					sprintf(str + outcnt, "%lu", minute);
					outcnt = strlen(str);
				   }
				   break;
				case 'S':		// S or SS
				   if (s[count] == 'S') { // 2 digits for second
					count++;
					sprintf(str + outcnt, "%02lu", second);
					outcnt = strlen(str);
				   }
				   else	{		// 1 digit if possible
					sprintf(str + outcnt, "%lu", second);
					outcnt = strlen(str);
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
