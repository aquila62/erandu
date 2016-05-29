#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "erandu.h"

#define SIZE (512*512)

/* write one block of ASCII characters to stdout */
void putblk(char *blk, int len)
   {
   int rslt;
   rslt = write(1,blk,len);
   if (rslt != len)
      {
      fprintf(stderr,"putblk: write error\n");
      exit(1);
      } /* write error */
   } /* putblk */

int main()
   {
   int i;            /* loop counter */
   char *p,*q;       /* pointers to mtx */
   char *mtx;        /* black and white raster matrix */
   char pfx[256];    /* prefix to the pbm format */
   rufmt *ru;        /* erandu structure */

   /********************************************************/
   /* initialize the erandu structure                      */
   /********************************************************/
   ru = (rufmt *) eranduinit();

   /********************************************************/
   /* allocate the raster matrix                           */
   /********************************************************/
   mtx = (char *) malloc(SIZE + 32);
   if (mtx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating mtx\n");
      exit(1);
      } /* out of memory */

   /********************************************************/
   /* fill the raster matrix with all white pixels         */
   /********************************************************/
   p = (char *) mtx;
   q = (char *) mtx + SIZE;
   while (p < q) *p++ = '0';

   /********************************************************/
   /* pick a pixel in the raster matrix at random          */
   /* flip a coin                                          */
   /* if heads, make the pixel black                       */
   /* if tails, make the pixel white                       */
   /* repeat 1 million times                               */
   /* with RANDU, the matrix becomes striated              */
   /* with erandu, the matrix is random                    */
   /* See the pictures randudots.png                       */
   /* and erandudots.png                                   */
   /********************************************************/
   i = 1000000;              /* loop counter */
   while (i--)
      {
      int ofst;              /* random offset into matrix */
      int x;                 /* random row in matrix */
      int y;                 /* random column in matrix */
      int bw;                /* white or black color 0,1 */
      x = erandupwr(ru,9);   /* calculate column */
      y = erandupwr(ru,9);   /* calculate row */
      ofst = (y << 9) + x;   /* offset of pixel in matrix */
      p = (char *) mtx + ofst;   /* point to pixel */
      /* boolean high order bit of erandu seed */
      bw = erandupwr(ru,1);      /* calculate white or black */
      *p = bw + 0x30;      /* paint the pixel white or black */
      } /* for each random pixel */
   strcpy(pfx,"P1 512 512 ");   /* pbm format prefix */
   putblk(pfx,strlen(pfx));     /* write prefix */
   putblk(mtx,SIZE);            /* write the matrix */
   return(0);                   /* normal end of job */
   } /* main */
