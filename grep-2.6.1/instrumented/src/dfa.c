
#line 1 "./instrumented/./src/dfa.c"

#line 1 "dfa.c"
/* dfa.c - deterministic extended regexp routines for GNU
   Copyright (C) 1988, 1998, 2000, 2002, 2004, 2005, 2007-2010 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc.,
   51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA */

/* Written June, 1988 by Mike Haertel
   Modified July, 1988 by Arthur David Olson to assist BMG speedups  */

#include "config.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <locale.h>

#ifndef isgraph
#define isgraph(C) (isprint(C) && !isspace(C))
#endif

#if defined (STDC_HEADERS) || (!defined (isascii) && !defined (HAVE_ISASCII))
#define ISALPHA(C) isalpha(C)
#define ISUPPER(C) isupper(C)
#define ISLOWER(C) islower(C)
#define ISDIGIT(C) isdigit(C)
#define ISXDIGIT(C) isxdigit(C)
#define ISSPACE(C) isspace(C)
#define ISPUNCT(C) ispunct(C)
#define ISALNUM(C) isalnum(C)
#define ISPRINT(C) isprint(C)
#define ISGRAPH(C) isgraph(C)
#define ISCNTRL(C) iscntrl(C)
#else
#define ISALPHA(C) (isascii(C) && isalpha(C))
#define ISUPPER(C) (isascii(C) && isupper(C))
#define ISLOWER(C) (isascii(C) && islower(C))
#define ISDIGIT(C) (isascii(C) && isdigit(C))
#define ISXDIGIT(C) (isascii(C) && isxdigit(C))
#define ISSPACE(C) (isascii(C) && isspace(C))
#define ISPUNCT(C) (isascii(C) && ispunct(C))
#define ISALNUM(C) (isascii(C) && isalnum(C))
#define ISPRINT(C) (isascii(C) && isprint(C))
#define ISGRAPH(C) (isascii(C) && isgraph(C))
#define ISCNTRL(C) (isascii(C) && iscntrl(C))
#endif

/* ISASCIIDIGIT differs from ISDIGIT, as follows:
   - Its arg may be any int or unsigned int; it need not be an unsigned char.
   - It's guaranteed to evaluate its argument exactly once.
   - It's typically faster.
   Posix 1003.2-1992 section 2.5.2.1 page 50 lines 1556-1558 says that
   only '0' through '9' are digits.  Prefer ISASCIIDIGIT to ISDIGIT unless
   it's important to use the locale's definition of `digit' even when the
   host does not conform to Posix.  */
#define ISASCIIDIGIT(c) ((unsigned) (c) - '0' <= 9)

/* gettext.h ensures that we don't use gettext if ENABLE_NLS is not defined */
#include "../lib/gettext.h"
#define _(str) gettext (str)

#include "mbsupport.h"  /* defines MBS_SUPPORT if appropriate */
#ifdef MBS_SUPPORT
/* We can handle multibyte strings. */
# include <wchar.h>
# include <wctype.h>
# include <langinfo.h>
#endif

#include "../lib/regex.h"
#include "dfa.h"
#include "../lib/hard-locale.h"
#include "../lib/xalloc.h"

/* HPUX, define those as macros in sys/param.h */
#ifdef setbit
# undef setbit
#endif
#ifdef clrbit
# undef clrbit
#endif

static void dfamust (struct dfa *dfa);
static void regexp (int toplevel);

int global_x;

#define CALLOC(p, t, n) ((p) = xcalloc((size_t)(n), sizeof (t)))
#define MALLOC(p, t, n) ((p) = xmalloc((n) * sizeof (t)))
#define REALLOC(p, t, n) ((p) = xrealloc((p), (n) * sizeof (t)))

/* Reallocate an array of type t if nalloc is too small for index. */
#define REALLOC_IF_NECESSARY(p, t, nalloc, index) \
  if ((index) >= (nalloc))			  \
    {						  \
      do					  \
	(nalloc) *= 2;				  \
      while ((index) >= (nalloc));		  \
      REALLOC(p, t, nalloc);			  \
    }

#ifdef DEBUG

static void
prtok (token t)
{
  char const *s;

  if (t < 0)
    fprintf(stderr, "END");
  else if (t < NOTCHAR)
    fprintf(stderr, "%c", t);
  else
    {
      switch (t)
	{
	case EMPTY: s = "EMPTY"; break;
	case BACKREF: s = "BACKREF"; break;
	case BEGLINE: s = "BEGLINE"; break;
	case ENDLINE: s = "ENDLINE"; break;
	case BEGWORD: s = "BEGWORD"; break;
	case ENDWORD: s = "ENDWORD"; break;
	case LIMWORD: s = "LIMWORD"; break;
	case NOTLIMWORD: s = "NOTLIMWORD"; break;
	case QMARK: s = "QMARK"; break;
	case STAR: s = "STAR"; break;
	case PLUS: s = "PLUS"; break;
	case CAT: s = "CAT"; break;
	case OR: s = "OR"; break;
	case ORTOP: s = "ORTOP"; break;
	case LPAREN: s = "LPAREN"; break;
	case RPAREN: s = "RPAREN"; break;
#ifdef MBS_SUPPORT
	case ANYCHAR: s = "ANYCHAR"; break;
	case MBCSET: s = "MBCSET"; break;
#endif /* MBS_SUPPORT */
	default: s = "CSET"; break;
	}
      fprintf(stderr, "%s", s);
    }
}
#endif /* DEBUG */

/* Stuff pertaining to charclasses. */

