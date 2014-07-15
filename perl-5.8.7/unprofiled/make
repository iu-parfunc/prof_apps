SHELL=/bin/sh

# To assist in cross-compiling
CC=icc
AR=ar
RANLIB=ranlib
LDFLAGS=-lm  

CFLAGS=-Wall -Winline -O2 -DSPEC_CPU -DPERL_CORE -DSPEC_CPU_LP64 -DSPEC_CPU_LINUX_X64 

# Where you want it installed when you do 'make install'
PREFIX=/usr/local

OBJS= av.o deb.o doio.o doop.o dump.o globals.o gv.o hv.o locale.o mg.o \
		 numeric.o op.o pad.o perl.o perlapi.o perlio.o perlmain.o perly.o pp.o \
		 pp_ctl.o pp_hot.o pp_pack.o pp_sort.o pp_sys.o regcomp.o regexec.o run.o \
		 scope.o sv.o taint.o toke.o universal.o utf8.o util.o xsutils.o Base64.o \
		 Cwd.o Dumper.o HiRes.o IO.o Peek.o attrs.o poll.o stdio.o DynaLoader.o \
		 MD5.o Storable.o Parser.o specrand.o Hostname.o Opcode.o

all: perlbench 

perlbench: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS) 

clean: 
	rm -f *.o *.B *.i *.I *.O *.spin perlbench
