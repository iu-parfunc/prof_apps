SHELL=/bin/sh

# To assist in cross-compiling
# CC=icc
AR=ar
RANLIB=ranlib

# LDFLAGS=-lm  

override CFLAGS +=-Wall -Winline -DSPEC_CPU -DSPEC_CPU_LP64 -DSPEC_CPU_LINUX_X64 

# Where you want it installed when you do 'make install'
PREFIX=/usr/local

OBJS= lbm.o main.o 

all: lbm

lbm: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) 

clean: 
	rm -f *.o *.B *.i *.I *.O *.spin lbm
