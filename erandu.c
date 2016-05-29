/* erandu.c - random number generator Version 1.0.0                  */
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

/********************************************************/
/* erandu: "extended RANDU"                             */
/* This subroutine produces a random unsigned           */
/* 32-bit integer using the RANDU algorithm plus a      */
/* Bays-Durham shuffle.  The previous two cycles are    */
/* xor'd together with the current cycle.               */
/* The speed of erandu is 1/3 faster than the GSL       */
/* subroutine gsl_rng_get(r).                           */
/********************************************************/

#include "erandu.h"

unsigned int erandu(rufmt *ru)
   {
   unsigned int *p;           /* state array pointer */
   unsigned int tmp;          /* used for Bays-Durham shuffle */
   /**********************************************************/
   /* The offset into the state array is not related         */
   /* to the current state.                                  */
   /**********************************************************/
   /* calculate a 10-bit offset into the state array         */
   /* See the Bays-Durham shuffle below.                     */
   ru->ofst  = ru->pprev >> 22;   /* offset into state array */
   ru->pprev = ru->prev;   /* prev prev <== prev             */
   ru->prev  = ru->s;      /* prev <== current               */
   /* calculate new current state                            */
   /* using the RANDU algorithm                              */
   /* The  macro is in erandu.h                              */
   /* XOR the two previous outputs with the current output   */
   RANDU;
   ru->s = (ru->s ^ ru->prev ^ ru->pprev);

   /********************************************************/
   /* Bays-Durham shuffle of state array                   */
   /* 1024! = 5.41e+2639 base 10 rounded down              */
   /* The period length of the state array is theoretical  */
   /* and cannot be proven with empirical testing.         */
   /********************************************************/
   /* point to a state array element                       */
   p     = (unsigned int *) ru->state + ru->ofst;
   /* swap the current output with the member of the state array */
   tmp   = *p;
   *p    = ru->s;
   ru->s = tmp;
   /*********************************************************/
   /* return the output of the erandu cycle after the swap  */
   return(ru->s);
   } /* erandu subroutine */
