
#line 1 "./instrumented/./unlzh.c"
/* unlzh.c -- decompress files in SCO compress -H (LZH) format.
 * The code in this file is directly derived from the public domain 'ar002'
 * written by Haruhiko Okumura.
 */

#ifdef RCSID
static char rcsid[] = "$Id: unlzh.c,v 1.2 1993/06/24 10:59:01 jloup Exp $";
#endif

#include <stdio.h>

#include "tailor.h"
#include "gzip.h"
#include "lzw.h" /* just for consistency checking */

/* decode.c */

int global_x;

local unsigned  decode  OF((unsigned count, uch buffer[]));
local void decode_start OF((void));

/* huf.c */
local void huf_decode_start OF((void));
local unsigned decode_c     OF((void));
local unsigned decode_p     OF((void));
local void read_pt_len      OF((int nn, int nbit, int i_special));
local void read_c_len       OF((void));

/* io.c */
local void fillbuf      OF((int n));
local unsigned getbits  OF((int n));
local void init_getbits OF((void));

/* maketbl.c */

local void make_table OF((int nchar, uch bitlen[],
			  int tablebits, ush table[]));


#define DICBIT    13    /* 12(-lh4-) or 13(-lh5-) */
#define DICSIZ ((unsigned) 1 << DICBIT)

#ifndef CHAR_BIT
#  define CHAR_BIT 8
#endif

#ifndef UCHAR_MAX
#  define UCHAR_MAX 255
#endif

#define BITBUFSIZ (CHAR_BIT * 2 * sizeof(char))
/* Do not use CHAR_BIT * sizeof(bitbuf), does not work on machines
 * for which short is not on 16 bits (Cray).
 */

/* encode.c and decode.c */

#define MAXMATCH 256    /* formerly F (not more than UCHAR_MAX + 1) */
#define THRESHOLD  3    /* choose optimal value */

/* huf.c */

#define NC (UCHAR_MAX + MAXMATCH + 2 - THRESHOLD)
	/* alphabet = {0, 1, 2, ..., NC - 1} */
#define CBIT 9  /* $\lfloor \log_2 NC \rfloor + 1$ */
#define CODE_BIT  16  /* codeword length */

#define NP (DICBIT + 1)
#define NT (CODE_BIT + 3)
#define PBIT 4  /* smallest integer such that (1U << PBIT) > NP */
#define TBIT 5  /* smallest integer such that (1U << TBIT) > NT */
#if NT > NP
# define NPT NT
#else
# define NPT NP
#endif

/* local ush left[2 * NC - 1]; */
/* local ush right[2 * NC - 1]; */
#define left  prev
#define right head
#if NC > (1<<(BITS-2))
    error cannot overlay left+right and prev
#endif

/* local uch c_len[NC]; */
#define c_len outbuf
#if NC > OUTBUFSIZ
    error cannot overlay c_len and outbuf
#endif

local uch pt_len[NPT];
local unsigned blocksize;
local ush pt_table[256];

/* local ush c_table[4096]; */
#define c_table d_buf
#if (DIST_BUFSIZE-1) < 4095
    error cannot overlay c_table and d_buf
#endif

/***********************************************************
        io.c -- input/output
***********************************************************/

local ush       bitbuf;
local unsigned  subbitbuf;
local int       bitcount;

local void fillbuf(n)  /* Shift bitbuf n bits left, read n bits */
    int n;
{

#line 113

__notify_intrinsic((void*)"fillbuf:start", (void *)&global_x);

#line 113
{
    bitbuf <<= n;
    while (n > bitcount) {
	bitbuf |= subbitbuf << (n -= bitcount);
	subbitbuf = (unsigned)try_byte();
	if ((int)subbitbuf == EOF) subbitbuf = 0;
	bitcount = CHAR_BIT;
    }
    bitbuf |= subbitbuf >> (bitcount -= n);

#line 122

}
	

#line 122
}

local unsigned getbits(n)
    int n;
{

#line 126

__notify_intrinsic((void*)"getbits:start", (void *)&global_x);

#line 126
{
    unsigned x;

    x = bitbuf >> (BITBUFSIZ - n);  fillbuf(n);
    
#line 130
{ unsigned int tau_ret_val =  x; __notify_intrinsic((void*)"getbits:end", (void *)&global_x); return (tau_ret_val); }

#line 130


#line 131

}
	

#line 131
}

local void init_getbits()
{

#line 134

__notify_intrinsic((void*)"init_getbits:start", (void *)&global_x);

#line 134
{
    bitbuf = 0;  subbitbuf = 0;  bitcount = 0;
    fillbuf(BITBUFSIZ);

#line 137

}
	

#line 137
}

/***********************************************************
	maketbl.c -- make table for decoding
***********************************************************/

