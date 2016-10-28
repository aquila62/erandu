/* eranduinit.c - Extended erandu initialization Version 1.0.0          */
/* Copyright (C) 2016 aquila62 at github.com                         */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

/* This is the initialization routine for extended erandu    */
/* This initialization routine is based on date/time/ticks   */
/* The caller is welcome to override the following:          */
/* the state array                                           */
/* the two previous outputs                                  */
/* the current output                                        */
/* the three states for the erandu algorithm                 */
/*                                                           */
/* The period length of erandu is estimated to be            */
/* 5.41e+2639.                                               */
/* The period length of GSL taus2 is 3.09e+26.               */
/* The speed of erandu is 1/3 faster than the GSL version    */
/* of taus2.                                                 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include "erandu.h"

/* size of the state array is 2^10 */
#define STATES 1024

rufmt *eranduinit(void)
   {
   int i;                      /* loop counter */
   unsigned int dttk;          /* combined date, time, and #ticks */
   unsigned int *stp,*stq;     /* pointer into state array */
   time_t now;                 /* current date and time */
   clock_t clk;                /* current number of ticks */
   struct tms t;               /* structure used by times() */
   rufmt *ru;                  /* erandu structure */

   /***************************************************/
   /* allocate memory for erandu structure            */
   /***************************************************/
   ru = (rufmt *) malloc(sizeof(rufmt));
   if (ru == NULL)
      {
      fprintf(stderr,"eranduinit: out of memory "
      "allocating erandu structure ru\n");
      exit(1);
      } /* out of memory */
   ru->states = STATES; /* save the number of erandu states */

   /***************************************************/
   /* allocate memory for erandu state array          */
   /***************************************************/
   ru->state = (unsigned int *)
      malloc(sizeof(unsigned int) * STATES);
   if (ru->state == NULL)
      {
      fprintf(stderr,"eranduinit: out of memory "
      "allocating ru->state state array\n");
      exit(1);
      } /* out of memory */

   /***************************************************/
   /* Randomize the seeds and states                  */
   /***************************************************/
   /* get clock ticks since boot                           */
   clk = times(&t);
   /* get date & time                                      */
   time(&now);
   /* combine date, time, and ticks into a single UINT     */
   dttk = (unsigned int) (now ^ clk) | 1;
   /* initialize the erandu state to date,time,ticks       */
   /* the initial seed must be an odd number               */
   ru->s = dttk | 1;      /* initialize s to combined dttk     */

   /***************************************************/
   /* Warm up the erandu state.                       */
   /* ru->s is truncated to 31 bits                   */
   /***************************************************/
   i = 128;
   while (i--) RANDU;

   /***************************************************/
   /* initialize out, prev, and prev prev             */
   /* to random values                                */
   /***************************************************/
   RANDU;
   ru->out   = ru->s;           /* set to random 31-bit UINT */
   RANDU;
   ru->pprev = ru->s;           /* set to random 31-bit UINT */
   RANDU;
   ru->prev  = ru->s;           /* set to random 31-bit UINT */

   /***************************************************/
   /* initialize the state array to random values     */
   /***************************************************/
   stp = (unsigned int *) ru->state;
   stq = (unsigned int *) ru->state + STATES;
   while (stp < stq)
      {
      RANDU;                    /* set to random 31-bit UINT */
      *stp++ = ru->s;           /* set to random UINT */
      } /* for each member in ru->state array */

   /***************************************************/
   /* Warm up the erandu state table.                 */
   /***************************************************/
   i = 128;
   while (i--) erandu(ru);

   /***************************************************/
   /* after this subroutine you may initialize the    */
   /* state array to your own values, if you wish     */
   /* to do regression testing.                       */
   /* Use the above 9 instructions as an example of   */
   /* how to initialize the generator                 */
   /***************************************************/
   /* return the erandu structure                     */
   /***************************************************/
   return(ru);
   } /* eranduinit subroutine */
