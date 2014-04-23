
#line 1 "./instrumented/./src/grep.c"
#include "config.h"
#include "search.h"

static void
Gcompile (char const *pattern, size_t size)
{

#line 8

__notify_intrinsic((void*)"void Gcompile(const char *, size_t) C_start", (void *)&global_x);

#line 8
{
  GEAcompile (pattern, size,
	      RE_SYNTAX_GREP
	      | RE_HAT_LISTS_NOT_NEWLINE
	      | RE_NO_EMPTY_RANGES);

#line 13

}
	

#line 13
}

static void
Ecompile (char const *pattern, size_t size)
{

#line 17

__notify_intrinsic((void*)"void Ecompile(const char *, size_t) C_start", (void *)&global_x);

#line 17
{
  GEAcompile (pattern, size, RE_SYNTAX_POSIX_EGREP | RE_NO_EMPTY_RANGES);

#line 19

}
	

#line 19
}

static void
Acompile (char const *pattern, size_t size)
{

#line 23

__notify_intrinsic((void*)"void Acompile(const char *, size_t) C_start", (void *)&global_x);

#line 23
{
  GEAcompile (pattern, size, RE_SYNTAX_AWK);

#line 25

}
	

#line 25
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
