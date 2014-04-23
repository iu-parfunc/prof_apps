
#line 1 "./instrumented/./src/kwsearch.c"
/* kwsearch.c - searching subroutines using kwset for grep.
   Copyright 1992, 1998, 2000, 2007, 2009-2010 Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

/* Written August 1992 by Mike Haertel. */

#include "config.h"
#include "search.h"

/* For -w, we also consider _ to be word constituent.  */
#define WCHAR(C) (ISALNUM(C) || (C) == '_')

/* KWset compiled pattern.  For Ecompile and Gcompile, we compile
   a list of strings, at least one of which is known to occur in
   any string matching the regexp. */
static kwset_t kwset;

void
Fcompile (char const *pattern, size_t size)
{

#line 34

__notify_intrinsic((void*)"void Fcompile(const char *, size_t) C_start", (void *)&global_x);

#line 34
{
  char const *beg, *end, *lim, *err, *pat;
  size_t psize;

  kwsinit (&kwset);
  psize = size;
#ifdef MBS_SUPPORT
  if (match_icase && MB_CUR_MAX > 1)
    pat = mbtolower (pattern, &psize);
  else
#endif
    pat = pattern;

  beg = pat;
  do
    {
      for (lim = beg;; ++lim)
	{
	  end = lim;
	  if (lim >= pat + psize)
	    break;
	 if (*lim == '\n')
	   {
	     lim++;
	     break;
	   }
#if HAVE_DOS_FILE_CONTENTS
	 if (*lim == '\r' && lim + 1 < pat + psize && lim[1] == '\n')
	   {
	     lim += 2;
	     break;
	   }
#endif
	}

      if ((err = kwsincr (kwset, beg, end - beg)) != NULL)
	error (EXIT_TROUBLE, 0, "%s", err);
      beg = lim;
    }
  while (beg < pat + psize);

  if ((err = kwsprep (kwset)) != NULL)
    error (EXIT_TROUBLE, 0, "%s", err);

#line 77

}
	

#line 77
}

size_t
Fexecute (char const *buf, size_t size, size_t *match_size,
	  char const *start_ptr)
{

#line 82

__notify_intrinsic((void*)"size_t Fexecute(const char *, size_t, size_t *, const char *) C_start", (void *)&global_x);

#line 82
{
  char const *beg, *try, *end, *mb_start;
  size_t len;
  char eol = eolbyte;
  struct kwsmatch kwsmatch;
  size_t ret_val;
#ifdef MBS_SUPPORT
  if (MB_CUR_MAX > 1)
    {
      if (match_icase)
        {
          char *case_buf = mbtolower (buf, &size);
	  if (start_ptr)
	    start_ptr = case_buf + (start_ptr - buf);
          buf = case_buf;
        }
    }
#endif /* MBS_SUPPORT */

  for (mb_start = beg = start_ptr ? start_ptr : buf; beg <= buf + size; beg++)
    {
      size_t offset = kwsexec (kwset, beg, buf + size - beg, &kwsmatch);
      if (offset == (size_t) -1)
	goto failure;
#ifdef MBS_SUPPORT
      if (MB_CUR_MAX > 1 && is_mb_middle (&mb_start, beg + offset, buf + size))
        {
          beg = mb_start - 1;
          continue; /* It is a part of multibyte character.  */
        }
#endif /* MBS_SUPPORT */
      beg += offset;
      len = kwsmatch.size[0];
      if (start_ptr && !match_words)
	goto success_in_beg_and_len;
      if (match_lines)
	{
	  if (beg > buf && beg[-1] != eol)
	    continue;
	  if (beg + len < buf + size && beg[len] != eol)
	    continue;
	  goto success;
	}
      else if (match_words)
	for (try = beg; len; )
	  {
	    if (try > buf && WCHAR((unsigned char) try[-1]))
	      break;
	    if (try + len < buf + size && WCHAR((unsigned char) try[len]))
	      {
		offset = kwsexec (kwset, beg, --len, &kwsmatch);
		if (offset == (size_t) -1)
		  break;
		try = beg + offset;
		len = kwsmatch.size[0];
	      }
	    else if (!start_ptr)
	      goto success;
	    else
	      goto success_in_beg_and_len;
	  } /* for (try) */
      else
	goto success;
    } /* for (beg in buf) */

 failure:
  ret_val = -1;
  goto out;

 success:
  if ((end = memchr (beg + len, eol, (buf + size) - (beg + len))) != NULL)
    end++;
  else
    end = buf + size;
  while (buf < beg && beg[-1] != eol)
    --beg;
  len = end - beg;
 success_in_beg_and_len:
  *match_size = len;
  ret_val = beg - buf;
 out:
  
#line 163
{ size_t tau_ret_val =  ret_val; __notify_intrinsic((void*)"size_t Fexecute(const char *, size_t, size_t *, const char *) C_end", (void *)&global_x); return (tau_ret_val); }

#line 163


#line 164

}
	

#line 164
}
