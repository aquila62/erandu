#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "erandu.h"

#define SIZE (512*512*3)

/* write one block of ASCII characters to stdout */
void putblk(unsigned char *blk, int len)
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
   unsigned char *p,*q;       /* pointers to mtx */
   unsigned char *mtx;        /* black and white raster matrix */
   char pfx[256];    /* prefix to the pbm format */
   rufmt *ru;        /* erandu structure */

   /********************************************************/
   /* initialize the erandu structure                      */
   /********************************************************/
   ru = (rufmt *) eranduinit();

   /********************************************************/
   /* allocate the raster matrix                           */
   /********************************************************/
   mtx = (unsigned char *) malloc(SIZE + 32);
   if (mtx == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating mtx\n");
      exit(1);
      } /* out of memory */

   /********************************************************/
   /* fill the raster matrix with all white pixels         */
   /********************************************************/
   p = (unsigned char *) mtx;
   q = (unsigned char *) mtx + SIZE;
   while (p < q) *p++ = 0xff;

   /********************************************************/
   /* pick a pixel in the raster matrix at random          */
   /* pick a red   shade 0-255                             */
   /* pick a green shade 0-255                             */
   /* pick a blue  shade 0-255                             */
   /* paint the pixel RGB                                  */
   /* repeat 1 million times                               */
   /* with RANDU, the matrix becomes striated              */
   /* with erandu, the matrix is random                    */
   /* See the pictures randuppm.png                        */
   /* and eranduppm.png                                    */
   /********************************************************/
   i = 1000000;              /* loop counter */
   while (i--)
      {
      int ofst;              /* random offset into matrix */
      int x;                 /* random row in matrix */
      int y;                 /* random column in matrix */
      int rgb;               /* RGB color 0-255 */
      x = erandupwr(ru,9) * 3;   /* calculate column */
      y = erandupwr(ru,9);       /* calculate row */
      ofst = (y * 512 * 3) + x;  /* offset of pixel in matrix */
      p = (unsigned char *) mtx + ofst;   /* point to pixel */
      /* high order 8 bits of erandu seed */
      rgb   = erandupwr(ru,8);      /* calculate white or black */
      *p++  = rgb;       /* paint the pixel RGB */
      rgb   = erandupwr(ru,8);      /* calculate white or black */
      *p++  = rgb;       /* paint the pixel RGB */
      rgb = erandupwr(ru,8);      /* calculate white or black */
      *p  = rgb;       /* paint the pixel RGB */
      } /* for each random pixel */
   strcpy(pfx,"P6 512 512 255 ");   /* ppm format prefix */
   putblk((unsigned char *) pfx,strlen(pfx));     /* write prefix */
   putblk(mtx,SIZE);            /* write the matrix */
   return(0);                   /* normal end of job */
   } /* main */
