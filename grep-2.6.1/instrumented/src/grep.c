
#line 1 "./instrumented/./src/grep.c"
#include "config.h"
#include "search.h"

static void
Gcompile (char const *pattern, size_t size)
{

#line 6

__notify_intrinsic((void*)"void Gcompile(const char *, size_t) C_start", (void *)&global_x);

#line 6
{
  GEAcompile (pattern, size,
	      RE_SYNTAX_GREP
	      | RE_HAT_LISTS_NOT_NEWLINE
	      | RE_NO_EMPTY_RANGES);

#line 11

}
	

#line 11
}

static void
Ecompile (char const *pattern, size_t size)
{

#line 15

__notify_intrinsic((void*)"void Ecompile(const char *, size_t) C_start", (void *)&global_x);

#line 15
{
  GEAcompile (pattern, size, RE_SYNTAX_POSIX_EGREP | RE_NO_EMPTY_RANGES);

#line 17

}
	

#line 17
}

static void
Acompile (char const *pattern, size_t size)
{

#line 21

__notify_intrinsic((void*)"void Acompile(const char *, size_t) C_start", (void *)&global_x);

#line 21
{
  GEAcompile (pattern, size, RE_SYNTAX_AWK);

#line 23

}
	

#line 23
}

struct matcher const matchers[] = {
  { "grep",    Gcompile, EGexecute },
  { "egrep",   Ecompile, EGexecute },
  { "awk",     Acompile, EGexecute },
  { "fgrep",   Fcompile, Fexecute },
  { "perl",    Pcompile, Pexecute },
  { NULL, NULL, NULL },
};

const char before_options[] =
N_("PATTERN is, by default, a basic regular expression (BRE).\n");
const char after_options[] =
N_("`egrep' means `grep -E'.  `fgrep' means `grep -F'.\n\
Direct invocation as either `egrep' or `fgrep' is deprecated.\n");
