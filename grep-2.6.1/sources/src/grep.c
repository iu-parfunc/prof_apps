#include "../config.h"
#include "search.h"

int global_x;

static void
Gcompile (char const *pattern, size_t size)
{
  GEAcompile (pattern, size, RE_SYNTAX_GREP | RE_NO_EMPTY_RANGES);
  return;
}

static void
Ecompile (char const *pattern, size_t size)
{
  GEAcompile (pattern, size, RE_SYNTAX_POSIX_EGREP | RE_NO_EMPTY_RANGES);
  return;
}

static void
Acompile (char const *pattern, size_t size)
{
  GEAcompile (pattern, size, RE_SYNTAX_AWK);
  return;
}

static void
GAcompile (char const *pattern, size_t size)
{
  GEAcompile (pattern, size, RE_SYNTAX_GNU_AWK);
  return;
}

static void
PAcompile (char const *pattern, size_t size)
{
  GEAcompile (pattern, size, RE_SYNTAX_POSIX_AWK);
  return;
}

struct matcher const matchers[] = {
  { "grep",    Gcompile, EGexecute },
  { "egrep",   Ecompile, EGexecute },
  { "awk",     Acompile, EGexecute },
  { "gawk",    GAcompile, EGexecute },
  { "posixawk", PAcompile, EGexecute },
  { "fgrep",   Fcompile, Fexecute },
  { "perl",    Pcompile, Pexecute },
  { NULL, NULL, NULL },
};

const char before_options[] =
N_("PATTERN is, by default, a basic regular expression (BRE).\n");
const char after_options[] =
N_("'egrep' means 'grep -E'.  'fgrep' means 'grep -F'.\n\
Direct invocation as either 'egrep' or 'fgrep' is deprecated.\n");
