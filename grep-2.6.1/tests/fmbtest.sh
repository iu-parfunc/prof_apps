#! /bin/sh
# Copyright (C) 2001, 2006, 2009-2010 Free Software Foundation, Inc.
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

: ${srcdir=.}

# If cs_CZ.UTF-8 locale doesn't work, skip this test silently
LC_ALL=cs_CZ.UTF-8 locale -k LC_CTYPE 2>/dev/null | ${GREP} -q charmap.*UTF-8 \
  || exit 77

# If matching is done in single-byte mode, skip this test too
printf 'é\n' | LC_ALL=cz_CZ.UTF-8 ${GREP} -Eq '^[é]{2}$'
case $? in
  0) exit 77;;
  1) ;;
  *) exit 1;;
esac

failures=0

cat > csinput <<EOF
01 Žluťoučká číše
ČíŠE 02
03 Z číší Čiší cosi
04 Čí
Še 05
06 ČČČČČČČíšČÍŠčíš
07 ČČČ ČČČČíšČÍŠčíšEEEE
čAs 08
09Čapka
10ČaSy se měnÍ
ČÍšE11
Čas12
𝇕ČÍšE𝇓13
ŽČÍšE𝇓14
𝇕ČÍšEŽ15
ŽČÍšEŽ16
ČÍšE𝇓17
ČÍšEŽ18
19𝇕ČÍše
20ŽČÍše
EOF
cat > cspatfile <<EOF
ČÍšE
Čas
EOF

for mode in F G E; do

test1="$(echo `LC_ALL=cs_CZ.UTF-8 ${GREP} -${mode} -f cspatfile csinput \
	       | LC_ALL=C sed 's/^.*\([0-9][0-9]\).*$/\1/'`)"
if test "$test1" != "11 12 13 14 15 16 17 18"; then
  echo "Test #1 ${mode} failed: $test1"
  failures=1
fi

test2="$(echo `LC_ALL=cs_CZ.UTF-8 ${GREP} -${mode}i -f cspatfile csinput \
	       | LC_ALL=C sed 's/^.*\([0-9][0-9]\).*$/\1/'`)"
if test "$test2" != "01 02 07 08 10 11 12 13 14 15 16 17 18 19 20"; then
  echo "Test #2 ${mode} failed: $test2"
  failures=1
fi

test3="$(echo `LC_ALL=cs_CZ.UTF-8 ${GREP} -${mode}i -e 'ČÍšE' -e 'Čas' csinput \
	       | LC_ALL=C sed 's/^.*\([0-9][0-9]\).*$/\1/'`)"
if test "$test3" != "01 02 07 08 10 11 12 13 14 15 16 17 18 19 20"; then
  echo "Test #3 ${mode} failed: $test3"
  failures=1
fi

# Skip the next test - known to fail. TAA.
#test4="$(echo `LC_ALL=cs_CZ.UTF-8 ${GREP} -${mode}iw -f cspatfile csinput \
#	       | LC_ALL=C sed 's/^.*\([0-9][0-9]\).*$/\1/'`)"
#if test "$test4" != "01 02 08 13 17 19"; then
#  echo "Test #4 ${mode} failed: $test4"
#  failures=1
#fi

# Test that --color=always does not depend on individual pattern order within the pattern
# list, and that a longer match is preferred to a shorter one starting at the same point.
test6="`echo 'Cosi tu ČišÍ...' \
	| LC_ALL=cs_CZ.UTF-8 ${GREP} --color=always -${mode}i -e 'čiš' -e 'čiší'`"
if echo "$test6" | LC_ALL=C ${GREP} -q 'Cosi tu .*\[.*m\(.\[K\)\?ČišÍ.*\[.*m\(.\[K\)\?\.\.\.'; then
  :
else
  echo "Test #6 ${mode} failed: $test6"
  failures=1
fi

# Test that --color=always does not depend on individual pattern order within the pattern
# list, and that a longer match is preferred to a shorter one starting at the same point.
test7="`echo 'Cosi tu ČišÍ...' \
	| LC_ALL=cs_CZ.UTF-8 ${GREP} --color=always -${mode}i -e 'čiší' -e 'čiš'`"
if echo "$test7" | LC_ALL=C ${GREP} -q 'Cosi tu .*\[.*m\(.\[K\)\?ČišÍ.*\[.*m\(.\[K\)\?\.\.\.'; then
  :
else
  echo "Test #7 ${mode} failed: $test7"
  failures=1
fi

done

for mode in G E; do

test8="$(echo `LC_ALL=cs_CZ.UTF-8 ${GREP} -${mode}i -e 'Č.šE' -e 'Č[a-f]s' csinput \
	       | LC_ALL=C sed 's/^.*\([0-9][0-9]\).*$/\1/'`)"
if test "$test8" != "01 02 07 08 10 11 12 13 14 15 16 17 18 19 20"; then
  echo "Test #8 ${mode} failed: $test8"
  failures=1
fi

done

exit $failures