static int
tstbit (unsigned int b, charclass c)
{

#line 166

__notify_intrinsic((void*)"int tstbit(unsigned int, int *) C_start", (void *)&global_x);

#line 166
{

#line 164

__notify_intrinsic((void*)"int tstbit(unsigned int, int *) C_start", (void *)&global_x);

#line 164
{
  
#line 165
{ int tau_ret_val =  c[b / INTBITS] & 1 << b % INTBITS; __notify_intrinsic((void*)"int tstbit(unsigned int, int *) C_end", (void *)&global_x); 
#line 176
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int tstbit(unsigned int, int *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 176
 }

#line 165


#line 166

}
	

#line 166

#line 187

}
	

#line 187
}

static void
setbit (unsigned int b, charclass c)
{

#line 191

__notify_intrinsic((void*)"void setbit(unsigned int, int *) C_start", (void *)&global_x);

#line 191
{

#line 170

__notify_intrinsic((void*)"void setbit(unsigned int, int *) C_start", (void *)&global_x);

#line 170
{
  c[b / INTBITS] |= 1 << b % INTBITS;

#line 172

}
	

#line 172

#line 207

}
	

#line 207
}

static void
clrbit (unsigned int b, charclass c)
{

#line 211

__notify_intrinsic((void*)"void clrbit(unsigned int, int *) C_start", (void *)&global_x);

#line 211
{

#line 176

__notify_intrinsic((void*)"void clrbit(unsigned int, int *) C_start", (void *)&global_x);

#line 176
{
  c[b / INTBITS] &= ~(1 << b % INTBITS);

#line 178

}
	

#line 178

#line 227

}
	

#line 227
}

static void
copyset (charclass src, charclass dst)
{

#line 231

__notify_intrinsic((void*)"void copyset(int *, int *) C_start", (void *)&global_x);

#line 231
{

#line 182

__notify_intrinsic((void*)"void copyset(int *, int *) C_start", (void *)&global_x);

#line 182
{
  memcpy (dst, src, sizeof (charclass));

#line 184

}
	

#line 184

#line 247

}
	

#line 247
}

static void
zeroset (charclass s)
{

#line 251

__notify_intrinsic((void*)"void zeroset(int *) C_start", (void *)&global_x);

#line 251
{

#line 188

__notify_intrinsic((void*)"void zeroset(int *) C_start", (void *)&global_x);

#line 188
{
  memset (s, 0, sizeof (charclass));

#line 190

}
	

#line 190

#line 267

}
	

#line 267
}

static void
notset (charclass s)
{

#line 271

__notify_intrinsic((void*)"void notset(int *) C_start", (void *)&global_x);

#line 271
{

#line 194

__notify_intrinsic((void*)"void notset(int *) C_start", (void *)&global_x);

#line 194
{
  int i;

  for (i = 0; i < CHARCLASS_INTS; ++i)
    s[i] = ~s[i];

#line 199

}
	

#line 199

#line 290

}
	

#line 290
}

static int
equal (charclass s1, charclass s2)
{

#line 294

__notify_intrinsic((void*)"int equal(int *, int *) C_start", (void *)&global_x);

#line 294
{

#line 203

__notify_intrinsic((void*)"int equal(int *, int *) C_start", (void *)&global_x);

#line 203
{
  
#line 204
{ int tau_ret_val =  memcmp (s1, s2, sizeof (charclass)) == 0; __notify_intrinsic((void*)"int equal(int *, int *) C_end", (void *)&global_x); 
#line 304
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int equal(int *, int *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 304
 }

#line 204


#line 205

}
	

#line 205

#line 315

}
	

#line 315
}

/* A pointer to the current dfa is kept here during parsing. */
static struct dfa *dfa;

/* Find the index of charclass s in dfa->charclasses, or allocate a new charclass. */
static int
charclass_index (charclass s)
{

#line 323

__notify_intrinsic((void*)"int charclass_index(int *) C_start", (void *)&global_x);

#line 323
{

#line 213

__notify_intrinsic((void*)"int charclass_index(int *) C_start", (void *)&global_x);

#line 213
{
  int i;

  for (i = 0; i < dfa->cindex; ++i)
    if (equal(s, dfa->charclasses[i]))
      
#line 218
{ int tau_ret_val =  i; __notify_intrinsic((void*)"int charclass_index(int *) C_end", (void *)&global_x); 
#line 337
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int charclass_index(int *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 337
 }

#line 218

  REALLOC_IF_NECESSARY(dfa->charclasses, charclass, dfa->calloc, dfa->cindex);
  ++dfa->cindex;
  copyset(s, dfa->charclasses[i]);
  
#line 222
{ int tau_ret_val =  i; __notify_intrinsic((void*)"int charclass_index(int *) C_end", (void *)&global_x); 
#line 346
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int charclass_index(int *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 346
 }

#line 222


#line 223

}
	

#line 223

#line 357

}
	

#line 357
}

/* Syntax bits controlling the behavior of the lexical analyzer. */
static reg_syntax_t syntax_bits, syntax_bits_set;

/* Flag for case-folding letters into sets. */
static int case_fold;

/* End-of-line byte in data.  */
static unsigned char eolbyte;

/* Entry point to set syntax options. */
void
dfasyntax (reg_syntax_t bits, int fold, unsigned char eol)
{

#line 371

__notify_intrinsic((void*)"void dfasyntax(reg_syntax_t, int, unsigned char) C_start", (void *)&global_x);

#line 371
{

#line 237

__notify_intrinsic((void*)"void dfasyntax(reg_syntax_t, int, unsigned char) C_start", (void *)&global_x);

#line 237
{
  syntax_bits_set = 1;
  syntax_bits = bits;
  case_fold = fold;
  eolbyte = eol;

#line 242

}
	

#line 242

#line 390

}
	

#line 390
}

/* Like setbit, but if case is folded, set both cases of a letter.
   For MB_CUR_MAX > 1, one or both of the two cases may not be set,
   so the resulting charset may only be used as an optimization.  */
static void
setbit_case_fold (
#ifdef MBS_SUPPORT
                  wint_t b,
#else
                  unsigned int b,
#endif
                  charclass c)
{

#line 403

__notify_intrinsic((void*)"void setbit_case_fold(wint_t, int *) C_start", (void *)&global_x);

#line 403
{

#line 255

__notify_intrinsic((void*)"void setbit_case_fold(wint_t, int *) C_start", (void *)&global_x);

#line 255
{
  if (case_fold)
    {
#ifdef MBS_SUPPORT
      if (MB_CUR_MAX > 1)
        {
          wint_t b1 = iswupper(b) ? towlower(b) : b;
          wint_t b2 = iswlower(b) ? towupper(b) : b;
          if (wctob ((unsigned char)b1) == b1)
            setbit (b1, c);
          if (b2 != b1 && wctob ((unsigned char)b2) == b2)
            setbit (b2, c);
        }
      else
#endif
        {
          unsigned char b1 = ISUPPER(b) ? tolower(b) : b;
          unsigned char b2 = ISLOWER(b) ? toupper(b) : b;
	  setbit (b1, c);
          if (b2 != b1)
            setbit (b2, c);
        }
    }
  else
    {
#ifdef MBS_SUPPORT
      if (wctob ((unsigned char)b) == b)
#endif
        setbit (b, c);
    }

#line 285

}
	

#line 285

#line 447

}
	

#line 447
}


/* UTF-8 encoding allows some optimizations that we can't otherwise
   assume in a multibyte encoding. */
static inline int
using_utf8 (void)
{
  static int utf8 = -1;
  if (utf8 == -1)
    {
#if defined HAVE_LANGINFO_CODESET && defined MBS_SUPPORT
      utf8 = (strcmp (nl_langinfo (CODESET), "UTF-8") == 0);
#else
      utf8 = 0;
#endif
    }

  return utf8;
}

/* Lexical analyzer.  All the dross that deals with the obnoxious
   GNU Regex syntax bits is located here.  The poor, suffering
   reader is referred to the GNU Regex documentation for the
   meaning of the @#%!@#%^!@ syntax bits. */

static char const *lexptr;	/* Pointer to next input character. */
static int lexleft;		/* Number of characters remaining. */
static token lasttok;		/* Previous token returned; initially END. */
static int laststart;		/* True if we're separated from beginning or (, |
				   only by zero-width characters. */
static int parens;		/* Count of outstanding left parens. */
static int minrep, maxrep;	/* Repeat counts for {m,n}. */
static int hard_LC_COLLATE;	/* Nonzero if LC_COLLATE is hard.  */

static int cur_mb_len = 1;	/* Length of the multibyte representation of
				   wctok.  */
#ifdef MBS_SUPPORT
/* These variables are used only if (MB_CUR_MAX > 1).  */
static mbstate_t mbs;		/* Mbstate for mbrlen().  */
static wchar_t wctok;		/* Wide character representation of the current
				   multibyte character.  */
static unsigned char *mblen_buf;/* Correspond to the input buffer in dfaexec().
				   Each element store the amount of remain
				   byte of corresponding multibyte character
				   in the input string.  A element's value
				   is 0 if corresponding character is a
				   single byte chracter.
				   e.g. input : 'a', <mb(0)>, <mb(1)>, <mb(2)>
				    mblen_buf :   0,       3,       2,       1
				*/
static wchar_t *inputwcs;	/* Wide character representation of input
				   string in dfaexec().
				   The length of this array is same as
				   the length of input string(char array).
				   inputstring[i] is a single-byte char,
				   or 1st byte of a multibyte char.
				   And inputwcs[i] is the codepoint.  */
static unsigned char const *buf_begin;	/* reference to begin in dfaexec().  */
static unsigned char const *buf_end;	/* reference to end in dfaexec().  */
#endif /* MBS_SUPPORT  */


#ifdef MBS_SUPPORT
/* Note that characters become unsigned here. */
# define FETCH_WC(c, wc, eoferr)		\
  do {						\
    if (! lexleft)				\
      {						\
        if ((eoferr) != 0)			\
	  dfaerror (eoferr);			\
        else					\
	  return lasttok = END;			\
      }						\
    else					\
      {						\
        wchar_t _wc;				\
        cur_mb_len = mbrtowc(&_wc, lexptr, lexleft, &mbs); \
        if (cur_mb_len <= 0)			\
          {					\
            cur_mb_len = 1;			\
            --lexleft;				\
            (wc) = (c) = (unsigned char) *lexptr++; \
          }					\
        else					\
          {					\
            lexptr += cur_mb_len;		\
            lexleft -= cur_mb_len;		\
            (wc) = _wc;				\
            (c) = wctob(wc);			\
          }					\
      }						\
  } while(0)

# define FETCH(c, eoferr)			\
  do {						\
    wint_t wc;					\
    FETCH_WC(c, wc, eoferr);			\
  } while(0)

#else
/* Note that characters become unsigned here. */
# define FETCH(c, eoferr)	      \
  do {				      \
    if (! lexleft)		      \
      {				      \
	if ((eoferr) != 0)	      \
	  dfaerror (eoferr);	      \
	else			      \
	  return lasttok = END;	      \
      }				      \
    (c) = (unsigned char) *lexptr++;  \
    --lexleft;			      \
  } while(0)

# define FETCH_WC(c, unused, eoferr) FETCH (c, eoferr)

#endif /* MBS_SUPPORT */

static int
in_coll_range (char ch, char from, char to)
{

#line 568

__notify_intrinsic((void*)"int in_coll_range(char, char, char) C_start", (void *)&global_x);

#line 568
{

#line 406

__notify_intrinsic((void*)"int in_coll_range(char, char, char) C_start", (void *)&global_x);

#line 406
{
  char c[6] = { from, 0, ch, 0, to, 0 };
  
#line 408
{ int tau_ret_val =  strcoll (&c[0], &c[2]) <= 0 && strcoll (&c[2], &c[4]) <= 0; __notify_intrinsic((void*)"int in_coll_range(char, char, char) C_end", (void *)&global_x); 
#line 579
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int in_coll_range(char, char, char) C_end", (void *)&global_x); return (tau_ret_val); }

#line 579
 }

#line 408


#line 409

}
	

#line 409

#line 590

}
	

#line 590
}

static int is_alpha(int c) {

#line 592

__notify_intrinsic((void*)"int is_alpha(int) C_start", (void *)&global_x);

#line 592
{

#line 411

__notify_intrinsic((void*)"int is_alpha(int) C_start", (void *)&global_x);

#line 411
{ 

#line 411
{ int tau_ret_val =  ISALPHA(c); __notify_intrinsic((void*)"int is_alpha(int) C_end", (void *)&global_x); 
#line 602
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_alpha(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 602
 }

#line 411
 

#line 411

}
	

#line 411

#line 613

}
	

#line 613
}
static int is_upper(int c) {

#line 614

__notify_intrinsic((void*)"int is_upper(int) C_start", (void *)&global_x);

#line 614
{

#line 412

__notify_intrinsic((void*)"int is_upper(int) C_start", (void *)&global_x);

#line 412
{ 

#line 412
{ int tau_ret_val =  ISUPPER(c); __notify_intrinsic((void*)"int is_upper(int) C_end", (void *)&global_x); 
#line 624
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_upper(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 624
 }

#line 412
 

#line 412

}
	

#line 412

#line 635

}
	

#line 635
}
static int is_lower(int c) {

#line 636

__notify_intrinsic((void*)"int is_lower(int) C_start", (void *)&global_x);

#line 636
{

#line 413

__notify_intrinsic((void*)"int is_lower(int) C_start", (void *)&global_x);

#line 413
{ 

#line 413
{ int tau_ret_val =  ISLOWER(c); __notify_intrinsic((void*)"int is_lower(int) C_end", (void *)&global_x); 
#line 646
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_lower(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 646
 }

#line 413
 

#line 413

}
	

#line 413

#line 657

}
	

#line 657
}
static int is_digit(int c) {

#line 658

__notify_intrinsic((void*)"int is_digit(int) C_start", (void *)&global_x);

#line 658
{

#line 414

__notify_intrinsic((void*)"int is_digit(int) C_start", (void *)&global_x);

#line 414
{ 

#line 414
{ int tau_ret_val =  ISDIGIT(c); __notify_intrinsic((void*)"int is_digit(int) C_end", (void *)&global_x); 
#line 668
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_digit(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 668
 }

#line 414
 

#line 414

}
	

#line 414

#line 679

}
	

#line 679
}
static int is_xdigit(int c) {

#line 680

__notify_intrinsic((void*)"int is_xdigit(int) C_start", (void *)&global_x);

#line 680
{

#line 415

__notify_intrinsic((void*)"int is_xdigit(int) C_start", (void *)&global_x);

#line 415
{ 

#line 415
{ int tau_ret_val =  ISXDIGIT(c); __notify_intrinsic((void*)"int is_xdigit(int) C_end", (void *)&global_x); 
#line 690
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_xdigit(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 690
 }

#line 415
 

#line 415

}
	

#line 415

#line 701

}
	

#line 701
}
static int is_space(int c) {

#line 702

__notify_intrinsic((void*)"int is_space(int) C_start", (void *)&global_x);

#line 702
{

#line 416

__notify_intrinsic((void*)"int is_space(int) C_start", (void *)&global_x);

#line 416
{ 

#line 416
{ int tau_ret_val =  ISSPACE(c); __notify_intrinsic((void*)"int is_space(int) C_end", (void *)&global_x); 
#line 712
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_space(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 712
 }

#line 416
 

#line 416

}
	

#line 416

#line 723

}
	

#line 723
}
static int is_punct(int c) {

#line 724

__notify_intrinsic((void*)"int is_punct(int) C_start", (void *)&global_x);

#line 724
{

#line 417

__notify_intrinsic((void*)"int is_punct(int) C_start", (void *)&global_x);

#line 417
{ 

#line 417
{ int tau_ret_val =  ISPUNCT(c); __notify_intrinsic((void*)"int is_punct(int) C_end", (void *)&global_x); 
#line 734
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_punct(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 734
 }

#line 417
 

#line 417

}
	

#line 417

#line 745

}
	

#line 745
}
static int is_alnum(int c) {

#line 746

__notify_intrinsic((void*)"int is_alnum(int) C_start", (void *)&global_x);

#line 746
{

#line 418

__notify_intrinsic((void*)"int is_alnum(int) C_start", (void *)&global_x);

#line 418
{ 

#line 418
{ int tau_ret_val =  ISALNUM(c); __notify_intrinsic((void*)"int is_alnum(int) C_end", (void *)&global_x); 
#line 756
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_alnum(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 756
 }

#line 418
 

#line 418

}
	

#line 418

#line 767

}
	

#line 767
}
static int is_print(int c) {

#line 768

__notify_intrinsic((void*)"int is_print(int) C_start", (void *)&global_x);

#line 768
{

#line 419

__notify_intrinsic((void*)"int is_print(int) C_start", (void *)&global_x);

#line 419
{ 

#line 419
{ int tau_ret_val =  ISPRINT(c); __notify_intrinsic((void*)"int is_print(int) C_end", (void *)&global_x); 
#line 778
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_print(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 778
 }

#line 419
 

#line 419

}
	

#line 419

#line 789

}
	

#line 789
}
static int is_graph(int c) {

#line 790

__notify_intrinsic((void*)"int is_graph(int) C_start", (void *)&global_x);

#line 790
{

#line 420

__notify_intrinsic((void*)"int is_graph(int) C_start", (void *)&global_x);

#line 420
{ 

#line 420
{ int tau_ret_val =  ISGRAPH(c); __notify_intrinsic((void*)"int is_graph(int) C_end", (void *)&global_x); 
#line 800
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_graph(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 800
 }

#line 420
 

#line 420

}
	

#line 420

#line 811

}
	

#line 811
}
static int is_cntrl(int c) {

#line 812

__notify_intrinsic((void*)"int is_cntrl(int) C_start", (void *)&global_x);

#line 812
{

#line 421

__notify_intrinsic((void*)"int is_cntrl(int) C_start", (void *)&global_x);

#line 421
{ 

#line 421
{ int tau_ret_val =  ISCNTRL(c); __notify_intrinsic((void*)"int is_cntrl(int) C_end", (void *)&global_x); 
#line 822
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_cntrl(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 822
 }

#line 421
 

#line 421

}
	

#line 421

#line 833

}
	

#line 833
}

static int
is_blank (int c)
{

#line 837

__notify_intrinsic((void*)"int is_blank(int) C_start", (void *)&global_x);

#line 837
{

#line 425

__notify_intrinsic((void*)"int is_blank(int) C_start", (void *)&global_x);

#line 425
{
   
#line 426
{ int tau_ret_val =  (c == ' ' || c == '\t'); __notify_intrinsic((void*)"int is_blank(int) C_end", (void *)&global_x); 
#line 847
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int is_blank(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 847
 }

#line 426


#line 427

}
	

#line 427

#line 858

}
	

#line 858
}

typedef int predicate (int);

/* The following list maps the names of the Posix named character classes
   to predicate functions that determine whether a given character is in
   the class.  The leading [ has already been eaten by the lexical analyzer. */
static struct {
  const char *name;
  predicate *pred;
} const prednames[] = {
  { "alpha", is_alpha },
  { "upper", is_upper },
  { "lower", is_lower },
  { "digit", is_digit },
  { "xdigit", is_xdigit },
  { "space", is_space },
  { "punct", is_punct },
  { "alnum", is_alnum },
  { "print", is_print },
  { "graph", is_graph },
  { "cntrl", is_cntrl },
  { "blank", is_blank },
  { NULL, NULL }
};

static predicate *
find_pred (const char *str)
{

#line 886

__notify_intrinsic((void*)"predicate *find_pred(const char *) C_start", (void *)&global_x);

#line 886
{

#line 455

__notify_intrinsic((void*)"predicate *find_pred(const char *) C_start", (void *)&global_x);

#line 455
{
  unsigned int i;
  for (i = 0; prednames[i].name; ++i)
    if (!strcmp(str, prednames[i].name))
      break;

  
#line 461
{ predicate * tau_ret_val =  prednames[i].pred; __notify_intrinsic((void*)"predicate *find_pred(const char *) C_end", (void *)&global_x); 
#line 901
{ predicate * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"predicate *find_pred(const char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 901
 }

#line 461


#line 462

}
	

#line 462

#line 912

}
	

#line 912
}

/* Multibyte character handling sub-routine for lex.
   This function  parse a bracket expression and build a struct
   mb_char_classes.  */
static token
parse_bracket_exp (void)
{

#line 919

__notify_intrinsic((void*)"token parse_bracket_exp(void) C_start", (void *)&global_x);

#line 919
{

#line 469

__notify_intrinsic((void*)"token parse_bracket_exp(void) C_start", (void *)&global_x);

#line 469
{
  int invert;
  int c, c1, c2;
  charclass ccl;

#ifdef MBS_SUPPORT
  wint_t wc, wc1, wc2;

  /* Work area to build a mb_char_classes.  */
  struct mb_char_classes *work_mbc;
  int chars_al, range_sts_al, range_ends_al, ch_classes_al,
    equivs_al, coll_elems_al;

  chars_al = 1;
  range_sts_al = range_ends_al = 0;
  ch_classes_al = equivs_al = coll_elems_al = 0;
  if (MB_CUR_MAX > 1)
    {
      REALLOC_IF_NECESSARY(dfa->mbcsets, struct mb_char_classes,
                           dfa->mbcsets_alloc, dfa->nmbcsets + 1);

      /* dfa->multibyte_prop[] hold the index of dfa->mbcsets.
         We will update dfa->multibyte_prop[] in addtok(), because we can't
         decide the index in dfa->tokens[].  */

      /* Initialize work area.  */
      work_mbc = &(dfa->mbcsets[dfa->nmbcsets++]);
      memset (work_mbc, 0, sizeof *work_mbc);
    }
  else
    work_mbc = NULL;
#endif

  memset (ccl, 0, sizeof(ccl));
  FETCH_WC (c, wc, _("unbalanced ["));
  if (c == '^')
    {
      FETCH_WC (c, wc, _("unbalanced ["));
      invert = 1;
    }
  else
    invert = 0;

  do
    {
      c1 = EOF; /* mark c1 is not initialized".  */

      /* Note that if we're looking at some other [:...:] construct,
	 we just treat it as a bunch of ordinary characters.  We can do
	 this because we assume regex has checked for syntax errors before
	 dfa is ever called. */
      if (c == '[' && (syntax_bits & RE_CHAR_CLASSES))
	{
#define BRACKET_BUFFER_SIZE 128
	  char str[BRACKET_BUFFER_SIZE];
	  FETCH_WC (c1, wc1, _("unbalanced ["));

	  /* If pattern contains `[[:', `[[.', or `[[='.  */
	  if (c1 == ':'
#ifdef MBS_SUPPORT
              /* TODO: handle `[[.' and `[[=' also for MB_CUR_MAX == 1.  */
	      || (MB_CUR_MAX > 1 && (c1 == '.' || c1 == '='))
#endif
	      )
	    {
	      int len = 0;
	      for (;;)
		{
		  FETCH_WC (c, wc, _("unbalanced ["));
		  if ((c == c1 && *lexptr == ']') || lexleft == 0)
		    break;
		  if (len < BRACKET_BUFFER_SIZE)
		    str[len++] = c;
		  else
		    /* This is in any case an invalid class name.  */
		    str[0] = '\0';
		}
	      str[len] = '\0';

              /* Fetch bracket.  */
	      FETCH_WC (c, wc, _("unbalanced ["));
	      if (c1 == ':')
		/* build character class.  */
		{
		  char const *class
		    = (case_fold && (!strcmp (str, "upper")
				     || !strcmp (str, "lower"))
				       ? "alpha"
				       : str);
#ifdef MBS_SUPPORT
                  if (MB_CUR_MAX > 1)
                    {
		      /* Store the character class as wctype_t.  */
                      wctype_t wt = wctype (class);

                      if (ch_classes_al == 0)
                        MALLOC(work_mbc->ch_classes, wctype_t, ++ch_classes_al);
                      REALLOC_IF_NECESSARY(work_mbc->ch_classes, wctype_t,
                                           ch_classes_al,
                                           work_mbc->nch_classes + 1);
                      work_mbc->ch_classes[work_mbc->nch_classes++] = wt;
                    }
#endif

                  {
                    predicate *pred = find_pred (class);
                    if (!pred)
                      dfaerror(_("invalid character class"));
                    for (c2 = 0; c2 < NOTCHAR; ++c2)
                      if ((*pred)(c2))
                        setbit_case_fold (c2, ccl);
                  }
                }

#ifdef MBS_SUPPORT
	      else if (c1 == '=' || c1 == '.')
		{
		  char *elem;
		  MALLOC(elem, char, len + 1);
		  strncpy(elem, str, len + 1);

		  if (c1 == '=')
		    /* build equivalent class.  */
		    {
		      if (equivs_al == 0)
			MALLOC(work_mbc->equivs, char*, ++equivs_al);
		      REALLOC_IF_NECESSARY(work_mbc->equivs, char*,
					   equivs_al,
					   work_mbc->nequivs + 1);
		      work_mbc->equivs[work_mbc->nequivs++] = elem;
		    }

		  if (c1 == '.')
		    /* build collating element.  */
		    {
		      if (coll_elems_al == 0)
			MALLOC(work_mbc->coll_elems, char*, ++coll_elems_al);
		      REALLOC_IF_NECESSARY(work_mbc->coll_elems, char*,
					   coll_elems_al,
					   work_mbc->ncoll_elems + 1);
		      work_mbc->coll_elems[work_mbc->ncoll_elems++] = elem;
		    }
		}
#endif

              /* Fetch new lookahead character.  */
	      FETCH_WC (c1, wc1, _("unbalanced ["));
              continue;
	    }

          /* We treat '[' as a normal character here.  c/c1/wc/wc1
             are already set up.  */
	}

      if (c == '\\' && (syntax_bits & RE_BACKSLASH_ESCAPE_IN_LISTS))
        FETCH_WC(c, wc, _("unbalanced ["));

      if (c1 == EOF)
	FETCH_WC(c1, wc1, _("unbalanced ["));

      if (c1 == '-')
	/* build range characters.  */
	{
	  FETCH_WC(c2, wc2, _("unbalanced ["));
	  if (c2 == ']')
	    {
	      /* In the case [x-], the - is an ordinary hyphen,
		 which is left in c1, the lookahead character. */
	      lexptr -= cur_mb_len;
	      lexleft += cur_mb_len;
            }
        }

      if (c1 == '-' && c2 != ']')
        {
          if (c2 == '\\'
              && (syntax_bits & RE_BACKSLASH_ESCAPE_IN_LISTS))
            FETCH_WC(c2, wc2, _("unbalanced ["));

#ifdef MBS_SUPPORT
          if (MB_CUR_MAX > 1)
            {
	      /* When case folding map a range, say [m-z] (or even [M-z])
		 to the pair of ranges, [m-z] [M-Z].  */
	      if (range_sts_al == 0)
                {
                  MALLOC(work_mbc->range_sts, wchar_t, ++range_sts_al);
                  MALLOC(work_mbc->range_ends, wchar_t, ++range_ends_al);
                }
              REALLOC_IF_NECESSARY(work_mbc->range_sts, wchar_t,
                                   range_sts_al, work_mbc->nranges + 1);
              REALLOC_IF_NECESSARY(work_mbc->range_ends, wchar_t,
                                   range_ends_al, work_mbc->nranges + 1);
              work_mbc->range_sts[work_mbc->nranges] =
                case_fold ? towlower(wc) : (wchar_t)wc;
              work_mbc->range_ends[work_mbc->nranges++] =
                case_fold ? towlower(wc2) : (wchar_t)wc2;

#ifndef GREP
              if (case_fold && (iswalpha(wc) || iswalpha(wc2)))
                {
                  REALLOC_IF_NECESSARY(work_mbc->range_sts, wchar_t,
                                       range_sts_al, work_mbc->nranges + 1);
                  work_mbc->range_sts[work_mbc->nranges] = towupper(wc);
                  REALLOC_IF_NECESSARY(work_mbc->range_ends, wchar_t,
                                       range_ends_al, work_mbc->nranges + 1);
                  work_mbc->range_ends[work_mbc->nranges++] = towupper(wc2);
                }
#endif
            }
          else
#endif
            {
              c1 = c;
              if (case_fold)
                {
                  c1 = tolower (c1);
                  c2 = tolower (c2);
                }
              if (!hard_LC_COLLATE)
                for (c = c1; c <= c2; c++)
                  setbit_case_fold (c, ccl);
              else
                for (c = 0; c < NOTCHAR; ++c)
                  if (!(case_fold && ISUPPER (c))
                      && in_coll_range (c, c1, c2))
                    setbit_case_fold (c, ccl);
            }

          FETCH_WC(c1, wc1, _("unbalanced ["));
	  continue;
	}

#ifdef MBS_SUPPORT
      /* Build normal characters.  */
      setbit_case_fold (wc, ccl);
      if (MB_CUR_MAX > 1)
        {
          if (case_fold && iswalpha(wc))
            {
              wc = towlower(wc);
              c = wctob(wc);
              if (c == EOF || (wint_t)c != (wint_t)wc)
                {
                  REALLOC_IF_NECESSARY(work_mbc->chars, wchar_t, chars_al,
                                       work_mbc->nchars + 1);
                  work_mbc->chars[work_mbc->nchars++] = wc;
                }
#ifdef GREP
	      continue;
#else
              wc = towupper(wc);
              c = wctob(wc);
#endif
            }
          if (c == EOF || (wint_t)c != (wint_t)wc)
            {
              REALLOC_IF_NECESSARY(work_mbc->chars, wchar_t, chars_al,
                                   work_mbc->nchars + 1);
              work_mbc->chars[work_mbc->nchars++] = wc;
            }
        }
#else
      setbit_case_fold (c, ccl);
#endif
    }
  while ((
#ifdef MBS_SUPPORT
	 wc = wc1,
#endif
	 (c = c1) != ']'));

#ifdef MBS_SUPPORT
  if (MB_CUR_MAX > 1
      && (!using_utf8()
	  || invert
          || work_mbc->nchars != 0
          || work_mbc->nch_classes != 0
          || work_mbc->nranges != 0
          || work_mbc->nequivs != 0
          || work_mbc->ncoll_elems != 0))
    {
      static charclass zeroclass;
      work_mbc->invert = invert;
      work_mbc->cset = equal(ccl, zeroclass) ? -1 : charclass_index(ccl);
      
#line 754
{ token tau_ret_val =  MBCSET; __notify_intrinsic((void*)"token parse_bracket_exp(void) C_end", (void *)&global_x); 
#line 1213
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token parse_bracket_exp(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1213
 }

#line 754

    }
#endif

  if (invert)
    {
#ifdef MBS_SUPPORT
      assert(MB_CUR_MAX == 1);
#endif
      notset(ccl);
      if (syntax_bits & RE_HAT_LISTS_NOT_NEWLINE)
        clrbit(eolbyte, ccl);
    }

  
#line 768
{ token tau_ret_val =  CSET + charclass_index(ccl); __notify_intrinsic((void*)"token parse_bracket_exp(void) C_end", (void *)&global_x); 
#line 1232
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token parse_bracket_exp(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1232
 }

#line 768


#line 769

}
	

#line 769

#line 1243

}
	

#line 1243
}

/* Return non-zero if C is a `word-constituent' byte; zero otherwise.  */
#define IS_WORD_CONSTITUENT(C) (ISALNUM(C) || (C) == '_')

static token
lex (void)
{

#line 1250

__notify_intrinsic((void*)"token lex(void) C_start", (void *)&global_x);

#line 1250
{

#line 776

__notify_intrinsic((void*)"token lex(void) C_start", (void *)&global_x);

#line 776
{
  unsigned int c, c2;
  int backslash = 0;
  charclass ccl;
  int i;

  /* Basic plan: We fetch a character.  If it's a backslash,
     we set the backslash flag and go through the loop again.
     On the plus side, this avoids having a duplicate of the
     main switch inside the backslash case.  On the minus side,
     it means that just about every case begins with
     "if (backslash) ...".  */
  for (i = 0; i < 2; ++i)
    {
#ifdef MBS_SUPPORT
      if (MB_CUR_MAX > 1)
        {
          FETCH_WC (c, wctok, NULL);
          if ((int)c == EOF)
            goto normal_char;
        }
      else
#endif /* MBS_SUPPORT  */
        FETCH(c, NULL);

      switch (c)
	{
	case '\\':
	  if (backslash)
	    goto normal_char;
	  if (lexleft == 0)
	    dfaerror(_("unfinished \\ escape"));
	  backslash = 1;
	  break;

	case '^':
	  if (backslash)
	    goto normal_char;
	  if (syntax_bits & RE_CONTEXT_INDEP_ANCHORS
	      || lasttok == END
	      || lasttok == LPAREN
	      || lasttok == OR)
	    
#line 818
{ token tau_ret_val =  lasttok = BEGLINE; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1301
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1301
 }

#line 818

	  goto normal_char;

	case '$':
	  if (backslash)
	    goto normal_char;
	  if (syntax_bits & RE_CONTEXT_INDEP_ANCHORS
	      || lexleft == 0
	      || (syntax_bits & RE_NO_BK_PARENS
		  ? lexleft > 0 && *lexptr == ')'
		  : lexleft > 1 && lexptr[0] == '\\' && lexptr[1] == ')')
	      || (syntax_bits & RE_NO_BK_VBAR
		  ? lexleft > 0 && *lexptr == '|'
		  : lexleft > 1 && lexptr[0] == '\\' && lexptr[1] == '|')
	      || ((syntax_bits & RE_NEWLINE_ALT)
	          && lexleft > 0 && *lexptr == '\n'))
	    
#line 834
{ token tau_ret_val =  lasttok = ENDLINE; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1322
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1322
 }

#line 834

	  goto normal_char;

	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  if (backslash && !(syntax_bits & RE_NO_BK_REFS))
	    {
	      laststart = 0;
	      
#line 849
{ token tau_ret_val =  lasttok = BACKREF; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1342
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1342
 }

#line 849

	    }
	  goto normal_char;

	case '`':
	  if (backslash && !(syntax_bits & RE_NO_GNU_OPS))
	    
#line 855
{ token tau_ret_val =  lasttok = BEGLINE; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1353
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1353
 }

#line 855
	/* FIXME: should be beginning of string */
	  goto normal_char;

	case '\'':
	  if (backslash && !(syntax_bits & RE_NO_GNU_OPS))
	    
#line 860
{ token tau_ret_val =  lasttok = ENDLINE; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1363
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1363
 }

#line 860
	/* FIXME: should be end of string */
	  goto normal_char;

	case '<':
	  if (backslash && !(syntax_bits & RE_NO_GNU_OPS))
	    
#line 865
{ token tau_ret_val =  lasttok = BEGWORD; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1373
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1373
 }

#line 865

	  goto normal_char;

	case '>':
	  if (backslash && !(syntax_bits & RE_NO_GNU_OPS))
	    
#line 870
{ token tau_ret_val =  lasttok = ENDWORD; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1383
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1383
 }

#line 870

	  goto normal_char;

	case 'b':
	  if (backslash && !(syntax_bits & RE_NO_GNU_OPS))
	    
#line 875
{ token tau_ret_val =  lasttok = LIMWORD; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1393
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1393
 }

#line 875

	  goto normal_char;

	case 'B':
	  if (backslash && !(syntax_bits & RE_NO_GNU_OPS))
	    
#line 880
{ token tau_ret_val =  lasttok = NOTLIMWORD; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1403
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1403
 }

#line 880

	  goto normal_char;

	case '?':
	  if (syntax_bits & RE_LIMITED_OPS)
	    goto normal_char;
	  if (backslash != ((syntax_bits & RE_BK_PLUS_QM) != 0))
	    goto normal_char;
	  if (!(syntax_bits & RE_CONTEXT_INDEP_OPS) && laststart)
	    goto normal_char;
	  
#line 890
{ token tau_ret_val =  lasttok = QMARK; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1418
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1418
 }

#line 890


	case '*':
	  if (backslash)
	    goto normal_char;
	  if (!(syntax_bits & RE_CONTEXT_INDEP_OPS) && laststart)
	    goto normal_char;
	  
#line 897
{ token tau_ret_val =  lasttok = STAR; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1430
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1430
 }

#line 897


	case '+':
	  if (syntax_bits & RE_LIMITED_OPS)
	    goto normal_char;
	  if (backslash != ((syntax_bits & RE_BK_PLUS_QM) != 0))
	    goto normal_char;
	  if (!(syntax_bits & RE_CONTEXT_INDEP_OPS) && laststart)
	    goto normal_char;
	  
#line 906
{ token tau_ret_val =  lasttok = PLUS; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1444
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1444
 }

#line 906


	case '{':
	  if (!(syntax_bits & RE_INTERVALS))
	    goto normal_char;
	  if (backslash != ((syntax_bits & RE_NO_BK_BRACES) == 0))
	    goto normal_char;
	  if (!(syntax_bits & RE_CONTEXT_INDEP_OPS) && laststart)
	    goto normal_char;

	  if (syntax_bits & RE_NO_BK_BRACES)
	    {
	      /* Scan ahead for a valid interval; if it's not valid,
		 treat it as a literal '{'.  */
	      int lo = -1, hi = -1;
	      char const *p = lexptr;
	      char const *lim = p + lexleft;
	      for (;  p != lim && ISASCIIDIGIT (*p);  p++)
		lo = (lo < 0 ? 0 : lo * 10) + *p - '0';
	      if (p != lim && *p == ',')
		while (++p != lim && ISASCIIDIGIT (*p))
		  hi = (hi < 0 ? 0 : hi * 10) + *p - '0';
	      else
		hi = lo;
	      if (p == lim || *p != '}'
		  || lo < 0 || RE_DUP_MAX < hi || (0 <= hi && hi < lo))
		goto normal_char;
	    }

	  minrep = 0;
	  /* Cases:
	     {M} - exact count
	     {M,} - minimum count, maximum is infinity
	     {M,N} - M through N */
	  FETCH(c, _("unfinished repeat count"));
	  if (ISASCIIDIGIT (c))
	    {
	      minrep = c - '0';
	      for (;;)
		{
		  FETCH(c, _("unfinished repeat count"));
		  if (! ISASCIIDIGIT (c))
		    break;
		  minrep = 10 * minrep + c - '0';
		}
	    }
	  else
	    dfaerror(_("malformed repeat count"));
	  if (c == ',')
	    {
	      FETCH (c, _("unfinished repeat count"));
	      if (! ISASCIIDIGIT (c))
		maxrep = -1;
	      else
		{
		  maxrep = c - '0';
		  for (;;)
		    {
		      FETCH (c, _("unfinished repeat count"));
		      if (! ISASCIIDIGIT (c))
			break;
		      maxrep = 10 * maxrep + c - '0';
		    }
		  if (0 <= maxrep && maxrep < minrep)
		    dfaerror (_("malformed repeat count"));
		}
	    }
	  else
	    maxrep = minrep;
	  if (!(syntax_bits & RE_NO_BK_BRACES))
	    {
	      if (c != '\\')
		dfaerror(_("malformed repeat count"));
	      FETCH(c, _("unfinished repeat count"));
	    }
	  if (c != '}')
	    dfaerror(_("malformed repeat count"));
	  laststart = 0;
#ifdef GAWK
	  dfa->broken = (minrep == maxrep && minrep == 0);
#endif
	  
#line 987
{ token tau_ret_val =  lasttok = REPMN; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1530
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1530
 }

#line 987


	case '|':
	  if (syntax_bits & RE_LIMITED_OPS)
	    goto normal_char;
	  if (backslash != ((syntax_bits & RE_NO_BK_VBAR) == 0))
	    goto normal_char;
	  laststart = 1;
	  
#line 995
{ token tau_ret_val =  lasttok = OR; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1543
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1543
 }

#line 995


	case '\n':
	  if (syntax_bits & RE_LIMITED_OPS
	      || backslash
	      || !(syntax_bits & RE_NEWLINE_ALT))
	    goto normal_char;
	  laststart = 1;
	  
#line 1003
{ token tau_ret_val =  lasttok = OR; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1556
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1556
 }

#line 1003


	case '(':
	  if (backslash != ((syntax_bits & RE_NO_BK_PARENS) == 0))
	    goto normal_char;
	  ++parens;
	  laststart = 1;
	  
#line 1010
{ token tau_ret_val =  lasttok = LPAREN; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1568
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1568
 }

#line 1010


	case ')':
	  if (backslash != ((syntax_bits & RE_NO_BK_PARENS) == 0))
	    goto normal_char;
	  if (parens == 0 && syntax_bits & RE_UNMATCHED_RIGHT_PAREN_ORD)
	    goto normal_char;
	  --parens;
	  laststart = 0;
	  
#line 1019
{ token tau_ret_val =  lasttok = RPAREN; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1582
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1582
 }

#line 1019


	case '.':
	  if (backslash)
	    goto normal_char;
#ifdef MBS_SUPPORT
	  if (MB_CUR_MAX > 1)
	    {
	      /* In multibyte environment period must match with a single
		 character not a byte.  So we use ANYCHAR.  */
	      laststart = 0;
	      
#line 1030
{ token tau_ret_val =  lasttok = ANYCHAR; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1598
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1598
 }

#line 1030

	    }
#endif /* MBS_SUPPORT */
	  zeroset(ccl);
	  notset(ccl);
	  if (!(syntax_bits & RE_DOT_NEWLINE))
	    clrbit(eolbyte, ccl);
	  if (syntax_bits & RE_DOT_NOT_NULL)
	    clrbit('\0', ccl);
	  laststart = 0;
	  
#line 1040
{ token tau_ret_val =  lasttok = CSET + charclass_index(ccl); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1613
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1613
 }

#line 1040


#ifndef GAWK
	case 's':
	case 'S':
	  if (!backslash || (syntax_bits & RE_NO_GNU_OPS))
	    goto normal_char;
	  zeroset(ccl);
	  for (c2 = 0; c2 < NOTCHAR; ++c2)
	    if (ISSPACE(c2))
	      setbit(c2, ccl);
	  if (c == 'S')
	    notset(ccl);
	  laststart = 0;
	  
#line 1054
{ token tau_ret_val =  lasttok = CSET + charclass_index(ccl); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1632
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1632
 }

#line 1054

#endif

	case 'w':
	case 'W':
	  if (!backslash || (syntax_bits & RE_NO_GNU_OPS))
	    goto normal_char;
	  zeroset(ccl);
	  for (c2 = 0; c2 < NOTCHAR; ++c2)
	    if (IS_WORD_CONSTITUENT(c2))
	      setbit(c2, ccl);
	  if (c == 'W')
	    notset(ccl);
	  laststart = 0;
	  
#line 1068
{ token tau_ret_val =  lasttok = CSET + charclass_index(ccl); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1651
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1651
 }

#line 1068


	case '[':
	  if (backslash)
	    goto normal_char;
	  laststart = 0;
	  
#line 1074
{ token tau_ret_val =  lasttok = parse_bracket_exp(); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1662
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1662
 }

#line 1074


	default:
	normal_char:
	  laststart = 0;
#ifdef MBS_SUPPORT
	  /* For multibyte character sets, folding is done in atom.  Always
             return WCHAR.  */
          if (MB_CUR_MAX > 1)
            
#line 1083
{ token tau_ret_val =  lasttok = WCHAR; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1676
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1676
 }

#line 1083

#endif

	  if (case_fold && ISALPHA(c))
	    {
	      zeroset(ccl);
	      setbit_case_fold (c, ccl);
	      
#line 1090
{ token tau_ret_val =  lasttok = CSET + charclass_index(ccl); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1688
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1688
 }

#line 1090

	    }

	  
#line 1093
{ token tau_ret_val =  lasttok = c; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1696
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1696
 }

#line 1093

	}
    }

  /* The above loop should consume at most a backslash
     and some other character. */
  abort();
  
#line 1100
{ token tau_ret_val =  END; __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); 
#line 1708
{ token tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"token lex(void) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1708
 }

#line 1100
	/* keeps pedantic compilers happy. */

#line 1101

}
	

#line 1101

#line 1719

}
	

#line 1719
}

/* Recursive descent parser for regular expressions. */

static token tok;		/* Lookahead token. */
static int depth;		/* Current depth of a hypothetical stack
				   holding deferred productions.  This is
				   used to determine the depth that will be
				   required of the real stack later on in
				   dfaanalyze(). */

static void
addtok_mb (token t, int mbprop)
{

#line 1732

__notify_intrinsic((void*)"void addtok_mb(token, int) C_start", (void *)&global_x);

#line 1732
{

#line 1114

__notify_intrinsic((void*)"void addtok_mb(token, int) C_start", (void *)&global_x);

#line 1114
{
#ifdef MBS_SUPPORT
  if (MB_CUR_MAX > 1)
    {
      REALLOC_IF_NECESSARY(dfa->multibyte_prop, int, dfa->nmultibyte_prop,
			   dfa->tindex);
      dfa->multibyte_prop[dfa->tindex] = mbprop;
    }
#else
  (void) mbprop;
#endif

  REALLOC_IF_NECESSARY(dfa->tokens, token, dfa->talloc, dfa->tindex);
  dfa->tokens[dfa->tindex++] = t;

  switch (t)
    {
    case QMARK:
    case STAR:
    case PLUS:
      break;

    case CAT:
    case OR:
    case ORTOP:
      --depth;
      break;

    default:
      ++dfa->nleaves;
    case EMPTY:
      ++depth;
      break;
    }
  if (depth > dfa->depth)
    dfa->depth = depth;

#line 1150

}
	

#line 1150

#line 1782

}
	

#line 1782
}

/* Add the given token to the parse tree, maintaining the depth count and
   updating the maximum depth if necessary. */
static void
addtok (token t)
{

#line 1788

__notify_intrinsic((void*)"void addtok(token) C_start", (void *)&global_x);

#line 1788
{

#line 1156

__notify_intrinsic((void*)"void addtok(token) C_start", (void *)&global_x);

#line 1156
{
#ifdef MBS_SUPPORT
  if (MB_CUR_MAX > 1 && t == MBCSET)
    addtok_mb (MBCSET, ((dfa->nmbcsets - 1) << 2) + 3);
  else
#endif
    addtok_mb (t, 3);

#line 1163

}
	

#line 1163

#line 1809

}
	

#line 1809
}

#ifdef MBS_SUPPORT
/* We treat a multibyte character as a single atom, so that DFA
   can treat a multibyte character as a single expression.

   e.g. We construct following tree from "<mb1><mb2>".
   <mb1(1st-byte)><mb1(2nd-byte)><CAT><mb1(3rd-byte)><CAT>
   <mb2(1st-byte)><mb2(2nd-byte)><CAT><mb2(3rd-byte)><CAT><CAT> */
static void
addtok_wc (wint_t wc)
{

#line 1820

__notify_intrinsic((void*)"void addtok_wc(wint_t) C_start", (void *)&global_x);

#line 1820
{

#line 1174

__notify_intrinsic((void*)"void addtok_wc(wint_t) C_start", (void *)&global_x);

#line 1174
{
  unsigned char buf[MB_LEN_MAX];
  mbstate_t s;
  int i;
  memset (&s, 0, sizeof(s));
  cur_mb_len = wcrtomb ((char *) buf, wc, &s);
  addtok_mb(buf[0], cur_mb_len == 1 ? 3 : 1);
  for (i = 1; i < cur_mb_len; i++)
    {
      addtok_mb(buf[i], i == cur_mb_len - 1 ? 2 : 0);
      addtok(CAT);
    }

#line 1186

}
	

#line 1186

#line 1846

}
	

#line 1846
}
#endif

/* The grammar understood by the parser is as follows.

   regexp:
     regexp OR branch
     branch

   branch:
     branch closure
     closure

   closure:
     closure QMARK
     closure STAR
     closure PLUS
     closure REPMN
     atom

   atom:
     <normal character>
     <multibyte character>
     ANYCHAR
     MBCSET
     CSET
     BACKREF
     BEGLINE
     ENDLINE
     BEGWORD
     ENDWORD
     LIMWORD
     NOTLIMWORD
     LPAREN regexp RPAREN
     <empty>

   The parser builds a parse tree in postfix form in an array of tokens. */

static void
atom (void)
{

#line 1886

__notify_intrinsic((void*)"void atom(void) C_start", (void *)&global_x);

#line 1886
{

#line 1226

__notify_intrinsic((void*)"void atom(void) C_start", (void *)&global_x);

#line 1226
{
#ifdef MBS_SUPPORT
  if (tok == WCHAR)
    {
      addtok_wc (case_fold ? towlower(wctok) : wctok);
#ifndef GREP
      if (case_fold && iswalpha(wctok))
        {
          addtok_wc (towupper(wctok));
          addtok (OR);
        }
#endif

      tok = lex();
      
#line 1240
{ __notify_intrinsic((void*)"void atom(void) C_end", (void *)&global_x); 
#line 1909
{ __notify_intrinsic((void*)"void atom(void) C_end", (void *)&global_x); return; }

#line 1909
 }

#line 1240

    }
#endif /* MBS_SUPPORT  */

  if ((tok >= 0 && tok < NOTCHAR) || tok >= CSET || tok == BACKREF
      || tok == BEGLINE || tok == ENDLINE || tok == BEGWORD
#ifdef MBS_SUPPORT
      || tok == ANYCHAR || tok == MBCSET /* MB_CUR_MAX > 1 */
#endif /* MBS_SUPPORT */
      || tok == ENDWORD || tok == LIMWORD || tok == NOTLIMWORD)
    {
      addtok(tok);
      tok = lex();
    }
  else if (tok == LPAREN)
    {
      tok = lex();
      regexp(0);
      if (tok != RPAREN)
	dfaerror(_("unbalanced ("));
      tok = lex();
    }
  else
    addtok(EMPTY);

#line 1264

}
	

#line 1264

#line 1943

}
	

#line 1943
}

/* Return the number of tokens in the given subexpression. */
static int
nsubtoks (int tindex)
{

#line 1948

__notify_intrinsic((void*)"int nsubtoks(int) C_start", (void *)&global_x);

#line 1948
{

#line 1269

__notify_intrinsic((void*)"int nsubtoks(int) C_start", (void *)&global_x);

#line 1269
{
  int ntoks1;

  switch (dfa->tokens[tindex - 1])
    {
    default:
      
#line 1275
{ int tau_ret_val =  1; __notify_intrinsic((void*)"int nsubtoks(int) C_end", (void *)&global_x); 
#line 1963
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int nsubtoks(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1963
 }

#line 1275

    case QMARK:
    case STAR:
    case PLUS:
      
#line 1279
{ int tau_ret_val =  1 + nsubtoks(tindex - 1); __notify_intrinsic((void*)"int nsubtoks(int) C_end", (void *)&global_x); 
#line 1972
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int nsubtoks(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1972
 }

#line 1279

    case CAT:
    case OR:
    case ORTOP:
      ntoks1 = nsubtoks(tindex - 1);
      
#line 1284
{ int tau_ret_val =  1 + ntoks1 + nsubtoks(tindex - 1 - ntoks1); __notify_intrinsic((void*)"int nsubtoks(int) C_end", (void *)&global_x); 
#line 1982
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int nsubtoks(int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 1982
 }

#line 1284

    }

#line 1286

}
	

#line 1286

#line 1994

}
	

#line 1994
}

/* Copy the given subexpression to the top of the tree. */
static void
copytoks (int tindex, int ntokens)
{

#line 1999

__notify_intrinsic((void*)"void copytoks(int, int) C_start", (void *)&global_x);

#line 1999
{

#line 1291

__notify_intrinsic((void*)"void copytoks(int, int) C_start", (void *)&global_x);

#line 1291
{
  int i;

  for (i = 0; i < ntokens; ++i)
    {
      addtok(dfa->tokens[tindex + i]);
#ifdef MBS_SUPPORT
      /* Update index into multibyte csets.  */
      if (MB_CUR_MAX > 1 && dfa->tokens[tindex + i] == MBCSET)
	dfa->multibyte_prop[dfa->tindex - 1] = dfa->multibyte_prop[tindex + i];
#endif
    }

#line 1303

}
	

#line 1303

#line 2025

}
	

#line 2025
}

static void
closure (void)
{

#line 2029

__notify_intrinsic((void*)"void closure(void) C_start", (void *)&global_x);

#line 2029
{

#line 1307

__notify_intrinsic((void*)"void closure(void) C_start", (void *)&global_x);

#line 1307
{
  int tindex, ntokens, i;

  atom();
  while (tok == QMARK || tok == STAR || tok == PLUS || tok == REPMN)
    if (tok == REPMN)
      {
	ntokens = nsubtoks(dfa->tindex);
	tindex = dfa->tindex - ntokens;
	if (maxrep < 0)
	  addtok(PLUS);
	if (minrep == 0)
	  addtok(QMARK);
	for (i = 1; i < minrep; ++i)
	  {
	    copytoks(tindex, ntokens);
	    addtok(CAT);
	  }
	for (; i < maxrep; ++i)
	  {
	    copytoks(tindex, ntokens);
	    addtok(QMARK);
	    addtok(CAT);
	  }
	tok = lex();
      }
    else
      {
	addtok(tok);
	tok = lex();
      }

#line 1338

}
	

#line 1338

#line 2074

}
	

#line 2074
}

static void
branch (void)
{

#line 2078

__notify_intrinsic((void*)"void branch(void) C_start", (void *)&global_x);

#line 2078
{

#line 1342

__notify_intrinsic((void*)"void branch(void) C_start", (void *)&global_x);

#line 1342
{
  closure();
  while (tok != RPAREN && tok != OR && tok >= 0)
    {
      closure();
      addtok(CAT);
    }

#line 1349

}
	

#line 1349

#line 2099

}
	

#line 2099
}

static void
regexp (int toplevel)
{

#line 2103

__notify_intrinsic((void*)"void regexp(int) C_start", (void *)&global_x);

#line 2103
{

#line 1353

__notify_intrinsic((void*)"void regexp(int) C_start", (void *)&global_x);

#line 1353
{
  branch();
  while (tok == OR)
    {
      tok = lex();
      branch();
      if (toplevel)
	addtok(ORTOP);
      else
	addtok(OR);
    }

#line 1364

}
	

#line 1364

#line 2128

}
	

#line 2128
}

/* Main entry point for the parser.  S is a string to be parsed, len is the
   length of the string, so s can include NUL characters.  D is a pointer to
   the struct dfa to parse into. */
void
dfaparse (char const *s, size_t len, struct dfa *d)
{

#line 2135

__notify_intrinsic((void*)"void dfaparse(const char *, size_t, struct dfa *) C_start", (void *)&global_x);

#line 2135
{

#line 1371

__notify_intrinsic((void*)"void dfaparse(const char *, size_t, struct dfa *) C_start", (void *)&global_x);

#line 1371
{
  dfa = d;
  lexptr = s;
  lexleft = len;
  lasttok = END;
  laststart = 1;
  parens = 0;
#ifdef LC_COLLATE
  hard_LC_COLLATE = hard_locale (LC_COLLATE);
#endif
#ifdef MBS_SUPPORT
  if (MB_CUR_MAX > 1)
    {
      cur_mb_len = 0;
      memset(&mbs, 0, sizeof(mbstate_t));
    }
#endif /* MBS_SUPPORT  */

  if (! syntax_bits_set)
    dfaerror(_("no syntax specified"));

  tok = lex();
  depth = d->depth;

  regexp(1);

  if (tok != END)
    dfaerror(_("unbalanced )"));

  addtok(END - d->nregexps);
  addtok(CAT);

  if (d->nregexps)
    addtok(ORTOP);

  ++d->nregexps;

#line 1407

}
	

#line 1407

#line 2185

}
	

#line 2185
}

/* Some primitives for operating on sets of positions. */

/* Copy one set to another; the destination must be large enough. */
static void
copy (position_set const *src, position_set *dst)
{

#line 2192

__notify_intrinsic((void*)"void copy(const position_set *, position_set *) C_start", (void *)&global_x);

#line 2192
{

#line 1414

__notify_intrinsic((void*)"void copy(const position_set *, position_set *) C_start", (void *)&global_x);

#line 1414
{
  int i;

  for (i = 0; i < src->nelem; ++i)
    dst->elems[i] = src->elems[i];
  dst->nelem = src->nelem;

#line 1420

}
	

#line 1420

#line 2212

}
	

#line 2212
}

/* Insert a position in a set.  Position sets are maintained in sorted
   order according to index.  If position already exists in the set with
   the same index then their constraints are logically or'd together.
   S->elems must point to an array large enough to hold the resulting set. */
static void
insert (position p, position_set *s)
{

#line 2220

__notify_intrinsic((void*)"void insert(position, position_set *) C_start", (void *)&global_x);

#line 2220
{

#line 1428

__notify_intrinsic((void*)"void insert(position, position_set *) C_start", (void *)&global_x);

#line 1428
{
  int count = s->nelem;
  int lo = 0, hi = count;
  while (lo < hi)
    {
      int mid = ((unsigned) lo + (unsigned) hi) >> 1;
      if (s->elems[mid].index < p.index)
        lo = mid + 1;
      else
        hi = mid;
    }

  if (lo < count && p.index == s->elems[lo].index)
    s->elems[lo].constraint |= p.constraint;
  else
    {
      int i;
      for (i = count; i > lo; i--)
        s->elems[i] = s->elems[i - 1];
      s->elems[lo] = p;
      ++s->nelem;
    }

#line 1450

}
	

#line 1450

#line 2256

}
	

#line 2256
}

/* Merge two sets of positions into a third.  The result is exactly as if
   the positions of both sets were inserted into an initially empty set. */
static void
merge (position_set const *s1, position_set const *s2, position_set *m)
{

#line 2262

__notify_intrinsic((void*)"void merge(const position_set *, const position_set *, position_set *) C_start", (void *)&global_x);

#line 2262
{

#line 1456

__notify_intrinsic((void*)"void merge(const position_set *, const position_set *, position_set *) C_start", (void *)&global_x);

#line 1456
{
  int i = 0, j = 0;

  m->nelem = 0;
  while (i < s1->nelem && j < s2->nelem)
    if (s1->elems[i].index > s2->elems[j].index)
      m->elems[m->nelem++] = s1->elems[i++];
    else if (s1->elems[i].index < s2->elems[j].index)
      m->elems[m->nelem++] = s2->elems[j++];
    else
      {
	m->elems[m->nelem] = s1->elems[i++];
	m->elems[m->nelem++].constraint |= s2->elems[j++].constraint;
      }
  while (i < s1->nelem)
    m->elems[m->nelem++] = s1->elems[i++];
  while (j < s2->nelem)
    m->elems[m->nelem++] = s2->elems[j++];

#line 1474

}
	

#line 1474

#line 2294

}
	

#line 2294
}

/* Delete a position from a set. */
static void
delete (position p, position_set *s)
{

#line 2299

__notify_intrinsic((void*)"void delete(position, position_set *) C_start", (void *)&global_x);

#line 2299
{

#line 1479

__notify_intrinsic((void*)"void delete(position, position_set *) C_start", (void *)&global_x);

#line 1479
{
  int i;

  for (i = 0; i < s->nelem; ++i)
    if (p.index == s->elems[i].index)
      break;
  if (i < s->nelem)
    for (--s->nelem; i < s->nelem; ++i)
      s->elems[i] = s->elems[i + 1];

#line 1488

}
	

#line 1488

#line 2322

}
	

#line 2322
}

/* Find the index of the state corresponding to the given position set with
   the given preceding context, or create a new state if there is no such
   state.  Newline and letter tell whether we got here on a newline or
   letter, respectively. */
static int
state_index (struct dfa *d, position_set const *s, int newline, int letter)
{

#line 2330

__notify_intrinsic((void*)"int state_index(struct dfa *, const position_set *, int, int) C_start", (void *)&global_x);

#line 2330
{

#line 1496

__notify_intrinsic((void*)"int state_index(struct dfa *, const position_set *, int, int) C_start", (void *)&global_x);

#line 1496
{
  int hash = 0;
  int constraint;
  int i, j;

  newline = newline ? 1 : 0;
  letter = letter ? 1 : 0;

  for (i = 0; i < s->nelem; ++i)
    hash ^= s->elems[i].index + s->elems[i].constraint;

  /* Try to find a state that exactly matches the proposed one. */
  for (i = 0; i < d->sindex; ++i)
    {
      if (hash != d->states[i].hash || s->nelem != d->states[i].elems.nelem
	  || newline != d->states[i].newline || letter != d->states[i].letter)
	continue;
      for (j = 0; j < s->nelem; ++j)
	if (s->elems[j].constraint
	    != d->states[i].elems.elems[j].constraint
	    || s->elems[j].index != d->states[i].elems.elems[j].index)
	  break;
      if (j == s->nelem)
	
#line 1519
{ int tau_ret_val =  i; __notify_intrinsic((void*)"int state_index(struct dfa *, const position_set *, int, int) C_end", (void *)&global_x); 
#line 2362
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int state_index(struct dfa *, const position_set *, int, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 2362
 }

#line 1519

    }

  /* We'll have to create a new state. */
  REALLOC_IF_NECESSARY(d->states, dfa_state, d->salloc, d->sindex);
  d->states[i].hash = hash;
  MALLOC(d->states[i].elems.elems, position, s->nelem);
  copy(s, &d->states[i].elems);
  d->states[i].newline = newline;
  d->states[i].letter = letter;
  d->states[i].backref = 0;
  d->states[i].constraint = 0;
  d->states[i].first_end = 0;
#ifdef MBS_SUPPORT
  d->states[i].mbps.nelem = 0;
  d->states[i].mbps.elems = NULL;
#endif
  for (j = 0; j < s->nelem; ++j)
    if (d->tokens[s->elems[j].index] < 0)
      {
	constraint = s->elems[j].constraint;
	if (SUCCEEDS_IN_CONTEXT(constraint, newline, 0, letter, 0)
	    || SUCCEEDS_IN_CONTEXT(constraint, newline, 0, letter, 1)
	    || SUCCEEDS_IN_CONTEXT(constraint, newline, 1, letter, 0)
	    || SUCCEEDS_IN_CONTEXT(constraint, newline, 1, letter, 1))
	  d->states[i].constraint |= constraint;
	if (! d->states[i].first_end)
	  d->states[i].first_end = d->tokens[s->elems[j].index];
      }
    else if (d->tokens[s->elems[j].index] == BACKREF)
      {
	d->states[i].constraint = NO_CONSTRAINT;
	d->states[i].backref = 1;
      }

  ++d->sindex;

  
#line 1556
{ int tau_ret_val =  i; __notify_intrinsic((void*)"int state_index(struct dfa *, const position_set *, int, int) C_end", (void *)&global_x); 
#line 2404
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int state_index(struct dfa *, const position_set *, int, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 2404
 }

#line 1556


#line 1557

}
	

#line 1557

#line 2415

}
	

#line 2415
}

/* Find the epsilon closure of a set of positions.  If any position of the set
   contains a symbol that matches the empty string in some context, replace
   that position with the elements of its follow labeled with an appropriate
   constraint.  Repeat exhaustively until no funny positions are left.
   S->elems must be large enough to hold the result. */
static void
epsclosure (position_set *s, struct dfa const *d)
{

#line 2424

__notify_intrinsic((void*)"void epsclosure(position_set *, const struct dfa *) C_start", (void *)&global_x);

#line 2424
{

#line 1566

__notify_intrinsic((void*)"void epsclosure(position_set *, const struct dfa *) C_start", (void *)&global_x);

#line 1566
{
  int i, j;
  char *visited;	/* array of booleans, enough to use char, not int */
  position p, old;

  CALLOC(visited, char, d->tindex);

  for (i = 0; i < s->nelem; ++i)
    if (d->tokens[s->elems[i].index] >= NOTCHAR
	&& d->tokens[s->elems[i].index] != BACKREF
#ifdef MBS_SUPPORT
	&& d->tokens[s->elems[i].index] != ANYCHAR
	&& d->tokens[s->elems[i].index] != MBCSET
#endif
	&& d->tokens[s->elems[i].index] < CSET)
      {
	old = s->elems[i];
	p.constraint = old.constraint;
	delete(s->elems[i], s);
	if (visited[old.index])
	  {
	    --i;
	    continue;
	  }
	visited[old.index] = 1;
	switch (d->tokens[old.index])
	  {
	  case BEGLINE:
	    p.constraint &= BEGLINE_CONSTRAINT;
	    break;
	  case ENDLINE:
	    p.constraint &= ENDLINE_CONSTRAINT;
	    break;
	  case BEGWORD:
	    p.constraint &= BEGWORD_CONSTRAINT;
	    break;
	  case ENDWORD:
	    p.constraint &= ENDWORD_CONSTRAINT;
	    break;
	  case LIMWORD:
	    p.constraint &= LIMWORD_CONSTRAINT;
	    break;
	  case NOTLIMWORD:
	    p.constraint &= NOTLIMWORD_CONSTRAINT;
	    break;
	  default:
	    break;
	  }
	for (j = 0; j < d->follows[old.index].nelem; ++j)
	  {
	    p.index = d->follows[old.index].elems[j].index;
	    insert(p, s);
	  }
	/* Force rescan to start at the beginning. */
	i = -1;
      }

  free(visited);

#line 1624

}
	

#line 1624

#line 2496

}
	

#line 2496
}

/* Perform bottom-up analysis on the parse tree, computing various functions.
   Note that at this point, we're pretending constructs like \< are real
   characters rather than constraints on what can follow them.

   Nullable:  A node is nullable if it is at the root of a regexp that can
   match the empty string.
   *  EMPTY leaves are nullable.
   * No other leaf is nullable.
   * A QMARK or STAR node is nullable.
   * A PLUS node is nullable if its argument is nullable.
   * A CAT node is nullable if both its arguments are nullable.
   * An OR node is nullable if either argument is nullable.

   Firstpos:  The firstpos of a node is the set of positions (nonempty leaves)
   that could correspond to the first character of a string matching the
   regexp rooted at the given node.
   * EMPTY leaves have empty firstpos.
   * The firstpos of a nonempty leaf is that leaf itself.
   * The firstpos of a QMARK, STAR, or PLUS node is the firstpos of its
     argument.
   * The firstpos of a CAT node is the firstpos of the left argument, union
     the firstpos of the right if the left argument is nullable.
   * The firstpos of an OR node is the union of firstpos of each argument.

   Lastpos:  The lastpos of a node is the set of positions that could
   correspond to the last character of a string matching the regexp at
   the given node.
   * EMPTY leaves have empty lastpos.
   * The lastpos of a nonempty leaf is that leaf itself.
   * The lastpos of a QMARK, STAR, or PLUS node is the lastpos of its
     argument.
   * The lastpos of a CAT node is the lastpos of its right argument, union
     the lastpos of the left if the right argument is nullable.
   * The lastpos of an OR node is the union of the lastpos of each argument.

   Follow:  The follow of a position is the set of positions that could
   correspond to the character following a character matching the node in
   a string matching the regexp.  At this point we consider special symbols
   that match the empty string in some context to be just normal characters.
   Later, if we find that a special symbol is in a follow set, we will
   replace it with the elements of its follow, labeled with an appropriate
   constraint.
   * Every node in the firstpos of the argument of a STAR or PLUS node is in
     the follow of every node in the lastpos.
   * Every node in the firstpos of the second argument of a CAT node is in
     the follow of every node in the lastpos of the first argument.

   Because of the postfix representation of the parse tree, the depth-first
   analysis is conveniently done by a linear scan with the aid of a stack.
   Sets are stored as arrays of the elements, obeying a stack-like allocation
   scheme; the number of elements in each set deeper in the stack can be
   used to determine the address of a particular set's array. */
void
dfaanalyze (struct dfa *d, int searchflag)
{

#line 2552

__notify_intrinsic((void*)"void dfaanalyze(struct dfa *, int) C_start", (void *)&global_x);

#line 2552
{

#line 1680

__notify_intrinsic((void*)"void dfaanalyze(struct dfa *, int) C_start", (void *)&global_x);

#line 1680
{
  int *nullable;		/* Nullable stack. */
  int *nfirstpos;		/* Element count stack for firstpos sets. */
  position *firstpos;		/* Array where firstpos elements are stored. */
  int *nlastpos;		/* Element count stack for lastpos sets. */
  position *lastpos;		/* Array where lastpos elements are stored. */
  int *nalloc;			/* Sizes of arrays allocated to follow sets. */
  position_set tmp;		/* Temporary set for merging sets. */
  position_set merged;		/* Result of merging sets. */
  int wants_newline;		/* True if some position wants newline info. */
  int *o_nullable;
  int *o_nfirst, *o_nlast;
  position *o_firstpos, *o_lastpos;
  int i, j;
  position *pos;

#ifdef DEBUG
  fprintf(stderr, "dfaanalyze:\n");
  for (i = 0; i < d->tindex; ++i)
    {
      fprintf(stderr, " %d:", i);
      prtok(d->tokens[i]);
    }
  putc('\n', stderr);
#endif

  d->searchflag = searchflag;

  MALLOC(nullable, int, d->depth);
  o_nullable = nullable;
  MALLOC(nfirstpos, int, d->depth);
  o_nfirst = nfirstpos;
  MALLOC(firstpos, position, d->nleaves);
  o_firstpos = firstpos, firstpos += d->nleaves;
  MALLOC(nlastpos, int, d->depth);
  o_nlast = nlastpos;
  MALLOC(lastpos, position, d->nleaves);
  o_lastpos = lastpos, lastpos += d->nleaves;
  CALLOC(nalloc, int, d->tindex);
  MALLOC(merged.elems, position, d->nleaves);

  CALLOC(d->follows, position_set, d->tindex);

  for (i = 0; i < d->tindex; ++i)
#ifdef DEBUG
    {				/* Nonsyntactic #ifdef goo... */
#endif
    switch (d->tokens[i])
      {
      case EMPTY:
	/* The empty set is nullable. */
	*nullable++ = 1;

	/* The firstpos and lastpos of the empty leaf are both empty. */
	*nfirstpos++ = *nlastpos++ = 0;
	break;

      case STAR:
      case PLUS:
	/* Every element in the firstpos of the argument is in the follow
	   of every element in the lastpos. */
	tmp.nelem = nfirstpos[-1];
	tmp.elems = firstpos;
	pos = lastpos;
	for (j = 0; j < nlastpos[-1]; ++j)
	  {
	    merge(&tmp, &d->follows[pos[j].index], &merged);
	    REALLOC_IF_NECESSARY(d->follows[pos[j].index].elems, position,
				 nalloc[pos[j].index], merged.nelem - 1);
	    copy(&merged, &d->follows[pos[j].index]);
	  }

      case QMARK:
	/* A QMARK or STAR node is automatically nullable. */
	if (d->tokens[i] != PLUS)
	  nullable[-1] = 1;
	break;

      case CAT:
	/* Every element in the firstpos of the second argument is in the
	   follow of every element in the lastpos of the first argument. */
	tmp.nelem = nfirstpos[-1];
	tmp.elems = firstpos;
	pos = lastpos + nlastpos[-1];
	for (j = 0; j < nlastpos[-2]; ++j)
	  {
	    merge(&tmp, &d->follows[pos[j].index], &merged);
	    REALLOC_IF_NECESSARY(d->follows[pos[j].index].elems, position,
				 nalloc[pos[j].index], merged.nelem - 1);
	    copy(&merged, &d->follows[pos[j].index]);
	  }

	/* The firstpos of a CAT node is the firstpos of the first argument,
	   union that of the second argument if the first is nullable. */
	if (nullable[-2])
	  nfirstpos[-2] += nfirstpos[-1];
	else
	  firstpos += nfirstpos[-1];
	--nfirstpos;

	/* The lastpos of a CAT node is the lastpos of the second argument,
	   union that of the first argument if the second is nullable. */
	if (nullable[-1])
	  nlastpos[-2] += nlastpos[-1];
	else
	  {
	    pos = lastpos + nlastpos[-2];
	    for (j = nlastpos[-1] - 1; j >= 0; --j)
	      pos[j] = lastpos[j];
	    lastpos += nlastpos[-2];
	    nlastpos[-2] = nlastpos[-1];
	  }
	--nlastpos;

	/* A CAT node is nullable if both arguments are nullable. */
	nullable[-2] = nullable[-1] && nullable[-2];
	--nullable;
	break;

      case OR:
      case ORTOP:
	/* The firstpos is the union of the firstpos of each argument. */
	nfirstpos[-2] += nfirstpos[-1];
	--nfirstpos;

	/* The lastpos is the union of the lastpos of each argument. */
	nlastpos[-2] += nlastpos[-1];
	--nlastpos;

	/* An OR node is nullable if either argument is nullable. */
	nullable[-2] = nullable[-1] || nullable[-2];
	--nullable;
	break;

      default:
	/* Anything else is a nonempty position.  (Note that special
	   constructs like \< are treated as nonempty strings here;
	   an "epsilon closure" effectively makes them nullable later.
	   Backreferences have to get a real position so we can detect
	   transitions on them later.  But they are nullable. */
	*nullable++ = d->tokens[i] == BACKREF;

	/* This position is in its own firstpos and lastpos. */
	*nfirstpos++ = *nlastpos++ = 1;
	--firstpos, --lastpos;
	firstpos->index = lastpos->index = i;
	firstpos->constraint = lastpos->constraint = NO_CONSTRAINT;

	/* Allocate the follow set for this position. */
	nalloc[i] = 1;
	MALLOC(d->follows[i].elems, position, nalloc[i]);
	break;
      }
#ifdef DEBUG
    /* ... balance the above nonsyntactic #ifdef goo... */
      fprintf(stderr, "node %d:", i);
      prtok(d->tokens[i]);
      putc('\n', stderr);
      fprintf(stderr, nullable[-1] ? " nullable: yes\n" : " nullable: no\n");
      fprintf(stderr, " firstpos:");
      for (j = nfirstpos[-1] - 1; j >= 0; --j)
	{
	  fprintf(stderr, " %d:", firstpos[j].index);
	  prtok(d->tokens[firstpos[j].index]);
	}
      fprintf(stderr, "\n lastpos:");
      for (j = nlastpos[-1] - 1; j >= 0; --j)
	{
	  fprintf(stderr, " %d:", lastpos[j].index);
	  prtok(d->tokens[lastpos[j].index]);
	}
      putc('\n', stderr);
    }
#endif

  /* For each follow set that is the follow set of a real position, replace
     it with its epsilon closure. */
  for (i = 0; i < d->tindex; ++i)
    if (d->tokens[i] < NOTCHAR || d->tokens[i] == BACKREF
#ifdef MBS_SUPPORT
        || d->tokens[i] == ANYCHAR
        || d->tokens[i] == MBCSET
#endif
	|| d->tokens[i] >= CSET)
      {
#ifdef DEBUG
	fprintf(stderr, "follows(%d:", i);
	prtok(d->tokens[i]);
	fprintf(stderr, "):");
	for (j = d->follows[i].nelem - 1; j >= 0; --j)
	  {
	    fprintf(stderr, " %d:", d->follows[i].elems[j].index);
	    prtok(d->tokens[d->follows[i].elems[j].index]);
	  }
	putc('\n', stderr);
#endif
	copy(&d->follows[i], &merged);
	epsclosure(&merged, d);
	if (d->follows[i].nelem < merged.nelem)
	  REALLOC(d->follows[i].elems, position, merged.nelem);
	copy(&merged, &d->follows[i]);
      }

  /* Get the epsilon closure of the firstpos of the regexp.  The result will
     be the set of positions of state 0. */
  merged.nelem = 0;
  for (i = 0; i < nfirstpos[-1]; ++i)
    insert(firstpos[i], &merged);
  epsclosure(&merged, d);

  /* Check if any of the positions of state 0 will want newline context. */
  wants_newline = 0;
  for (i = 0; i < merged.nelem; ++i)
    if (PREV_NEWLINE_DEPENDENT(merged.elems[i].constraint))
      wants_newline = 1;

  /* Build the initial state. */
  d->salloc = 1;
  d->sindex = 0;
  MALLOC(d->states, dfa_state, d->salloc);
  state_index(d, &merged, wants_newline, 0);

  free(o_nullable);
  free(o_nfirst);
  free(o_firstpos);
  free(o_nlast);
  free(o_lastpos);
  free(nalloc);
  free(merged.elems);

#line 1909

}
	

#line 1909

#line 2795

}
	

#line 2795
}

/* Find, for each character, the transition out of state s of d, and store
   it in the appropriate slot of trans.

   We divide the positions of s into groups (positions can appear in more
   than one group).  Each group is labeled with a set of characters that
   every position in the group matches (taking into account, if necessary,
   preceding context information of s).  For each group, find the union
   of the its elements' follows.  This set is the set of positions of the
   new state.  For each character in the group's label, set the transition
   on this character to be to a state corresponding to the set's positions,
   and its associated backward context information, if necessary.

   If we are building a searching matcher, we include the positions of state
   0 in every state.

   The collection of groups is constructed by building an equivalence-class
   partition of the positions of s.

   For each position, find the set of characters C that it matches.  Eliminate
   any characters from C that fail on grounds of backward context.

   Search through the groups, looking for a group whose label L has nonempty
   intersection with C.  If L - C is nonempty, create a new group labeled
   L - C and having the same positions as the current group, and set L to
   the intersection of L and C.  Insert the position in this group, set
   C = C - L, and resume scanning.

   If after comparing with every group there are characters remaining in C,
   create a new group labeled with the characters of C and insert this
   position in that group. */
void
dfastate (int s, struct dfa *d, int trans[])
{

#line 2829

__notify_intrinsic((void*)"void dfastate(int, struct dfa *, int *) C_start", (void *)&global_x);

#line 2829
{

#line 1943

__notify_intrinsic((void*)"void dfastate(int, struct dfa *, int *) C_start", (void *)&global_x);

#line 1943
{
  position_set grps[NOTCHAR];	/* As many as will ever be needed. */
  charclass labels[NOTCHAR];	/* Labels corresponding to the groups. */
  int ngrps = 0;		/* Number of groups actually used. */
  position pos;			/* Current position being considered. */
  charclass matches;		/* Set of matching characters. */
  int matchesf;			/* True if matches is nonempty. */
  charclass intersect;		/* Intersection with some label set. */
  int intersectf;		/* True if intersect is nonempty. */
  charclass leftovers;		/* Stuff in the label that didn't match. */
  int leftoversf;		/* True if leftovers is nonempty. */
  static charclass letters;	/* Set of characters considered letters. */
  static charclass newline;	/* Set of characters that aren't newline. */
  position_set follows;		/* Union of the follows of some group. */
  position_set tmp;		/* Temporary space for merging sets. */
  int state;			/* New state. */
  int wants_newline;		/* New state wants to know newline context. */
  int state_newline;		/* New state on a newline transition. */
  int wants_letter;		/* New state wants to know letter context. */
  int state_letter;		/* New state on a letter transition. */
  static int initialized;	/* Flag for static initialization. */
#ifdef MBS_SUPPORT
  int next_isnt_1st_byte = 0;	/* Flag if we can't add state0.  */
#endif
  int i, j, k;

  /* Initialize the set of letters, if necessary. */
  if (! initialized)
    {
      initialized = 1;
      for (i = 0; i < NOTCHAR; ++i)
	if (IS_WORD_CONSTITUENT(i))
	  setbit(i, letters);
      setbit(eolbyte, newline);
    }

  zeroset(matches);

  for (i = 0; i < d->states[s].elems.nelem; ++i)
    {
      pos = d->states[s].elems.elems[i];
      if (d->tokens[pos.index] >= 0 && d->tokens[pos.index] < NOTCHAR)
	setbit(d->tokens[pos.index], matches);
      else if (d->tokens[pos.index] >= CSET)
	copyset(d->charclasses[d->tokens[pos.index] - CSET], matches);
#ifdef MBS_SUPPORT
      else if (d->tokens[pos.index] == ANYCHAR
               || d->tokens[pos.index] == MBCSET)
      /* MB_CUR_MAX > 1  */
	{
	  /* ANYCHAR and MBCSET must match with a single character, so we
	     must put it to d->states[s].mbps, which contains the positions
	     which can match with a single character not a byte.  */
	  if (d->states[s].mbps.nelem == 0)
	    {
	      MALLOC(d->states[s].mbps.elems, position,
		     d->states[s].elems.nelem);
	    }
	  insert(pos, &(d->states[s].mbps));
	  continue;
	}
#endif /* MBS_SUPPORT */
      else
	continue;

      /* Some characters may need to be eliminated from matches because
	 they fail in the current context. */
      if (pos.constraint != 0xFF)
	{
	  if (! MATCHES_NEWLINE_CONTEXT(pos.constraint,
					 d->states[s].newline, 1))
	    clrbit(eolbyte, matches);
	  if (! MATCHES_NEWLINE_CONTEXT(pos.constraint,
					 d->states[s].newline, 0))
	    for (j = 0; j < CHARCLASS_INTS; ++j)
	      matches[j] &= newline[j];
	  if (! MATCHES_LETTER_CONTEXT(pos.constraint,
					d->states[s].letter, 1))
	    for (j = 0; j < CHARCLASS_INTS; ++j)
	      matches[j] &= ~letters[j];
	  if (! MATCHES_LETTER_CONTEXT(pos.constraint,
					d->states[s].letter, 0))
	    for (j = 0; j < CHARCLASS_INTS; ++j)
	      matches[j] &= letters[j];

	  /* If there are no characters left, there's no point in going on. */
	  for (j = 0; j < CHARCLASS_INTS && !matches[j]; ++j)
	    continue;
	  if (j == CHARCLASS_INTS)
	    continue;
	}

      for (j = 0; j < ngrps; ++j)
	{
	  /* If matches contains a single character only, and the current
	     group's label doesn't contain that character, go on to the
	     next group. */
	  if (d->tokens[pos.index] >= 0 && d->tokens[pos.index] < NOTCHAR
	      && !tstbit(d->tokens[pos.index], labels[j]))
	    continue;

	  /* Check if this group's label has a nonempty intersection with
	     matches. */
	  intersectf = 0;
	  for (k = 0; k < CHARCLASS_INTS; ++k)
	    (intersect[k] = matches[k] & labels[j][k]) ? (intersectf = 1) : 0;
	  if (! intersectf)
	    continue;

	  /* It does; now find the set differences both ways. */
	  leftoversf = matchesf = 0;
	  for (k = 0; k < CHARCLASS_INTS; ++k)
	    {
	      /* Even an optimizing compiler can't know this for sure. */
	      int match = matches[k], label = labels[j][k];

	      (leftovers[k] = ~match & label) ? (leftoversf = 1) : 0;
	      (matches[k] = match & ~label) ? (matchesf = 1) : 0;
	    }

	  /* If there were leftovers, create a new group labeled with them. */
	  if (leftoversf)
	    {
	      copyset(leftovers, labels[ngrps]);
	      copyset(intersect, labels[j]);
	      MALLOC(grps[ngrps].elems, position, d->nleaves);
	      copy(&grps[j], &grps[ngrps]);
	      ++ngrps;
	    }

	  /* Put the position in the current group.  Note that there is no
	     reason to call insert() here. */
	  grps[j].elems[grps[j].nelem++] = pos;

	  /* If every character matching the current position has been
	     accounted for, we're done. */
	  if (! matchesf)
	    break;
	}

      /* If we've passed the last group, and there are still characters
	 unaccounted for, then we'll have to create a new group. */
      if (j == ngrps)
	{
	  copyset(matches, labels[ngrps]);
	  zeroset(matches);
	  MALLOC(grps[ngrps].elems, position, d->nleaves);
	  grps[ngrps].nelem = 1;
	  grps[ngrps].elems[0] = pos;
	  ++ngrps;
	}
    }

  MALLOC(follows.elems, position, d->nleaves);
  MALLOC(tmp.elems, position, d->nleaves);

  /* If we are a searching matcher, the default transition is to a state
     containing the positions of state 0, otherwise the default transition
     is to fail miserably. */
  if (d->searchflag)
    {
      wants_newline = 0;
      wants_letter = 0;
      for (i = 0; i < d->states[0].elems.nelem; ++i)
	{
	  if (PREV_NEWLINE_DEPENDENT(d->states[0].elems.elems[i].constraint))
	    wants_newline = 1;
	  if (PREV_LETTER_DEPENDENT(d->states[0].elems.elems[i].constraint))
	    wants_letter = 1;
	}
      copy(&d->states[0].elems, &follows);
      state = state_index(d, &follows, 0, 0);
      if (wants_newline)
	state_newline = state_index(d, &follows, 1, 0);
      else
	state_newline = state;
      if (wants_letter)
	state_letter = state_index(d, &follows, 0, 1);
      else
	state_letter = state;
      for (i = 0; i < NOTCHAR; ++i)
	trans[i] = (IS_WORD_CONSTITUENT(i)) ? state_letter : state;
      trans[eolbyte] = state_newline;
    }
  else
    for (i = 0; i < NOTCHAR; ++i)
      trans[i] = -1;

  for (i = 0; i < ngrps; ++i)
    {
      follows.nelem = 0;

      /* Find the union of the follows of the positions of the group.
	 This is a hideously inefficient loop.  Fix it someday. */
      for (j = 0; j < grps[i].nelem; ++j)
	for (k = 0; k < d->follows[grps[i].elems[j].index].nelem; ++k)
	  insert(d->follows[grps[i].elems[j].index].elems[k], &follows);

#ifdef MBS_SUPPORT
      if (d->mb_cur_max > 1)
	{
	  /* If a token in follows.elems is not 1st byte of a multibyte
	     character, or the states of follows must accept the bytes
	     which are not 1st byte of the multibyte character.
	     Then, if a state of follows encounter a byte, it must not be
	     a 1st byte of a multibyte character nor single byte character.
	     We cansel to add state[0].follows to next state, because
	     state[0] must accept 1st-byte

	     For example, we assume <sb a> is a certain single byte
	     character, <mb A> is a certain multibyte character, and the
	     codepoint of <sb a> equals the 2nd byte of the codepoint of
	     <mb A>.
	     When state[0] accepts <sb a>, state[i] transit to state[i+1]
	     by accepting accepts 1st byte of <mb A>, and state[i+1]
	     accepts 2nd byte of <mb A>, if state[i+1] encounter the
	     codepoint of <sb a>, it must not be <sb a> but 2nd byte of
	     <mb A>, so we can not add state[0].  */

	  next_isnt_1st_byte = 0;
	  for (j = 0; j < follows.nelem; ++j)
	    {
	      if (!(d->multibyte_prop[follows.elems[j].index] & 1))
		{
		  next_isnt_1st_byte = 1;
		  break;
		}
	    }
	}
#endif

      /* If we are building a searching matcher, throw in the positions
	 of state 0 as well. */
#ifdef MBS_SUPPORT
      if (d->searchflag && (d->mb_cur_max == 1 || !next_isnt_1st_byte))
#else
      if (d->searchflag)
#endif
	for (j = 0; j < d->states[0].elems.nelem; ++j)
	  insert(d->states[0].elems.elems[j], &follows);

      /* Find out if the new state will want any context information. */
      wants_newline = 0;
      if (tstbit(eolbyte, labels[i]))
	for (j = 0; j < follows.nelem; ++j)
	  if (PREV_NEWLINE_DEPENDENT(follows.elems[j].constraint))
	    wants_newline = 1;

      wants_letter = 0;
      for (j = 0; j < CHARCLASS_INTS; ++j)
	if (labels[i][j] & letters[j])
	  break;
      if (j < CHARCLASS_INTS)
	for (j = 0; j < follows.nelem; ++j)
	  if (PREV_LETTER_DEPENDENT(follows.elems[j].constraint))
	    wants_letter = 1;

      /* Find the state(s) corresponding to the union of the follows. */
      state = state_index(d, &follows, 0, 0);
      if (wants_newline)
	state_newline = state_index(d, &follows, 1, 0);
      else
	state_newline = state;
      if (wants_letter)
	state_letter = state_index(d, &follows, 0, 1);
      else
	state_letter = state;

      /* Set the transitions for each character in the current label. */
      for (j = 0; j < CHARCLASS_INTS; ++j)
	for (k = 0; k < INTBITS; ++k)
	  if (labels[i][j] & 1 << k)
	    {
	      int c = j * INTBITS + k;

	      if (c == eolbyte)
		trans[c] = state_newline;
	      else if (IS_WORD_CONSTITUENT(c))
		trans[c] = state_letter;
	      else if (c < NOTCHAR)
		trans[c] = state;
	    }
    }

  for (i = 0; i < ngrps; ++i)
    free(grps[i].elems);
  free(follows.elems);
  free(tmp.elems);

#line 2231

}
	

#line 2231

#line 3131

}
	

#line 3131
}

/* Some routines for manipulating a compiled dfa's transition tables.
   Each state may or may not have a transition table; if it does, and it
   is a non-accepting state, then d->trans[state] points to its table.
   If it is an accepting state then d->fails[state] points to its table.
   If it has no table at all, then d->trans[state] is NULL.
   TODO: Improve this comment, get rid of the unnecessary redundancy. */

static void
build_state (int s, struct dfa *d)
{

#line 3142

__notify_intrinsic((void*)"void build_state(int, struct dfa *) C_start", (void *)&global_x);

#line 3142
{

#line 2242

__notify_intrinsic((void*)"void build_state(int, struct dfa *) C_start", (void *)&global_x);

#line 2242
{
  int *trans;			/* The new transition table. */
  int i;

  /* Set an upper limit on the number of transition tables that will ever
     exist at once.  1024 is arbitrary.  The idea is that the frequently
     used transition tables will be quickly rebuilt, whereas the ones that
     were only needed once or twice will be cleared away. */
  if (d->trcount >= 1024)
    {
      for (i = 0; i < d->tralloc; ++i)
        {
	  free(d->trans[i]);
	  free(d->fails[i]);
	  d->trans[i] = d->fails[i] = NULL;
	}
      d->trcount = 0;
    }

  ++d->trcount;

  /* Set up the success bits for this state. */
  d->success[s] = 0;
  if (ACCEPTS_IN_CONTEXT(d->states[s].newline, 1, d->states[s].letter, 0,
      s, *d))
    d->success[s] |= 4;
  if (ACCEPTS_IN_CONTEXT(d->states[s].newline, 0, d->states[s].letter, 1,
      s, *d))
    d->success[s] |= 2;
  if (ACCEPTS_IN_CONTEXT(d->states[s].newline, 0, d->states[s].letter, 0,
      s, *d))
    d->success[s] |= 1;

  MALLOC(trans, int, NOTCHAR);
  dfastate(s, d, trans);

  /* Now go through the new transition table, and make sure that the trans
     and fail arrays are allocated large enough to hold a pointer for the
     largest state mentioned in the table. */
  for (i = 0; i < NOTCHAR; ++i)
    if (trans[i] >= d->tralloc)
      {
	int oldalloc = d->tralloc;

	while (trans[i] >= d->tralloc)
	  d->tralloc *= 2;
	REALLOC(d->realtrans, int *, d->tralloc + 1);
	d->trans = d->realtrans + 1;
	REALLOC(d->fails, int *, d->tralloc);
	REALLOC(d->success, int, d->tralloc);
	REALLOC(d->newlines, int, d->tralloc);
	while (oldalloc < d->tralloc)
	  {
	    d->trans[oldalloc] = NULL;
	    d->fails[oldalloc++] = NULL;
	  }
      }

  /* Keep the newline transition in a special place so we can use it as
     a sentinel. */
  d->newlines[s] = trans[eolbyte];
  trans[eolbyte] = -1;

  if (ACCEPTING(s, *d))
    d->fails[s] = trans;
  else
    d->trans[s] = trans;

#line 2309

}
	

#line 2309

#line 3223

}
	

#line 3223
}

static void
build_state_zero (struct dfa *d)
{

#line 3227

__notify_intrinsic((void*)"void build_state_zero(struct dfa *) C_start", (void *)&global_x);

#line 3227
{

#line 2313

__notify_intrinsic((void*)"void build_state_zero(struct dfa *) C_start", (void *)&global_x);

#line 2313
{
  d->tralloc = 1;
  d->trcount = 0;
  CALLOC(d->realtrans, int *, d->tralloc + 1);
  d->trans = d->realtrans + 1;
  CALLOC(d->fails, int *, d->tralloc);
  MALLOC(d->success, int, d->tralloc);
  MALLOC(d->newlines, int, d->tralloc);
  build_state(0, d);

#line 2322

}
	

#line 2322

#line 3250

}
	

#line 3250
}

#ifdef MBS_SUPPORT
/* Multibyte character handling sub-routines for dfaexec.  */

/* Initial state may encounter the byte which is not a single byte character
   nor 1st byte of a multibyte character.  But it is incorrect for initial
   state to accept such a byte.
   For example, in sjis encoding the regular expression like "\\" accepts
   the codepoint 0x5c, but should not accept the 2nd byte of the codepoint
   0x815c. Then Initial state must skip the bytes which are not a single byte
   character nor 1st byte of a multibyte character.  */
#define SKIP_REMAINS_MB_IF_INITIAL_STATE(s, p)		\
  if (s == 0)						\
    {							\
      while (inputwcs[p - buf_begin] == 0		\
            && mblen_buf[p - buf_begin] > 0		\
            && (unsigned char const *) p < buf_end)	\
        ++p;						\
      if ((char *) p >= end)				\
	{						\
          free(mblen_buf);				\
          free(inputwcs);				\
	  *end = saved_end;				\
	  return NULL;					\
	}						\
    }

static void
realloc_trans_if_necessary(struct dfa *d, int new_state)
{

#line 3280

__notify_intrinsic((void*)"void realloc_trans_if_necessary(struct dfa *, int) C_start", (void *)&global_x);

#line 3280
{

#line 2352

__notify_intrinsic((void*)"void realloc_trans_if_necessary(struct dfa *, int) C_start", (void *)&global_x);

#line 2352
{
  /* Make sure that the trans and fail arrays are allocated large enough
     to hold a pointer for the new state. */
  if (new_state >= d->tralloc)
    {
      int oldalloc = d->tralloc;

      while (new_state >= d->tralloc)
	d->tralloc *= 2;
      REALLOC(d->realtrans, int *, d->tralloc + 1);
      d->trans = d->realtrans + 1;
      REALLOC(d->fails, int *, d->tralloc);
      REALLOC(d->success, int, d->tralloc);
      REALLOC(d->newlines, int, d->tralloc);
      while (oldalloc < d->tralloc)
	{
	  d->trans[oldalloc] = NULL;
	  d->fails[oldalloc++] = NULL;
	}
    }

#line 2372

}
	

#line 2372

#line 3314

}
	

#line 3314
}

/* Return values of transit_state_singlebyte(), and
   transit_state_consume_1char.  */
typedef enum
{
  TRANSIT_STATE_IN_PROGRESS,	/* State transition has not finished.  */
  TRANSIT_STATE_DONE,		/* State transition has finished.  */
  TRANSIT_STATE_END_BUFFER	/* Reach the end of the buffer.  */
} status_transit_state;

/* Consume a single byte and transit state from 's' to '*next_state'.
   This function is almost same as the state transition routin in dfaexec().
   But state transition is done just once, otherwise matching succeed or
   reach the end of the buffer.  */
static status_transit_state
transit_state_singlebyte (struct dfa *d, int s, unsigned char const *p,
				  int *next_state)
{

#line 3332

__notify_intrinsic((void*)"status_transit_state transit_state_singlebyte(struct dfa *, int, const unsigned char *, int *) C_start", (void *)&global_x);

#line 3332
{

#line 2390

__notify_intrinsic((void*)"status_transit_state transit_state_singlebyte(struct dfa *, int, const unsigned char *, int *) C_start", (void *)&global_x);

#line 2390
{
  int *t;
  int works = s;

  status_transit_state rval = TRANSIT_STATE_IN_PROGRESS;

  while (rval == TRANSIT_STATE_IN_PROGRESS)
    {
      if ((t = d->trans[works]) != NULL)
	{
	  works = t[*p];
	  rval = TRANSIT_STATE_DONE;
	  if (works < 0)
	    works = 0;
	}
      else if (works < 0)
	{
	  if (p == buf_end)
	    {
	      /* At the moment, it must not happen.  */
	      abort ();
	    }
	  works = 0;
	}
      else if (d->fails[works])
	{
	  works = d->fails[works][*p];
	  rval = TRANSIT_STATE_DONE;
	}
      else
	{
	  build_state(works, d);
	}
    }
  *next_state = works;
  
#line 2425
{ status_transit_state tau_ret_val =  rval; __notify_intrinsic((void*)"status_transit_state transit_state_singlebyte(struct dfa *, int, const unsigned char *, int *) C_end", (void *)&global_x); 
#line 3376
{ status_transit_state tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"status_transit_state transit_state_singlebyte(struct dfa *, int, const unsigned char *, int *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3376
 }

#line 2425


#line 2426

}
	

#line 2426

#line 3387

}
	

#line 3387
}

/* Check whether period can match or not in the current context.  If it can,
   return the amount of the bytes with which period can match, otherwise
   return 0.
   `pos' is the position of the period.  `idx' is the index from the
   buf_begin, and it is the current position in the buffer.  */
static int
match_anychar (struct dfa *d, int s, position pos, int idx)
{

#line 3396

__notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_start", (void *)&global_x);

#line 3396
{

#line 2435

__notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_start", (void *)&global_x);

#line 2435
{
  int newline = 0;
  int letter = 0;
  wchar_t wc;
  int mbclen;

  wc = inputwcs[idx];
  mbclen = (mblen_buf[idx] == 0)? 1 : mblen_buf[idx];

  /* Check context.  */
  if (wc == (wchar_t)eolbyte)
    {
      if (!(syntax_bits & RE_DOT_NEWLINE))
	
#line 2448
{ int tau_ret_val =  0; __notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_end", (void *)&global_x); 
#line 3418
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3418
 }

#line 2448

      newline = 1;
    }
  else if (wc == (wchar_t)'\0')
    {
      if (syntax_bits & RE_DOT_NOT_NULL)
	
#line 2454
{ int tau_ret_val =  0; __notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_end", (void *)&global_x); 
#line 3429
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3429
 }

#line 2454

      newline = 1;
    }

  if (iswalnum(wc) || wc == L'_')
    letter = 1;

  if (!SUCCEEDS_IN_CONTEXT(pos.constraint, d->states[s].newline,
			   newline, d->states[s].letter, letter))
    
#line 2463
{ int tau_ret_val =  0; __notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_end", (void *)&global_x); 
#line 3443
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3443
 }

#line 2463


  
#line 2465
{ int tau_ret_val =  mbclen; __notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_end", (void *)&global_x); 
#line 3450
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int match_anychar(struct dfa *, int, position, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3450
 }

#line 2465


#line 2466

}
	

#line 2466

#line 3461

}
	

#line 3461
}

/* Check whether bracket expression can match or not in the current context.
   If it can, return the amount of the bytes with which expression can match,
   otherwise return 0.
   `pos' is the position of the bracket expression.  `idx' is the index
   from the buf_begin, and it is the current position in the buffer.  */
static int
match_mb_charset (struct dfa *d, int s, position pos, int idx)
{

#line 3470

__notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_start", (void *)&global_x);

#line 3470
{

#line 2475

__notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_start", (void *)&global_x);

#line 2475
{
  int i;
  int match;		/* Flag which represent that matching succeed.  */
  int match_len;	/* Length of the character (or collating element)
			   with which this operator match.  */
  int op_len;		/* Length of the operator.  */
  char buffer[128];
  wchar_t wcbuf[6];

  /* Pointer to the structure to which we are currently refering.  */
  struct mb_char_classes *work_mbc;

  int newline = 0;
  int letter = 0;
  wchar_t wc;		/* Current refering character.  */

  wc = inputwcs[idx];

  /* Check context.  */
  if (wc == (wchar_t)eolbyte)
    {
      if (!(syntax_bits & RE_DOT_NEWLINE))
	
#line 2497
{ int tau_ret_val =  0; __notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_end", (void *)&global_x); 
#line 3501
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3501
 }

#line 2497

      newline = 1;
    }
  else if (wc == (wchar_t)'\0')
    {
      if (syntax_bits & RE_DOT_NOT_NULL)
	
#line 2503
{ int tau_ret_val =  0; __notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_end", (void *)&global_x); 
#line 3512
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3512
 }

#line 2503

      newline = 1;
    }
  if (iswalnum(wc) || wc == L'_')
    letter = 1;
  if (!SUCCEEDS_IN_CONTEXT(pos.constraint, d->states[s].newline,
			   newline, d->states[s].letter, letter))
    
#line 2510
{ int tau_ret_val =  0; __notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_end", (void *)&global_x); 
#line 3524
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3524
 }

#line 2510


  /* Assign the current refering operator to work_mbc.  */
  work_mbc = &(d->mbcsets[(d->multibyte_prop[pos.index]) >> 2]);
  match = !work_mbc->invert;
  match_len = (mblen_buf[idx] == 0)? 1 : mblen_buf[idx];

  /* Match in range 0-255?  */
  if (wc < NOTCHAR && work_mbc->cset != -1
      && tstbit((unsigned char)wc, d->charclasses[work_mbc->cset]))
    goto charset_matched;

  /* match with a character class?  */
  for (i = 0; i<work_mbc->nch_classes; i++)
    {
      if (iswctype((wint_t)wc, work_mbc->ch_classes[i]))
	goto charset_matched;
    }

  strncpy(buffer, (char const *) buf_begin + idx, match_len);
  buffer[match_len] = '\0';

  /* match with an equivalent class?  */
  for (i = 0; i<work_mbc->nequivs; i++)
    {
      op_len = strlen(work_mbc->equivs[i]);
      strncpy(buffer, (char const *) buf_begin + idx, op_len);
      buffer[op_len] = '\0';
      if (strcoll(work_mbc->equivs[i], buffer) == 0)
	{
	  match_len = op_len;
	  goto charset_matched;
	}
    }

  /* match with a collating element?  */
  for (i = 0; i<work_mbc->ncoll_elems; i++)
    {
      op_len = strlen(work_mbc->coll_elems[i]);
      strncpy(buffer, (char const *) buf_begin + idx, op_len);
      buffer[op_len] = '\0';

      if (strcoll(work_mbc->coll_elems[i], buffer) == 0)
	{
	  match_len = op_len;
	  goto charset_matched;
	}
    }

  wcbuf[0] = wc;
  wcbuf[1] = wcbuf[3] = wcbuf[5] = '\0';

  /* match with a range?  */
  for (i = 0; i<work_mbc->nranges; i++)
    {
      wcbuf[2] = work_mbc->range_sts[i];
      wcbuf[4] = work_mbc->range_ends[i];

      if (wcscoll(wcbuf, wcbuf+2) >= 0 &&
	  wcscoll(wcbuf+4, wcbuf) >= 0)
	goto charset_matched;
    }

  /* match with a character?  */
  for (i = 0; i<work_mbc->nchars; i++)
    {
      if (wc == work_mbc->chars[i])
	goto charset_matched;
    }

  match = !match;

 charset_matched:
  
#line 2583
{ int tau_ret_val =  match ? match_len : 0; __notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_end", (void *)&global_x); 
#line 3602
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int match_mb_charset(struct dfa *, int, position, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3602
 }

#line 2583


#line 2584

}
	

#line 2584

#line 3613

}
	

#line 3613
}

/* Check each of `d->states[s].mbps.elem' can match or not. Then return the
   array which corresponds to `d->states[s].mbps.elem' and each element of
   the array contains the amount of the bytes with which the element can
   match.
   `idx' is the index from the buf_begin, and it is the current position
   in the buffer.
   Caller MUST free the array which this function return.  */
static int*
check_matching_with_multibyte_ops (struct dfa *d, int s, int idx)
{

#line 3624

__notify_intrinsic((void*)"int *check_matching_with_multibyte_ops(struct dfa *, int, int) C_start", (void *)&global_x);

#line 3624
{

#line 2595

__notify_intrinsic((void*)"int *check_matching_with_multibyte_ops(struct dfa *, int, int) C_start", (void *)&global_x);

#line 2595
{
  int i;
  int* rarray;

  MALLOC(rarray, int, d->states[s].mbps.nelem);
  for (i = 0; i < d->states[s].mbps.nelem; ++i)
    {
      position pos = d->states[s].mbps.elems[i];
      switch(d->tokens[pos.index])
	{
	case ANYCHAR:
	  rarray[i] = match_anychar(d, s, pos, idx);
	  break;
	case MBCSET:
	  rarray[i] = match_mb_charset(d, s, pos, idx);
	  break;
	default:
	  break; /* can not happen.  */
	}
    }
  
#line 2615
{ int * tau_ret_val =  rarray; __notify_intrinsic((void*)"int *check_matching_with_multibyte_ops(struct dfa *, int, int) C_end", (void *)&global_x); 
#line 3653
{ int * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int *check_matching_with_multibyte_ops(struct dfa *, int, int) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3653
 }

#line 2615


#line 2616

}
	

#line 2616

#line 3664

}
	

#line 3664
}

/* Consume a single character and enumerate all of the positions which can
   be next position from the state `s'.
   `match_lens' is the input. It can be NULL, but it can also be the output
   of check_matching_with_multibyte_ops() for optimization.
   `mbclen' and `pps' are the output.  `mbclen' is the length of the
   character consumed, and `pps' is the set this function enumerate.  */
static status_transit_state
transit_state_consume_1char (struct dfa *d, int s, unsigned char const **pp,
			     int *match_lens, int *mbclen, position_set *pps)
{

#line 3675

__notify_intrinsic((void*)"status_transit_state transit_state_consume_1char(struct dfa *, int, const unsigned char **, int *, int *, position_set *) C_start", (void *)&global_x);

#line 3675
{

#line 2627

__notify_intrinsic((void*)"status_transit_state transit_state_consume_1char(struct dfa *, int, const unsigned char **, int *, int *, position_set *) C_start", (void *)&global_x);

#line 2627
{
  int i, j;
  int s1, s2;
  int* work_mbls;
  status_transit_state rs = TRANSIT_STATE_DONE;

  /* Calculate the length of the (single/multi byte) character
     to which p points.  */
  *mbclen = (mblen_buf[*pp - buf_begin] == 0)? 1
    : mblen_buf[*pp - buf_begin];

  /* Calculate the state which can be reached from the state `s' by
     consuming `*mbclen' single bytes from the buffer.  */
  s1 = s;
  for (i = 0; i < *mbclen; i++)
    {
      s2 = s1;
      rs = transit_state_singlebyte(d, s2, (*pp)++, &s1);
    }
  /* Copy the positions contained by `s1' to the set `pps'.  */
  copy(&(d->states[s1].elems), pps);

  /* Check (inputed)match_lens, and initialize if it is NULL.  */
  if (match_lens == NULL && d->states[s].mbps.nelem != 0)
    work_mbls = check_matching_with_multibyte_ops(d, s, *pp - buf_begin);
  else
    work_mbls = match_lens;

  /* Add all of the positions which can be reached from `s' by consuming
     a single character.  */
  for (i = 0; i < d->states[s].mbps.nelem ; i++)
   {
      if (work_mbls[i] == *mbclen)
	for (j = 0; j < d->follows[d->states[s].mbps.elems[i].index].nelem;
	     j++)
	  insert(d->follows[d->states[s].mbps.elems[i].index].elems[j],
		 pps);
    }

  if (match_lens == NULL && work_mbls != NULL)
    free(work_mbls);
  
#line 2668
{ status_transit_state tau_ret_val =  rs; __notify_intrinsic((void*)"status_transit_state transit_state_consume_1char(struct dfa *, int, const unsigned char **, int *, int *, position_set *) C_end", (void *)&global_x); 
#line 3725
{ status_transit_state tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"status_transit_state transit_state_consume_1char(struct dfa *, int, const unsigned char **, int *, int *, position_set *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3725
 }

#line 2668


#line 2669

}
	

#line 2669

#line 3736

}
	

#line 3736
}

/* Transit state from s, then return new state and update the pointer of the
   buffer.  This function is for some operator which can match with a multi-
   byte character or a collating element (which may be multi characters).  */
static int
transit_state (struct dfa *d, int s, unsigned char const **pp)
{

#line 3743

__notify_intrinsic((void*)"int transit_state(struct dfa *, int, const unsigned char **) C_start", (void *)&global_x);

#line 3743
{

#line 2676

__notify_intrinsic((void*)"int transit_state(struct dfa *, int, const unsigned char **) C_start", (void *)&global_x);

#line 2676
{
  int s1;
  int mbclen;		/* The length of current input multibyte character. */
  int maxlen = 0;
  int i, j;
  int *match_lens = NULL;
  int nelem = d->states[s].mbps.nelem; /* Just a alias.  */
  position_set follows;
  unsigned char const *p1 = *pp;
  wchar_t wc;

  if (nelem > 0)
    /* This state has (a) multibyte operator(s).
       We check whether each of them can match or not.  */
    {
      /* Note: caller must free the return value of this function.  */
      match_lens = check_matching_with_multibyte_ops(d, s, *pp - buf_begin);

      for (i = 0; i < nelem; i++)
	/* Search the operator which match the longest string,
	   in this state.  */
	{
	  if (match_lens[i] > maxlen)
	    maxlen = match_lens[i];
	}
    }

  if (nelem == 0 || maxlen == 0)
    /* This state has no multibyte operator which can match.
       We need to check only one single byte character.  */
    {
      status_transit_state rs;
      rs = transit_state_singlebyte(d, s, *pp, &s1);

      /* We must update the pointer if state transition succeeded.  */
      if (rs == TRANSIT_STATE_DONE)
	++*pp;

      free(match_lens);
      
#line 2715
{ int tau_ret_val =  s1; __notify_intrinsic((void*)"int transit_state(struct dfa *, int, const unsigned char **) C_end", (void *)&global_x); 
#line 3791
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int transit_state(struct dfa *, int, const unsigned char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3791
 }

#line 2715

    }

  /* This state has some operators which can match a multibyte character.  */
  follows.nelem = 0;
  MALLOC(follows.elems, position, d->nleaves);

  /* `maxlen' may be longer than the length of a character, because it may
     not be a character but a (multi character) collating element.
     We enumerate all of the positions which `s' can reach by consuming
     `maxlen' bytes.  */
  transit_state_consume_1char(d, s, pp, match_lens, &mbclen, &follows);

  wc = inputwcs[*pp - mbclen - buf_begin];
  s1 = state_index(d, &follows, wc == L'\n', iswalnum(wc));
  realloc_trans_if_necessary(d, s1);

  while (*pp - p1 < maxlen)
    {
      follows.nelem = 0;
      transit_state_consume_1char(d, s1, pp, NULL, &mbclen, &follows);

      for (i = 0; i < nelem ; i++)
	{
	  if (match_lens[i] == *pp - p1)
	    for (j = 0;
		 j < d->follows[d->states[s1].mbps.elems[i].index].nelem; j++)
	      insert(d->follows[d->states[s1].mbps.elems[i].index].elems[j],
		     &follows);
	}

      wc = inputwcs[*pp - mbclen - buf_begin];
      s1 = state_index(d, &follows, wc == L'\n', iswalnum(wc));
      realloc_trans_if_necessary(d, s1);
    }
  free(match_lens);
  free(follows.elems);
  
#line 2752
{ int tau_ret_val =  s1; __notify_intrinsic((void*)"int transit_state(struct dfa *, int, const unsigned char **) C_end", (void *)&global_x); 
#line 3833
{ int tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"int transit_state(struct dfa *, int, const unsigned char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3833
 }

#line 2752


#line 2753

}
	

#line 2753

#line 3844

}
	

#line 3844
}

#endif /* MBS_SUPPORT */

/* Search through a buffer looking for a match to the given struct dfa.
   Find the first occurrence of a string matching the regexp in the
   buffer, and the shortest possible version thereof.  Return a pointer to
   the first character after the match, or NULL if none is found.  BEGIN
   points to the beginning of the buffer, and END points to the first byte
   after its end.  Note however that we store a sentinel byte (usually
   newline) in *END, so the actual buffer must be one byte longer.
   When NEWLINE is nonzero, newlines may appear in the matching string.
   If COUNT is non-NULL, increment *COUNT once for each newline processed.
   Finally, if BACKREF is non-NULL set *BACKREF to indicate whether we
   encountered a back-reference (1) or not (0).  The caller may use this
   to decide whether to fall back on a backtracking matcher. */
char *
dfaexec (struct dfa *d, char const *begin, char *end,
	 int newline, int *count, int *backref)
{

#line 3863

__notify_intrinsic((void*)"char *dfaexec(struct dfa *, const char *, char *, int, int *, int *) C_start", (void *)&global_x);

#line 3863
{

#line 2772

__notify_intrinsic((void*)"char *dfaexec(struct dfa *, const char *, char *, int, int *, int *) C_start", (void *)&global_x);

#line 2772
{
  int s, s1, tmp;	/* Current state. */
  unsigned char const *p; /* Current input character. */
  int **trans, *t;	/* Copy of d->trans so it can be optimized
				   into a register. */
  unsigned char eol = eolbyte;	/* Likewise for eolbyte.  */
  static int sbit[NOTCHAR];	/* Table for anding with d->success. */
  static int sbit_init;

  if (! sbit_init)
    {
      int i;

      sbit_init = 1;
      for (i = 0; i < NOTCHAR; ++i)
	sbit[i] = (IS_WORD_CONSTITUENT(i)) ? 2 : 1;
      sbit[eol] = 4;
    }

  if (! d->tralloc)
    build_state_zero(d);

  s = s1 = 0;
  p = (unsigned char const *) begin;
  trans = d->trans;
  unsigned char saved_end = *(unsigned char *) end;
  *end = eol;

#ifdef MBS_SUPPORT
  if (d->mb_cur_max > 1)
    {
      int remain_bytes, i;
      buf_begin = (unsigned char *) begin;
      buf_end = (unsigned char *) end;

      /* initialize mblen_buf, and inputwcs.  */
      MALLOC(mblen_buf, unsigned char, end - begin + 2);
      MALLOC(inputwcs, wchar_t, end - begin + 2);
      memset(&mbs, 0, sizeof(mbstate_t));
      remain_bytes = 0;
      for (i = 0; i < end - begin + 1; i++)
	{
	  if (remain_bytes == 0)
	    {
	      remain_bytes
		= mbrtowc(inputwcs + i, begin + i, end - begin - i + 1, &mbs);
	      if (remain_bytes < 1
		|| (remain_bytes == 1 && inputwcs[i] == (wchar_t)begin[i]))
		{
		  remain_bytes = 0;
		  inputwcs[i] = (wchar_t)begin[i];
		  mblen_buf[i] = 0;
		}
	      else
		{
		  mblen_buf[i] = remain_bytes;
		  remain_bytes--;
		}
	    }
	  else
	    {
	      mblen_buf[i] = remain_bytes;
	      inputwcs[i] = 0;
	      remain_bytes--;
	    }
	}
      mblen_buf[i] = 0;
      inputwcs[i] = 0; /* sentinel */
    }
#endif /* MBS_SUPPORT */

  for (;;)
    {
#ifdef MBS_SUPPORT
      if (d->mb_cur_max > 1)
	while ((t = trans[s]))
	  {
	    if ((char *) p > end)
	      break;
	    s1 = s;
	    SKIP_REMAINS_MB_IF_INITIAL_STATE(s, p);

	    if (d->states[s].mbps.nelem == 0)
	      {
		s = t[*p++];
		continue;
	      }

	    /* Can match with a multibyte character (and multi character
	       collating element).  Transition table might be updated.  */
	    s = transit_state(d, s, &p);
	    trans = d->trans;
	  }
      else
#endif /* MBS_SUPPORT */
      while ((t = trans[s]) != 0) { /* hand-optimized loop */
	s1 = t[*p++];
	if ((t = trans[s1]) == 0) {
	  tmp = s ; s = s1 ; s1 = tmp ; /* swap */
	  break;
	}
	s = t[*p++];
      }

      if (s >= 0 && (char *) p <= end && d->fails[s])
	{
	  if (d->success[s] & sbit[*p])
	    {
	      if (backref)
		*backref = (d->states[s].backref != 0);
#ifdef MBS_SUPPORT
	      if (d->mb_cur_max > 1)
		{
		  free(mblen_buf);
		  free(inputwcs);
		}
#endif /* MBS_SUPPORT */
	      *end = saved_end;
	      
#line 2890
{ char * tau_ret_val =  (char *) p; __notify_intrinsic((void*)"char *dfaexec(struct dfa *, const char *, char *, int, int *, int *) C_end", (void *)&global_x); 
#line 3990
{ char * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char *dfaexec(struct dfa *, const char *, char *, int, int *, int *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 3990
 }

#line 2890

	    }

	  s1 = s;
#ifdef MBS_SUPPORT
	  if (d->mb_cur_max > 1)
	    {
              /* Can match with a multibyte character (and multicharacter
                 collating element).  Transition table might be updated.  */
              s = transit_state(d, s, &p);
              trans = d->trans;
            }
	  else
#endif /* MBS_SUPPORT */
	  s = d->fails[s][*p++];
	  continue;
	}

      /* If the previous character was a newline, count it. */
      if (count && (char *) p <= end && p[-1] == eol)
	++*count;

      /* Check if we've run off the end of the buffer. */
      if ((char *) p > end)
	{
#ifdef MBS_SUPPORT
	  if (d->mb_cur_max > 1)
	    {
	      free(mblen_buf);
	      free(inputwcs);
	    }
#endif /* MBS_SUPPORT */
	  *end = saved_end;
	  
#line 2923
{ char * tau_ret_val =  NULL; __notify_intrinsic((void*)"char *dfaexec(struct dfa *, const char *, char *, int, int *, int *) C_end", (void *)&global_x); 
#line 4028
{ char * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char *dfaexec(struct dfa *, const char *, char *, int, int *, int *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4028
 }

#line 2923

	}

      if (s >= 0)
	{
	  build_state(s, d);
	  trans = d->trans;
	  continue;
	}

      if (p[-1] == eol && newline)
	{
	  s = d->newlines[s1];
	  continue;
	}

      s = 0;
    }

#line 2941

}
	

#line 2941

#line 4056

}
	

#line 4056
}

#ifdef MBS_SUPPORT
static void
free_mbdata (struct dfa *d)
{

#line 4061

__notify_intrinsic((void*)"void free_mbdata(struct dfa *) C_start", (void *)&global_x);

#line 4061
{

#line 2946

__notify_intrinsic((void*)"void free_mbdata(struct dfa *) C_start", (void *)&global_x);

#line 2946
{
  unsigned int i;

  free(d->multibyte_prop);
  d->multibyte_prop = NULL;

  for (i = 0; i < d->nmbcsets; ++i)
    {
      unsigned int j;
      struct mb_char_classes *p = &(d->mbcsets[i]);
      free(p->chars);
      free(p->ch_classes);
      free(p->range_sts);
      free(p->range_ends);

      for (j = 0; j < p->nequivs; ++j)
        free(p->equivs[j]);
      free(p->equivs);

      for (j = 0; j < p->ncoll_elems; ++j)
        free(p->coll_elems[j]);
      free(p->coll_elems);
    }

  free(d->mbcsets);
  d->mbcsets = NULL;
  d->nmbcsets = 0;

#line 2973

}
	

#line 2973

#line 4102

}
	

#line 4102
}
#endif

/* Initialize the components of a dfa that the other routines don't
   initialize for themselves. */
void
dfainit (struct dfa *d)
{

#line 4109

__notify_intrinsic((void*)"void dfainit(struct dfa *) C_start", (void *)&global_x);

#line 4109
{

#line 2980

__notify_intrinsic((void*)"void dfainit(struct dfa *) C_start", (void *)&global_x);

#line 2980
{
  d->calloc = 1;
  MALLOC(d->charclasses, charclass, d->calloc);
  d->cindex = 0;

  d->talloc = 1;
  MALLOC(d->tokens, token, d->talloc);
  d->tindex = d->depth = d->nleaves = d->nregexps = 0;

#ifdef MBS_SUPPORT
  d->mb_cur_max = MB_CUR_MAX;
  if (d->mb_cur_max > 1)
    {
      d->nmultibyte_prop = 1;
      MALLOC(d->multibyte_prop, int, d->nmultibyte_prop);
      d->nmbcsets = 0;
      d->mbcsets_alloc = 1;
      MALLOC(d->mbcsets, struct mb_char_classes, d->mbcsets_alloc);
    }
#endif

  d->searchflag = 0;
  d->tralloc = 0;

  d->musts = 0;
  d->realtrans = 0;
  d->fails = 0;
  d->newlines = 0;
  d->success = 0;
#ifdef GAWK
  d->broken = 0;
#endif

#line 3012

}
	

#line 3012

#line 4155

}
	

#line 4155
}

#ifdef MBS_SUPPORT
static void
dfaoptimize (struct dfa *d)
{

#line 4160

__notify_intrinsic((void*)"void dfaoptimize(struct dfa *) C_start", (void *)&global_x);

#line 4160
{

#line 3017

__notify_intrinsic((void*)"void dfaoptimize(struct dfa *) C_start", (void *)&global_x);

#line 3017
{
  unsigned int i;
  if (!using_utf8())
    
#line 3020
{ __notify_intrinsic((void*)"void dfaoptimize(struct dfa *) C_end", (void *)&global_x); 
#line 4172
{ __notify_intrinsic((void*)"void dfaoptimize(struct dfa *) C_end", (void *)&global_x); return; }

#line 4172
 }

#line 3020


  for (i = 0; i < d->tindex; ++i)
    {
      switch(d->tokens[i])
	{
	case ANYCHAR:
	case MBCSET:
	  /* Requires multi-byte algorithm.  */
	  
#line 3029
{ __notify_intrinsic((void*)"void dfaoptimize(struct dfa *) C_end", (void *)&global_x); 
#line 4186
{ __notify_intrinsic((void*)"void dfaoptimize(struct dfa *) C_end", (void *)&global_x); return; }

#line 4186
 }

#line 3029

	default:
	  break;
	}
    }

  free_mbdata (d);
  d->mb_cur_max = 1;

#line 3037

}
	

#line 3037

#line 4204

}
	

#line 4204
}
#endif

/* Parse and analyze a single string of the given length. */
void
dfacomp (char const *s, size_t len, struct dfa *d, int searchflag)
{

#line 4210

__notify_intrinsic((void*)"void dfacomp(const char *, size_t, struct dfa *, int) C_start", (void *)&global_x);

#line 4210
{

#line 3043

__notify_intrinsic((void*)"void dfacomp(const char *, size_t, struct dfa *, int) C_start", (void *)&global_x);

#line 3043
{
  dfainit(d);
  dfaparse(s, len, d);
  dfamust(d);
#ifdef MBS_SUPPORT
  dfaoptimize(d);
#endif
  dfaanalyze(d, searchflag);

#line 3051

}
	

#line 3051

#line 4232

}
	

#line 4232
}

/* Free the storage held by the components of a dfa. */
void
dfafree (struct dfa *d)
{

#line 4237

__notify_intrinsic((void*)"void dfafree(struct dfa *) C_start", (void *)&global_x);

#line 4237
{

#line 3056

__notify_intrinsic((void*)"void dfafree(struct dfa *) C_start", (void *)&global_x);

#line 3056
{
  int i;
  struct dfamust *dm, *ndm;

  free(d->charclasses);
  free(d->tokens);

#ifdef MBS_SUPPORT
  if (d->mb_cur_max > 1)
    free_mbdata(d);
#endif /* MBS_SUPPORT */

  for (i = 0; i < d->sindex; ++i) {
    free(d->states[i].elems.elems);
#ifdef MBS_SUPPORT
    free(d->states[i].mbps.elems);
#endif /* MBS_SUPPORT */
  }
  free(d->states);
  for (i = 0; i < d->tindex; ++i)
    free(d->follows[i].elems);
  free(d->follows);
  for (i = 0; i < d->tralloc; ++i)
    {
      free(d->trans[i]);
      free(d->fails[i]);
    }
  free(d->realtrans);
  free(d->fails);
  free(d->newlines);
  free(d->success);
  for (dm = d->musts; dm; dm = ndm)
    {
      ndm = dm->next;
      free(dm->must);
      free(dm);
    }

#line 3093

}
	

#line 3093

#line 4288

}
	

#line 4288
}

/* Having found the postfix representation of the regular expression,
   try to find a long sequence of characters that must appear in any line
   containing the r.e.
   Finding a "longest" sequence is beyond the scope here;
   we take an easy way out and hope for the best.
   (Take "(ab|a)b"--please.)

   We do a bottom-up calculation of sequences of characters that must appear
   in matches of r.e.'s represented by trees rooted at the nodes of the postfix
   representation:
	sequences that must appear at the left of the match ("left")
	sequences that must appear at the right of the match ("right")
	lists of sequences that must appear somewhere in the match ("in")
	sequences that must constitute the match ("is")

   When we get to the root of the tree, we use one of the longest of its
   calculated "in" sequences as our answer.  The sequence we find is returned in
   d->must (where "d" is the single argument passed to "dfamust");
   the length of the sequence is returned in d->mustn.

   The sequences calculated for the various types of node (in pseudo ANSI c)
   are shown below.  "p" is the operand of unary operators (and the left-hand
   operand of binary operators); "q" is the right-hand operand of binary
   operators.

   "ZERO" means "a zero-length sequence" below.

	Type	left		right		is		in
	----	----		-----		--		--
	char c	# c		# c		# c		# c

	ANYCHAR	ZERO		ZERO		ZERO		ZERO

	MBCSET	ZERO		ZERO		ZERO		ZERO

	CSET	ZERO		ZERO		ZERO		ZERO

	STAR	ZERO		ZERO		ZERO		ZERO

	QMARK	ZERO		ZERO		ZERO		ZERO

	PLUS	p->left		p->right	ZERO		p->in

	CAT	(p->is==ZERO)?	(q->is==ZERO)?	(p->is!=ZERO &&	p->in plus
		p->left :	q->right :	q->is!=ZERO) ?	q->in plus
		p->is##q->left	p->right##q->is	p->is##q->is :	p->right##q->left
						ZERO

	OR	longest common	longest common	(do p->is and	substrings common to
		leading		trailing	q->is have same	p->in and q->in
		(sub)sequence	(sub)sequence	length and
		of p->left	of p->right	content) ?
		and q->left	and q->right	p->is : NULL

   If there's anything else we recognize in the tree, all four sequences get set
   to zero-length sequences.  If there's something we don't recognize in the tree,
   we just return a zero-length sequence.

   Break ties in favor of infrequent letters (choosing 'zzz' in preference to
   'aaa')?

   And. . .is it here or someplace that we might ponder "optimizations" such as
	egrep 'psi|epsilon'	->	egrep 'psi'
	egrep 'pepsi|epsilon'	->	egrep 'epsi'
					(Yes, we now find "epsi" as a "string
					that must occur", but we might also
					simplify the *entire* r.e. being sought)
	grep '[c]'		->	grep 'c'
	grep '(ab|a)b'		->	grep 'ab'
	grep 'ab*'		->	grep 'a'
	grep 'a*b'		->	grep 'b'

   There are several issues:

   Is optimization easy (enough)?

   Does optimization actually accomplish anything,
   or is the automaton you get from "psi|epsilon" (for example)
   the same as the one you get from "psi" (for example)?

   Are optimizable r.e.'s likely to be used in real-life situations
   (something like 'ab*' is probably unlikely; something like is
   'psi|epsilon' is likelier)? */

static char *
icatalloc (char *old, char *new)
{

#line 4376

__notify_intrinsic((void*)"char *icatalloc(char *, char *) C_start", (void *)&global_x);

#line 4376
{

#line 3181

__notify_intrinsic((void*)"char *icatalloc(char *, char *) C_start", (void *)&global_x);

#line 3181
{
  char *result;
  size_t oldsize, newsize;

  newsize = (new == NULL) ? 0 : strlen(new);
  if (old == NULL)
    oldsize = 0;
  else if (newsize == 0)
    
#line 3189
{ char * tau_ret_val =  old; __notify_intrinsic((void*)"char *icatalloc(char *, char *) C_end", (void *)&global_x); 
#line 4393
{ char * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char *icatalloc(char *, char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4393
 }

#line 3189

  else	oldsize = strlen(old);
  if (old == NULL)
    result = (char *) malloc(newsize + 1);
  else
    result = (char *) realloc((void *) old, oldsize + newsize + 1);
  if (result != NULL && new != NULL)
    (void) strcpy(result + oldsize, new);
  
#line 3197
{ char * tau_ret_val =  result; __notify_intrinsic((void*)"char *icatalloc(char *, char *) C_end", (void *)&global_x); 
#line 4406
{ char * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char *icatalloc(char *, char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4406
 }

#line 3197


#line 3198

}
	

#line 3198

#line 4417

}
	

#line 4417
}

static char *
icpyalloc (char *string)
{

#line 4421

__notify_intrinsic((void*)"char *icpyalloc(char *) C_start", (void *)&global_x);

#line 4421
{

#line 3202

__notify_intrinsic((void*)"char *icpyalloc(char *) C_start", (void *)&global_x);

#line 3202
{
  
#line 3203
{ char * tau_ret_val =  icatalloc((char *) NULL, string); __notify_intrinsic((void*)"char *icpyalloc(char *) C_end", (void *)&global_x); 
#line 4431
{ char * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char *icpyalloc(char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4431
 }

#line 3203


#line 3204

}
	

#line 3204

#line 4442

}
	

#line 4442
}

static char *
istrstr (char *lookin, char *lookfor)
{

#line 4446

__notify_intrinsic((void*)"char *istrstr(char *, char *) C_start", (void *)&global_x);

#line 4446
{

#line 3208

__notify_intrinsic((void*)"char *istrstr(char *, char *) C_start", (void *)&global_x);

#line 3208
{
  char *cp;
  size_t len;

  len = strlen(lookfor);
  for (cp = lookin; *cp != '\0'; ++cp)
    if (strncmp(cp, lookfor, len) == 0)
      
#line 3215
{ char * tau_ret_val =  cp; __notify_intrinsic((void*)"char *istrstr(char *, char *) C_end", (void *)&global_x); 
#line 4462
{ char * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char *istrstr(char *, char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4462
 }

#line 3215

  
#line 3216
{ char * tau_ret_val =  NULL; __notify_intrinsic((void*)"char *istrstr(char *, char *) C_end", (void *)&global_x); 
#line 4468
{ char * tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char *istrstr(char *, char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4468
 }

#line 3216


#line 3217

}
	

#line 3217

#line 4479

}
	

#line 4479
}

static void
freelist (char **cpp)
{

#line 4483

__notify_intrinsic((void*)"void freelist(char **) C_start", (void *)&global_x);

#line 4483
{

#line 3221

__notify_intrinsic((void*)"void freelist(char **) C_start", (void *)&global_x);

#line 3221
{
  int i;

  if (cpp == NULL)
    
#line 3225
{ __notify_intrinsic((void*)"void freelist(char **) C_end", (void *)&global_x); 
#line 4496
{ __notify_intrinsic((void*)"void freelist(char **) C_end", (void *)&global_x); return; }

#line 4496
 }

#line 3225

  for (i = 0; cpp[i] != NULL; ++i)
    {
      free(cpp[i]);
      cpp[i] = NULL;
    }

#line 3231

}
	

#line 3231

#line 4512

}
	

#line 4512
}

static char **
enlist (char **cpp, char *new, size_t len)
{

#line 4516

__notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_start", (void *)&global_x);

#line 4516
{

#line 3235

__notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_start", (void *)&global_x);

#line 3235
{
  int i, j;

  if (cpp == NULL)
    
#line 3239
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); 
#line 4529
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4529
 }

#line 3239

  if ((new = icpyalloc(new)) == NULL)
    {
      freelist(cpp);
      
#line 3243
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); 
#line 4538
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4538
 }

#line 3243

    }
  new[len] = '\0';
  /* Is there already something in the list that's new (or longer)? */
  for (i = 0; cpp[i] != NULL; ++i)
    if (istrstr(cpp[i], new) != NULL)
      {
	free(new);
	
#line 3251
{ char ** tau_ret_val =  cpp; __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); 
#line 4551
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4551
 }

#line 3251

      }
  /* Eliminate any obsoleted strings. */
  j = 0;
  while (cpp[j] != NULL)
    if (istrstr(new, cpp[j]) == NULL)
      ++j;
    else
      {
	free(cpp[j]);
	if (--i == j)
	  break;
	cpp[j] = cpp[i];
	cpp[i] = NULL;
      }
  /* Add the new string. */
  cpp = (char **) realloc((char *) cpp, (i + 2) * sizeof *cpp);
  if (cpp == NULL)
    
#line 3269
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); 
#line 4574
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4574
 }

#line 3269

  cpp[i] = new;
  cpp[i + 1] = NULL;
  
#line 3272
{ char ** tau_ret_val =  cpp; __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); 
#line 4582
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **enlist(char **, char *, size_t) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4582
 }

#line 3272


#line 3273

}
	

#line 3273

#line 4593

}
	

#line 4593
}

/* Given pointers to two strings, return a pointer to an allocated
   list of their distinct common substrings. Return NULL if something
   seems wild. */
static char **
comsubs (char *left, char *right)
{

#line 4600

__notify_intrinsic((void*)"char **comsubs(char *, char *) C_start", (void *)&global_x);

#line 4600
{

#line 3280

__notify_intrinsic((void*)"char **comsubs(char *, char *) C_start", (void *)&global_x);

#line 3280
{
  char **cpp;
  char *lcp;
  char *rcp;
  size_t i, len;

  if (left == NULL || right == NULL)
    
#line 3287
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **comsubs(char *, char *) C_end", (void *)&global_x); 
#line 4616
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **comsubs(char *, char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4616
 }

#line 3287

  cpp = (char **) malloc(sizeof *cpp);
  if (cpp == NULL)
    
#line 3290
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **comsubs(char *, char *) C_end", (void *)&global_x); 
#line 4624
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **comsubs(char *, char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4624
 }

#line 3290

  cpp[0] = NULL;
  for (lcp = left; *lcp != '\0'; ++lcp)
    {
      len = 0;
      rcp = strchr (right, *lcp);
      while (rcp != NULL)
	{
	  for (i = 1; lcp[i] != '\0' && lcp[i] == rcp[i]; ++i)
	    continue;
	  if (i > len)
	    len = i;
	  rcp = strchr (rcp + 1, *lcp);
	}
      if (len == 0)
	continue;
      if ((cpp = enlist(cpp, lcp, len)) == NULL)
	break;
    }
  
#line 3309
{ char ** tau_ret_val =  cpp; __notify_intrinsic((void*)"char **comsubs(char *, char *) C_end", (void *)&global_x); 
#line 4648
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **comsubs(char *, char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4648
 }

#line 3309


#line 3310

}
	

#line 3310

#line 4659

}
	

#line 4659
}

static char **
addlists (char **old, char **new)
{

#line 4663

__notify_intrinsic((void*)"char **addlists(char **, char **) C_start", (void *)&global_x);

#line 4663
{

#line 3314

__notify_intrinsic((void*)"char **addlists(char **, char **) C_start", (void *)&global_x);

#line 3314
{
  int i;

  if (old == NULL || new == NULL)
    
#line 3318
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **addlists(char **, char **) C_end", (void *)&global_x); 
#line 4676
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **addlists(char **, char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4676
 }

#line 3318

  for (i = 0; new[i] != NULL; ++i)
    {
      old = enlist(old, new[i], strlen(new[i]));
      if (old == NULL)
	break;
    }
  
#line 3325
{ char ** tau_ret_val =  old; __notify_intrinsic((void*)"char **addlists(char **, char **) C_end", (void *)&global_x); 
#line 4688
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **addlists(char **, char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4688
 }

#line 3325


#line 3326

}
	

#line 3326

#line 4699

}
	

#line 4699
}

/* Given two lists of substrings, return a new list giving substrings
   common to both. */
static char **
inboth (char **left, char **right)
{

#line 4705

__notify_intrinsic((void*)"char **inboth(char **, char **) C_start", (void *)&global_x);

#line 4705
{

#line 3332

__notify_intrinsic((void*)"char **inboth(char **, char **) C_start", (void *)&global_x);

#line 3332
{
  char **both;
  char **temp;
  int lnum, rnum;

  if (left == NULL || right == NULL)
    
#line 3338
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); 
#line 4720
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4720
 }

#line 3338

  both = (char **) malloc(sizeof *both);
  if (both == NULL)
    
#line 3341
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); 
#line 4728
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4728
 }

#line 3341

  both[0] = NULL;
  for (lnum = 0; left[lnum] != NULL; ++lnum)
    {
      for (rnum = 0; right[rnum] != NULL; ++rnum)
	{
	  temp = comsubs(left[lnum], right[rnum]);
	  if (temp == NULL)
	    {
	      freelist(both);
	      
#line 3351
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); 
#line 4743
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4743
 }

#line 3351

	    }
	  both = addlists(both, temp);
	  freelist(temp);
	  free(temp);
	  if (both == NULL)
	    
#line 3357
{ char ** tau_ret_val =  NULL; __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); 
#line 4754
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4754
 }

#line 3357

	}
    }
  
#line 3360
{ char ** tau_ret_val =  both; __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); 
#line 4762
{ char ** tau_ret_val =  (tau_ret_val); __notify_intrinsic((void*)"char **inboth(char **, char **) C_end", (void *)&global_x); return (tau_ret_val); }

#line 4762
 }

#line 3360


#line 3361

}
	

#line 3361

#line 4773

}
	

#line 4773
}

typedef struct
{
  char **in;
  char *left;
  char *right;
  char *is;
} must;

static void
resetmust (must *mp)
{

#line 4785

__notify_intrinsic((void*)"void resetmust(must *) C_start", (void *)&global_x);

#line 4785
{

#line 3373

__notify_intrinsic((void*)"void resetmust(must *) C_start", (void *)&global_x);

#line 3373
{
  mp->left[0] = mp->right[0] = mp->is[0] = '\0';
  freelist(mp->in);

#line 3376

}
	

#line 3376

#line 4802

}
	

#line 4802
}

static void
dfamust (struct dfa *d)
{

#line 4806

__notify_intrinsic((void*)"void dfamust(struct dfa *) C_start", (void *)&global_x);

#line 4806
{

#line 3380

__notify_intrinsic((void*)"void dfamust(struct dfa *) C_start", (void *)&global_x);

#line 3380
{
  must *musts;
  must *mp;
  char *result;
  int ri;
  int i;
  int exact;
  token t;
  static must must0;
  struct dfamust *dm;
  static char empty_string[] = "";

  result = empty_string;
  exact = 0;
  musts = (must *) malloc((d->tindex + 1) * sizeof *musts);
  if (musts == NULL)
    
#line 3396
{ __notify_intrinsic((void*)"void dfamust(struct dfa *) C_end", (void *)&global_x); 
#line 4831
{ __notify_intrinsic((void*)"void dfamust(struct dfa *) C_end", (void *)&global_x); return; }

#line 4831
 }

#line 3396

  mp = musts;
  for (i = 0; i <= d->tindex; ++i)
    mp[i] = must0;
  for (i = 0; i <= d->tindex; ++i)
    {
      mp[i].in = (char **) malloc(sizeof *mp[i].in);
      mp[i].left = malloc(2);
      mp[i].right = malloc(2);
      mp[i].is = malloc(2);
      if (mp[i].in == NULL || mp[i].left == NULL ||
	  mp[i].right == NULL || mp[i].is == NULL)
	goto done;
      mp[i].left[0] = mp[i].right[0] = mp[i].is[0] = '\0';
      mp[i].in[0] = NULL;
    }
#ifdef DEBUG
  fprintf(stderr, "dfamust:\n");
  for (i = 0; i < d->tindex; ++i)
    {
      fprintf(stderr, " %d:", i);
      prtok(d->tokens[i]);
    }
  putc('\n', stderr);
#endif
  for (ri = 0; ri < d->tindex; ++ri)
    {
      switch (t = d->tokens[ri])
	{
	case LPAREN:
	case RPAREN:
	  goto done;		/* "cannot happen" */
	case EMPTY:
	case BEGLINE:
	case ENDLINE:
	case BEGWORD:
	case ENDWORD:
	case LIMWORD:
	case NOTLIMWORD:
	case BACKREF:
	  resetmust(mp);
	  break;
	case STAR:
	case QMARK:
	  if (mp <= musts)
	    goto done;		/* "cannot happen" */
	  --mp;
	  resetmust(mp);
	  break;
	case OR:
	case ORTOP:
	  if (mp < &musts[2])
	    goto done;		/* "cannot happen" */
	  {
	    char **new;
	    must *lmp;
	    must *rmp;
	    int j, ln, rn, n;

	    rmp = --mp;
	    lmp = --mp;
	    /* Guaranteed to be.  Unlikely, but. . . */
	    if (strcmp(lmp->is, rmp->is) != 0)
	      lmp->is[0] = '\0';
	    /* Left side--easy */
	    i = 0;
	    while (lmp->left[i] != '\0' && lmp->left[i] == rmp->left[i])
	      ++i;
	    lmp->left[i] = '\0';
	    /* Right side */
	    ln = strlen(lmp->right);
	    rn = strlen(rmp->right);
	    n = ln;
	    if (n > rn)
	      n = rn;
	    for (i = 0; i < n; ++i)
	      if (lmp->right[ln - i - 1] != rmp->right[rn - i - 1])
		break;
	    for (j = 0; j < i; ++j)
	      lmp->right[j] = lmp->right[(ln - i) + j];
	    lmp->right[j] = '\0';
	    new = inboth(lmp->in, rmp->in);
	    if (new == NULL)
	      goto done;
	    freelist(lmp->in);
	    free(lmp->in);
	    lmp->in = new;
	  }
	  break;
	case PLUS:
	  if (mp <= musts)
	    goto done;		/* "cannot happen" */
	  --mp;
	  mp->is[0] = '\0';
	  break;
	case END:
	  if (mp != &musts[1])
	    goto done;		/* "cannot happen" */
	  for (i = 0; musts[0].in[i] != NULL; ++i)
	    if (strlen(musts[0].in[i]) > strlen(result))
	      result = musts[0].in[i];
	  if (strcmp(result, musts[0].is) == 0)
	    exact = 1;
	  goto done;
	case CAT:
	  if (mp < &musts[2])
	    goto done;		/* "cannot happen" */
	  {
	    must *lmp;
	    must *rmp;

	    rmp = --mp;
	    lmp = --mp;
	    /* In.  Everything in left, plus everything in
	       right, plus catenation of
	       left's right and right's left. */
	    lmp->in = addlists(lmp->in, rmp->in);
	    if (lmp->in == NULL)
	      goto done;
	    if (lmp->right[0] != '\0' &&
		rmp->left[0] != '\0')
	      {
		char *tp;

		tp = icpyalloc(lmp->right);
		if (tp == NULL)
		  goto done;
		tp = icatalloc(tp, rmp->left);
		if (tp == NULL)
		  goto done;
		lmp->in = enlist(lmp->in, tp,
				 strlen(tp));
		free(tp);
		if (lmp->in == NULL)
		  goto done;
	      }
	    /* Left-hand */
	    if (lmp->is[0] != '\0')
	      {
		lmp->left = icatalloc(lmp->left,
				      rmp->left);
		if (lmp->left == NULL)
		  goto done;
	      }
	    /* Right-hand */
	    if (rmp->is[0] == '\0')
	      lmp->right[0] = '\0';
	    lmp->right = icatalloc(lmp->right, rmp->right);
	    if (lmp->right == NULL)
	      goto done;
	    /* Guaranteed to be */
	    if (lmp->is[0] != '\0' && rmp->is[0] != '\0')
	      {
		lmp->is = icatalloc(lmp->is, rmp->is);
		if (lmp->is == NULL)
		  goto done;
	      }
	    else
	      lmp->is[0] = '\0';
	  }
	  break;
	default:
	  if (t < END)
	    {
	      /* "cannot happen" */
	      goto done;
	    }
	  else if (t == '\0')
	    {
	      /* not on *my* shift */
	      goto done;
	    }
	  else if (t >= CSET
#ifdef MBS_SUPPORT
		   || t == ANYCHAR
		   || t == MBCSET
#endif /* MBS_SUPPORT */
		   )
	    {
	      /* easy enough */
	      resetmust(mp);
	    }
	  else
	    {
	      /* plain character */
	      resetmust(mp);
	      mp->is[0] = mp->left[0] = mp->right[0] = t;
	      mp->is[1] = mp->left[1] = mp->right[1] = '\0';
	      mp->in = enlist(mp->in, mp->is, (size_t)1);
	      if (mp->in == NULL)
		goto done;
	    }
	  break;
	}
#ifdef DEBUG
      fprintf(stderr, " node: %d:", ri);
      prtok(d->tokens[ri]);
      fprintf(stderr, "\n  in:");
      for (i = 0; mp->in[i]; ++i)
	fprintf(stderr, " \"%s\"", mp->in[i]);
      fprintf(stderr, "\n  is: \"%s\"\n", mp->is);
      fprintf(stderr, "  left: \"%s\"\n", mp->left);
      fprintf(stderr, "  right: \"%s\"\n", mp->right);
#endif
      ++mp;
    }
 done:
  if (strlen(result))
    {
      MALLOC(dm, struct dfamust, 1);
      dm->exact = exact;
      MALLOC(dm->must, char, strlen(result) + 1);
      strcpy(dm->must, result);
      dm->next = d->musts;
      d->musts = dm;
    }
  mp = musts;
  for (i = 0; i <= d->tindex; ++i)
    {
      freelist(mp[i].in);
      free(mp[i].in);
      free(mp[i].left);
      free(mp[i].right);
      free(mp[i].is);
    }
  free(mp);

#line 3622

}
	

#line 3622

#line 5067

}
	

#line 5067
}
/* vim:set shiftwidth=2: */