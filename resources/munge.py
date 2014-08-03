import sys
import getopt

leaf_raw = dict()
leaf_stats = dict()
dyn_raw = dict()
dyn_stats = dict()
func_overhead = dict()
overhead_histogram = dict()
result = dict()

# User arguments
metric = "MIN"
outputfile = "results.txt"

def read_data(file, raw_data):
  for line in open(file):
    print ".",
    tokens = line.split(',',4) # tokens[0] = 'name' tokens[1] = 'min' tokens[2] = 'max' tokens[3] = 'Avg'
    if tokens[0].rstrip() in raw_data:
      func_data = raw_data[tokens[0].rstrip()]
      min_data = func_data[0]
      min_data.append(tokens[1].rstrip())
      max_data = func_data[1]
      max_data.append(tokens[2].rstrip())
      avg_data = func_data[2]
      avg_data.append(tokens[3].rstrip())
    else:
      arr = []
      arr.append([])
      arr.append([])
      arr.append([])
      arr[0].append(tokens[1].rstrip())
      arr[1].append(tokens[2].rstrip())
      arr[2].append(tokens[3].rstrip())
      raw_data[tokens[0].rstrip()] = arr

def munge(raw_data, stats):
  for key, value in raw_data.iteritems():
    print ".",
    min_list = value[0];
    max_list = value[1];
    avg_list = value[2];
  
    min_list.sort()
    max_list.sort()
    avg_list.sort()

    min = 0
    max = 0
    sum = 0
    min_stats = []
    if len(min_list) >= 3:
      median = int(min_list[len(min_list)/2])
      for i in range(len(min_list)):
        val = int(min_list[i])
        sum += val 
        if min == 0 or min > val:
          min = val 
        if max < val:
          max =  val
      avg = sum / len(min_list)
      min_stats.append(min)
      min_stats.append(max)
      min_stats.append(avg)
      min_stats.append(median)

    min = 0
    max = 0
    sum = 0
    max_stats = []
    if len(max_list) >= 3:
      median = int(max_list[len(max_list)/2])
      for i in range(len(max_list)):
        val = int(max_list[i])
        sum += val 
        if min == 0 or min > val:
          min = val 
        if max < val:
          max = val
        avg = sum / len(max_list)
      max_stats.append(min)
      max_stats.append(max)
      max_stats.append(avg)
      max_stats.append(median)

    min = 0
    max = 0
    sum = 0
    avg_stats = []
    if len(avg_list) >= 3:
      median = float(avg_list[len(avg_list)/2])
      for i in range(len(avg_list)):
        val = float(avg_list[i])
        sum += val 
        if min == 0 or min > val:
          min = val 
        if max < val:
          max = val 
      avg = sum / len(avg_list)
      avg_stats.append(min)
      avg_stats.append(max)
      avg_stats.append(avg)
      avg_stats.append(median)

    if (len(min_list) >= 3):
      count = [len(min_list)]
      func_stats = [count, min_stats, max_stats, avg_stats]
      stats[key] = func_stats

def crunch(data_set_1, data_set_2):
  f = open(outputfile, "w")
  f1 = open("extended_results.txt","w")
  for key, set_1_value in data_set_1.iteritems():
    if metric == "MIN":
      set_1_min_stats = set_1_value[1]
      set_1_min_median = set_1_min_stats[3]
      set_2_value = data_set_2.get(key,0)
      if set_2_value != 0:
        set_2_min_stats = set_2_value[1]
        set_2_min_median = set_2_min_stats[3]
        difference = (set_1_min_median-set_2_min_median) * 100/float(set_2_min_median)
        percentage = int(difference)
        func_overhead[key] = percentage 
        f1.write("%35s,%3d\n" % (key, percentage))
        if percentage in overhead_histogram:
          overhead_histogram[percentage] += 1 
        else:
          overhead_histogram[percentage] = 1 
    elif metric == "AVG":
      set_1_avg_stats = set_1_value[2]
      set_1_avg_median = set_1_avg_stats[3]
      set_2_value = data_set_2.get(key,0)
      if set_2_value != 0:
        set_2_avg_stats = set_2_value[1]
        set_2_avg_median = set_2_avg_stats[3]
        difference = (set_1_avg_median-set_2_avg_median) * 100/float(set_2_avg_median)
        percentage = int(difference)
        func_overhead[key] = percentage 
        f1.write("%35s,%3d\n" % (key, percentage))
        if percentage in overhead_histogram:
          overhead_histogram[percentage] += 1 
        else:
          overhead_histogram[percentage] = 1 
  for key, value in overhead_histogram.iteritems():
    f.write("%3d,%3d\n" % (key, value))

def main(argv):

  try:
    opts, args = getopt.getopt(argv,"hm:o:")
  except getopt.GetoptError:
    print 'munge.py -m <metric[MIN,AVG]> -o <outputfile>'
    sys.exit(2)

  for opt, arg in opts:
    if opt == '-h':
      print 'munge.py -m <metric[MIN,AVG]> -o <outputfile>'
      sys.exit()
    elif opt in ("-m"):
      global metric 
      metric = arg
    elif opt in ("-o"):
      global outputfile 
      outputfile = arg

  print "Reading leaf node data ...\n"
  read_data("filtered.out", leaf_raw)
  print "\nRead data for %d functions.\n\n" % len(leaf_raw)

  print "Munging leaf node data ...\n"
  munge(leaf_raw, leaf_stats)
  print "\nMunging data for %d functions.\n\n" % len(leaf_stats)
#  print leaf_stats

  print "Reading dynprof data ...\n"
  read_data("unfiltered.out", dyn_raw)
  print "\nRead data for %d functions.\n\n" % len(dyn_raw)

  print "Munging dynaprof data ...\n"
  munge(dyn_raw, dyn_stats)
  print "\nMunging data for %d functions.\n\n" % len(dyn_stats)
#  print dyn_stats

  print "Doing final analysis..\n"
  crunch(dyn_stats, leaf_stats)
  print "Result written to %s......" % outputfile

if __name__ == "__main__":
     main(sys.argv[1:])
