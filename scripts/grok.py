#!/usr/bin/python
import re
import fileinput
import operator

# line = "Cats are smarter than dogs"
f1 = {}
f2 = {}
for line in fileinput.input(['prof.out']):
# line = "Function Name: ParseContent Count 102 Deactivation Count : 0 Avg time (cycles) : 7456"
  matchObj = re.match( r'Function Name: (.*) Count ([0-9]+)', line, re.M|re.I)
  if matchObj:
    function = matchObj.group(1)
    count = int(matchObj.group(2))
    if count in f1:
      f1[count].append(function)
    else:
      f1[count] = [function]
  else:
   print "No match!!"
  f1_bucketed = sorted(f1.items(), key=operator.itemgetter(0))

for line in fileinput.input(['prof1.out']):
# line = "Function Name: ParseContent Count 102 Deactivation Count : 0 Avg time (cycles) : 7456"
  matchObj = re.match( r'Function Name: (.*) Count ([0-9]+)', line, re.M|re.I)
  if matchObj:
    function = matchObj.group(1)
    count = int(matchObj.group(2))
    if count in f2:
      f2[count].append(function)
    else:
      f2[count] = [function]
  else:
   print "No match!!"
  f2_bucketed = sorted(f2.items(), key=operator.itemgetter(0))

f1_sorted = []
for i, val in enumerate(f1_bucketed):
  val[1].sort()
  f1_sorted.append(val[1])

f2_sorted = []
for i, val in enumerate(f2_bucketed):
  val[1].sort()
  f2_sorted.append(val[1])

print "<<<<>>>>"

diffCount = 0
for i, val in enumerate(f1_sorted):
  if val != f2_sorted[i]:
    print val, f2_sorted[i]
    diffCount += 1

print "Diff count" , diffCount



