
#line 1 "./instrumented/./bits.c"
/* bits.c -- output variable-length bit strings
 * Copyright (C) 1992-1993 Jean-loup Gailly
 * This is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License, see the file COPYING.
 */


/*
 *  PURPOSE
 *
 *      Output variable-length bit strings. Compression can be done
 *      to a file or to memory. (The latter is not supported in this version.)
 *
 *  DISCUSSION
 *
 *      The PKZIP "deflate" file format interprets compressed file data
 *      as a sequence of bits.  Multi-bit strings in the file may cross
 *      byte boundaries without restriction.
 *
 *      The first bit of each byte is the low-order bit.
 *
 *      The routines in this file allow a variable-length bit value to
 *      be output right-to-left (useful for literal values). For
 *      left-to-right output (useful for code strings from the tree routines),
 *      the bits must have been reversed first with bi_reverse().
 *
 *      For in-memory compression, the compressed bit stream goes directly
 *      into the requested output buffer. The input data is read in blocks
 *      by the mem_read() function. The buffer is limited to 64K on 16 bit
 *      machines.
 *
 *  INTERFACE
 *
 *      void bi_init (FILE *zipfile)
 *          Initialize the bit string routines.
 *
 *      void send_bits (int value, int length)
 *          Write out a bit string, taking the source bits right to
 *          left.
 *
 *      int bi_reverse (int value, int length)
 *          Reverse the bits of a bit string, taking the source bits left to
 *          right and emitting them right to left.
 *
 *      void bi_windup (void)
 *          Write out any remaining bits in an incomplete byte.
 *
 *      void copy_block(char *buf, unsigned len, int header)
 *          Copy a stored block to the zip file, storing first the length and
 *          its one's complement if requested.
 *
 */

#include "tailor.h"
#include "gzip.h"
#include "crypt.h"

#ifdef DEBUG
#  include <stdio.h>
#endif

#ifdef RCSID
static char rcsid[] = "$Id: bits.c,v 0.9 1993/06/11 10:16:58 jloup Exp $";
#endif

/* ===========================================================================
 * Local data used by the "bit string" routines.
 */

int global_x;

local file_t zfile; /* output gzip file */

local unsigned short bi_buf;
/* Output buffer. bits are inserted starting at the bottom (least significant
 * bits).
 */

#define Buf_size (8 * 2*sizeof(char))
/* Number of bits used within bi_buf. (bi_buf might be implemented on
 * more than 16 bits on some systems.)
 */

local int bi_valid;
/* Number of valid bits in bi_buf.  All bits above the last valid bit
 * are always zero.
 */

int (*read_buf) OF((char *buf, unsigned size));
/* Current input function. Set to mem_read for in-memory compression */

#ifdef DEBUG
  ulg bits_sent;   /* bit length of the compressed data */
#endif

/* ===========================================================================
 * Initialize the bit string routines.
 */
void bi_init (zipfile)
    file_t zipfile; /* output zip file, NO_FILE for in-memory compression */
{

#line 101

__notify_intrinsic((void*)"bi_init:start", (void *)&global_x);

#line 101
{
    zfile  = zipfile;
    bi_buf = 0;
    bi_valid = 0;
#ifdef DEBUG
    bits_sent = 0L;
#endif

    /* Set the defaults for file compression. They are set by memcompress
     * for in-memory compression.
     */
    if (zfile != NO_FILE) {
	read_buf  = file_read;
    }

    
#line 116
{ __notify_intrinsic((void*)"bi_init:end", (void *)&global_x); return; }

#line 116


#line 117

}
	

#line 117
}

/* ===========================================================================
 * Send a value on a given number of bits.
 * IN assertion: length <= 16 and value fits in length bits.
 */
void send_bits(value, length)
    int value;  /* value to send */
    int length; /* number of bits */
{

#line 126

__notify_intrinsic((void*)"send_bits:start", (void *)&global_x);

#line 126
{
#ifdef DEBUG
    Tracev((stderr," l %2d v %4x ", length, value));
    Assert(length > 0 && length <= 15, "invalid length");
    bits_sent += (ulg)length;
#endif
    /* If not enough room in bi_buf, use (valid) bits from bi_buf and
     * (16 - bi_valid) bits from value, leaving (width - (16-bi_valid))
     * unused bits in value.
     */
    if (bi_valid > (int)Buf_size - length) {
        bi_buf |= (value << bi_valid);
        put_short(bi_buf);
        bi_buf = (ush)value >> (Buf_size - bi_valid);
        bi_valid += length - Buf_size;
    } else {
        bi_buf |= value << bi_valid;
        bi_valid += length;
    }
    
#line 145
{ __notify_intrinsic((void*)"send_bits:end", (void *)&global_x); return; }

#line 145


#line 146

}
	

#line 146
}

/* ===========================================================================
 * Reverse the first len bits of a code, using straightforward code (a faster
 * method would use a table)
 * IN assertion: 1 <= len <= 15
 */
unsigned bi_reverse(code, len)
    unsigned code; /* the value to invert */
    int len;       /* its bit length */
{

#line 156

__notify_intrinsic((void*)"bi_reverse:start", (void *)&global_x);

#line 156
{
    register unsigned res = 0;
    do {
        res |= code & 1;
        code >>= 1, res <<= 1;
    } while (--len > 0);
    
#line 162
{ unsigned int tau_ret_val =  res >> 1; __notify_intrinsic((void*)"bi_reverse:end", (void *)&global_x); return (tau_ret_val); }

#line 162


#line 163

}
	

#line 163
}

/* ===========================================================================
 * Write out any remaining bits in an incomplete byte.
 */
void bi_windup()
{

#line 169

__notify_intrinsic((void*)"bi_windup:start", (void *)&global_x);

#line 169
{
    if (bi_valid > 8) {
        put_short(bi_buf);
    } else if (bi_valid > 0) {
        put_byte(bi_buf);
    }
    bi_buf = 0;
    bi_valid = 0;
#ifdef DEBUG
    bits_sent = (bits_sent+7) & ~7;
#endif
   
#line 180
{ __notify_intrinsic((void*)"bi_windup:end", (void *)&global_x); return; }

#line 180


#line 181

}
	

#line 181
}

/* ===========================================================================
 * Copy a stored block to the zip file, storing first the length and its
 * one's complement if requested.
 */
void copy_block(buf, len, header)
    char     *buf;    /* the input data */
    unsigned len;     /* its length */
    int      header;  /* true if block header must be written */
{

#line 191

__notify_intrinsic((void*)"copy_block:start", (void *)&global_x);

#line 191
{
    bi_windup();              /* align on byte boundary */

    if (header) {
        put_short((ush)len);   
        put_short((ush)~len);
#ifdef DEBUG
        bits_sent += 2*16;
#endif
    }
#ifdef DEBUG
    bits_sent += (ulg)len<<3;
#endif
    while (len--) {
#ifdef CRYPT
        int t;
	if (key) zencode(*buf, t);
#endif
	put_byte(*buf++);
    }
    
#line 211
{ __notify_intrinsic((void*)"copy_block:end", (void *)&global_x); return; }

#line 211


#line 212

}
	

#line 212
}
