#ifndef CONSTANT_HXX
#define CONSTANT_HXX
// Central declaration of some constants
// Last Modification: 23-4-92 Henry Schenau: new BOOLEAN

#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include <iostream.h>
#include <math.h>



#define PI 3.14159265359
#define pi 3.14159265359  // Will eventually (op ten dur) disappear

#define UNDEFINED 9e99

const int MAX_LENGTH_INT = 10;   // used in DYNSTR
const int LINE_WIDTH = 80;  // used in DYNSTR
const int SPACE = ' ';      // used in DYNSTR
const int ON  = 1;          // used in BYTE (no enum because it refers to a)
const int OFF = 0;          // used in BYTE (variable)
const int NOT_FOUND = -1;   // used in STRLIST
enum CASE_SENS {NO_SENS, SENS}; // used in STRLIST

// used in DICT
const int MAX_DICT = 10;    // DICT: Maximum number of VALUES per RECORD.

enum BGFTYPE {ASCII=0, BINARY=1};

enum ERR_STATE {OK=1, INVINP=2, ERROPN=3, ERREAD=4, ERROOB=5, INVARG=6,\
				  ERRMEM=7};
//typedef enum ERROR_STATE ERR_STATE;

enum BOOLEAN {FALSE, TRUE};

// Enums for the CAD classes here

// PO
enum CARTESIAN_AXIS {X, Y, Z};

// LI

// CI

// AR
enum ANG_ORIENT {COUNTERCLOCKWISE, CLOCKWISE};


// Values used in function evaluations
#define STOP_CONDITION 100
#define GAMMA_TOL 1.0e-7

// Values in numerical integration
#define TRAP_INTERVAL 30	// Used in CNSDIST (trapezoidal rule)

#endif // CONSTANT_HXX

