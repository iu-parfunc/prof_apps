#!/usr/bin/python
import re
import fileinput
import operator

# line = "Cats are smarter than dogs"
def compare(file1, file2):
  f1 = {}
  f2 = {}
  for line in fileinput.input(file1):
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

  for line in fileinput.input(file2):
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

  # print "Diff count : ", file1, file2, diffCount
  return diffCount

def main():
  benches = ['h264ref-9.3', 'perl-5.8.7', 'hmmer', 'lbm', 'nbody', 'blackscholes', 'fluid', 'hull'] 
  overheads = ['3', '5', '10']
  rounds = ['1', '2', '3']

  for bench in benches:
    for overhead in overheads:
      for round in rounds:
        trace = bench + "-trace.txt"
        sample = "prof-swarm-" + bench + round + overhead + ".out"

        diff = compare(trace, sample)
        print trace, sample, diff
 
if __name__ == "__main__":
      main()
