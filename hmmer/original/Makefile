SHELL=/bin/sh

# To assist in cross-compiling
CC=icc
AR=ar
RANLIB=ranlib
LDFLAGS=-lm

BIGFILES=-D_FILE_OFFSET_BITS=64
override CFLAGS += -Wall -Winline -O2 -g $(BIGFILES) -DSPEC_CPU 

# Where you want it installed when you do 'make install'
PREFIX=/usr/local


OBJS= a2m.o       \
	  core_algorithms.o  \
      eps.o    \
      histogram.o   \
      masks.o  \
      phylip.o   \
      rk.o \
      stack.o \
      ucbqsort.o \
      aligneval.o \
      dayhoff.o \
      fast_algorithms.o \
      hmmcalibrate.o \
      mathsupport.o \
      plan7.o \
      selex.o \
      sre_ctype.o \
      stockholm.o \
      vectorops.o \
      alignio.o \
      debug.o \
      file.o \
      hmmio.o \
      misc.o \
      plan9.o \
      seqencode.o \
      sre_math.o \
      tophits.o \
      weight.o \
      alphabet.o \
      display.o \
      getopt.o \
      hmmsearch.o \
      modelmakers.o \
      postprob.o \
      shuffle.o \
      sre_random.o \
      clustal.o \
      emit.o \
      gki.o \
      hsregex.o \
      msa.o \
      prior.o \
      sqerror.o \
      sre_string.o \
      translate.o \
      cluster.o \
      emulation.o \
      gsi.o \
      iupac.o \
      msf.o \
      revcomp.o \
      sqio.o \
      ssi.o \
      trace.o \
      types.o 

all: hmmer 

hmmer : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean: 
	rm -f *.o *.B *.i *.I *.O hmmer 
