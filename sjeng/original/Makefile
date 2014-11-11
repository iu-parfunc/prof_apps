SHELL=/bin/sh

# To assist in cross-compiling
CC=gcc
AR=ar
RANLIB=ranlib
LDFLAGS=

CFLAGS=-Wall -Winline -O2 -g $(BIGFILES) -DSPEC_CPU

# Where you want it installed when you do 'make install'
PREFIX=/usr/local

OBJS= attacks.o book.o crazy.o draw.o ecache.o epd.o eval.o leval.o \
	  moves.o neval.o partner.o proof.o rcfile.o search.o see.o seval.o \
	  ttable.o utils.o sjeng.o

all: sjeng 

sjeng: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

clean: 
	rm -f *.o *.B *.i *.I *.O *.spin sjeng
