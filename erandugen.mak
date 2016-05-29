#  erandugen.mak - Compile erandugen.c Version 1.0.0
#  Copyright (C) 2016 aquila62 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

# this program feeds ranwlk.c
# use tstwlk.sh to test this program with ranwlk.c

OBJ=erandugen.o \
	eranduinit.o \
	erandu.o \
	erandubit.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=

erandugen:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o erandugen $(LDFLAGS)

erandugen.o:			erandugen.c
		$(CC) $(CFLAGS) erandugen.c

eranduinit.o:			eranduinit.c
		$(CC) $(CFLAGS) eranduinit.c

erandu.o:			erandu.c
		$(CC) $(CFLAGS) erandu.c

erandubit.o:			erandubit.c
		$(CC) $(CFLAGS) erandubit.c

clean:
		rm -f $(OBJ) erandugen