local void make_table(nchar, bitlen, tablebits, table)
    int nchar;
    uch bitlen[];
    int tablebits;
    ush table[];
{

#line 148

__notify_intrinsic((void*)"make_table:start", (void *)&global_x);

#line 148
{
    ush count[17], weight[17], start[18], *p;
    unsigned i, k, len, ch, jutbits, avail, nextcode, mask;

    for (i = 1; i <= 16; i++) count[i] = 0;
    for (i = 0; i < (unsigned)nchar; i++) count[bitlen[i]]++;

    start[1] = 0;
    for (i = 1; i <= 16; i++)
	start[i + 1] = start[i] + (count[i] << (16 - i));
    if ((start[17] & 0xffff) != 0)
	error("Bad table\n");

    jutbits = 16 - tablebits;
    for (i = 1; i <= (unsigned)tablebits; i++) {
	start[i] >>= jutbits;
	weight[i] = (unsigned) 1 << (tablebits - i);
    }
    while (i <= 16) {
	weight[i] = (unsigned) 1 << (16 - i);
	i++;
    }

    i = start[tablebits + 1] >> jutbits;
    if (i != 0) {
	k = 1 << tablebits;
	while (i != k) table[i++] = 0;
    }

    avail = nchar;
    mask = (unsigned) 1 << (15 - tablebits);
    for (ch = 0; ch < (unsigned)nchar; ch++) {
	if ((len = bitlen[ch]) == 0) continue;
	nextcode = start[len] + weight[len];
	if (len <= (unsigned)tablebits) {
	    for (i = start[len]; i < nextcode; i++) table[i] = ch;
	} else {
	    k = start[len];
	    p = &table[k >> jutbits];
	    i = len - tablebits;
	    while (i != 0) {
		if (*p == 0) {
		    right[avail] = left[avail] = 0;
		    *p = avail++;
		}
		if (k & mask) p = &right[*p];
		else          p = &left[*p];
		k <<= 1;  i--;
	    }
	    *p = ch;
	}
	start[len] = nextcode;
    }

#line 201

}
	

#line 201
}

/***********************************************************
        huf.c -- static Huffman
***********************************************************/

local void read_pt_len(nn, nbit, i_special)
    int nn;
    int nbit;
    int i_special;
{

#line 211

__notify_intrinsic((void*)"read_pt_len:start", (void *)&global_x);

#line 211
{
    int i, c, n;
    unsigned mask;

    n = getbits(nbit);
    if (n == 0) {
	c = getbits(nbit);
	for (i = 0; i < nn; i++) pt_len[i] = 0;
	for (i = 0; i < 256; i++) pt_table[i] = c;
    } else {
	i = 0;
	while (i < n) {
	    c = bitbuf >> (BITBUFSIZ - 3);
	    if (c == 7) {
		mask = (unsigned) 1 << (BITBUFSIZ - 1 - 3);
		while (mask & bitbuf) {  mask >>= 1;  c++;  }
	    }
	    fillbuf((c < 7) ? 3 : c - 3);
	    pt_len[i++] = c;
	    if (i == i_special) {
		c = getbits(2);
		while (--c >= 0) pt_len[i++] = 0;
	    }
	}
	while (i < nn) pt_len[i++] = 0;
	make_table(nn, pt_len, 8, pt_table);
    }

#line 238

}
	

#line 238
}

local void read_c_len()
{

#line 241

__notify_intrinsic((void*)"read_c_len:start", (void *)&global_x);

#line 241
{
    int i, c, n;
    unsigned mask;

    n = getbits(CBIT);
    if (n == 0) {
	c = getbits(CBIT);
	for (i = 0; i < NC; i++) c_len[i] = 0;
	for (i = 0; i < 4096; i++) c_table[i] = c;
    } else {
	i = 0;
	while (i < n) {
	    c = pt_table[bitbuf >> (BITBUFSIZ - 8)];
	    if (c >= NT) {
		mask = (unsigned) 1 << (BITBUFSIZ - 1 - 8);
		do {
		    if (bitbuf & mask) c = right[c];
		    else               c = left [c];
		    mask >>= 1;
		} while (c >= NT);
	    }
	    fillbuf((int) pt_len[c]);
	    if (c <= 2) {
		if      (c == 0) c = 1;
		else if (c == 1) c = getbits(4) + 3;
		else             c = getbits(CBIT) + 20;
		while (--c >= 0) c_len[i++] = 0;
	    } else c_len[i++] = c - 2;
	}
	while (i < NC) c_len[i++] = 0;
	make_table(NC, c_len, 12, c_table);
    }

#line 273

}
	

#line 273
}

