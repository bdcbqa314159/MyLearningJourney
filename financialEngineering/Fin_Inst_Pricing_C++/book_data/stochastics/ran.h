

/* File: "sys/libutl/ran.h"
 *
 * 	Random Number Routines
 *
 *
 * Change Log:
 *
 * 
 */



/*
 * Typedefs
 */

#ifndef RAN_H
#define RAN_H

typedef union s_seed
{
  unsigned short data_s[4];
  unsigned int   data_i[2];
}
t_seed;



/*
 * Externs
 */

extern void             RanSetSeed(int);
extern void             RanResetSeed1(t_seed *);
extern void             RanResetSeed2(t_seed *);
extern void             RanGetSeed(t_seed *);
extern void             RanCopySeed(t_seed *, t_seed *);
extern char           * RanSeedText(t_seed *);

extern int              RanI();
extern unsigned int     RanU();
extern float            RanF();
extern double           RanD();
extern int 		RanModN(int n);



/*
 * Portable 32 bit Linear Congruential Random Number Generator
 */

extern unsigned int 	Ran32_UInt();
extern double		Ran32_Double();
extern void		Ran32_SetSeed(unsigned int seed);
extern unsigned int	Ran32_GetSeed();
extern void		Ran32_TestFns();

#endif