local unsigned decode_c()
{

#line 276

__notify_intrinsic((void*)"decode_c:start", (void *)&global_x);

#line 276
{
    unsigned j, mask;

    if (blocksize == 0) {
	blocksize = getbits(16);
	if (blocksize == 0) {
	    
#line 282
{ unsigned int tau_ret_val =  NC; __notify_intrinsic((void*)"decode_c:end", (void *)&global_x); return (tau_ret_val); }

#line 282
 /* end of file */
	}
	read_pt_len(NT, TBIT, 3);
	read_c_len();
	read_pt_len(NP, PBIT, -1);
    }
    blocksize--;
    j = c_table[bitbuf >> (BITBUFSIZ - 12)];
    if (j >= NC) {
	mask = (unsigned) 1 << (BITBUFSIZ - 1 - 12);
	do {
	    if (bitbuf & mask) j = right[j];
	    else               j = left [j];
	    mask >>= 1;
	} while (j >= NC);
    }
    fillbuf((int) c_len[j]);
    
#line 299
{ unsigned int tau_ret_val =  j; __notify_intrinsic((void*)"decode_c:end", (void *)&global_x); return (tau_ret_val); }

#line 299


#line 300

}
	

#line 300
}

local unsigned decode_p()
{

#line 303

__notify_intrinsic((void*)"decode_p:start", (void *)&global_x);

#line 303
{
    unsigned j, mask;

    j = pt_table[bitbuf >> (BITBUFSIZ - 8)];
    if (j >= NP) {
	mask = (unsigned) 1 << (BITBUFSIZ - 1 - 8);
	do {
	    if (bitbuf & mask) j = right[j];
	    else               j = left [j];
	    mask >>= 1;
	} while (j >= NP);
    }
    fillbuf((int) pt_len[j]);
    if (j != 0) j = ((unsigned) 1 << (j - 1)) + getbits((int) (j - 1));
    
#line 317
{ unsigned int tau_ret_val =  j; __notify_intrinsic((void*)"decode_p:end", (void *)&global_x); return (tau_ret_val); }

#line 317


#line 318

}
	

#line 318
}

local void huf_decode_start()
{

#line 321

__notify_intrinsic((void*)"huf_decode_start:start", (void *)&global_x);

#line 321
{
    init_getbits();  blocksize = 0;

#line 323

}
	

#line 323
}

/***********************************************************
        decode.c
***********************************************************/

local int j;    /* remaining bytes to copy */
local int done; /* set at end of input */

local void decode_start()
{

#line 333

__notify_intrinsic((void*)"decode_start:start", (void *)&global_x);

#line 333
{
    huf_decode_start();
    j = 0;
    done = 0;

#line 337

}
	

#line 337
}

/* Decode the input and return the number of decoded bytes put in buffer
 */
local unsigned decode(count, buffer)
    unsigned count;
    uch buffer[];
    /* The calling function must keep the number of
       bytes to be processed.  This function decodes
       either 'count' bytes or 'DICSIZ' bytes, whichever
       is smaller, into the array 'buffer[]' of size
       'DICSIZ' or more.
       Call decode_start() once for each new file
       before calling this function.
     */
{

#line 352

__notify_intrinsic((void*)"decode:start", (void *)&global_x);

#line 352
{
    local unsigned i;
    unsigned r, c;

    r = 0;
    while (--j >= 0) {
	buffer[r] = buffer[i];
	i = (i + 1) & (DICSIZ - 1);
	if (++r == count) 
#line 360
{ unsigned int tau_ret_val =  r; __notify_intrinsic((void*)"decode:end", (void *)&global_x); return (tau_ret_val); }

#line 360

    }
    for ( ; ; ) {
	c = decode_c();
	if (c == NC) {
	    done = 1;
	    
#line 366
{ unsigned int tau_ret_val =  r; __notify_intrinsic((void*)"decode:end", (void *)&global_x); return (tau_ret_val); }

#line 366

	}
	if (c <= UCHAR_MAX) {
	    buffer[r] = c;
	    if (++r == count) 
#line 370
{ unsigned int tau_ret_val =  r; __notify_intrinsic((void*)"decode:end", (void *)&global_x); return (tau_ret_val); }

#line 370

	} else {
	    j = c - (UCHAR_MAX + 1 - THRESHOLD);
	    i = (r - decode_p() - 1) & (DICSIZ - 1);
	    while (--j >= 0) {
		buffer[r] = buffer[i];
		i = (i + 1) & (DICSIZ - 1);
		if (++r == count) 
#line 377
{ unsigned int tau_ret_val =  r; __notify_intrinsic((void*)"decode:end", (void *)&global_x); return (tau_ret_val); }

#line 377

	    }
	}
    }

#line 381

}
	

#line 381
}


/* ===========================================================================
 * Unlzh in to out. Return OK or ERROR.
 */
int unlzh(in, out)
    int in;
    int out;
{

#line 390

__notify_intrinsic((void*)"unlzh:start", (void *)&global_x);

#line 390
{
    unsigned n;
    ifd = in;
    ofd = out;

    decode_start();
    while (!done) {
	n = decode((unsigned) DICSIZ, window);
	if (!test && n > 0) {
	    write_buf(out, (char*)window, n);
	}
    }
    
#line 402
{ int tau_ret_val =  OK; __notify_intrinsic((void*)"unlzh:end", (void *)&global_x); return (tau_ret_val); }

#line 402


#line 403

}
	

#line 403
}
