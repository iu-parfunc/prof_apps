#!/usr/bin/python
import re
import fileinput
import os
import sys

class cd:
  "Context manager for changing the current working directory"
  def __init__(self, newPath):
    self.newPath = os.path.expanduser(newPath)

  def __enter__(self):
    self.savedPath = os.getcwd()
    os.chdir(self.newPath)

  def __exit__(self, etype, value, traceback):
    os.chdir(self.savedPath)

def get_min_time(sample_file, function):
  finput = fileinput.input(sample_file)
  for line in finput:
    regex = "%s,([0-9]+),([0-9]+),*" % function
    matchObj = re.match(r'%s' % regex, line, re.M|re.I)
    if matchObj:
      min_time = int(matchObj.group(2))
      finput.close()
      return min_time
  print "Function %s not found in %s" % (function, sample_file)
  finput.close()
  # sys.exit(1)

def main():
  # benches = ['h264ref-9.3', 'perl-5.8.7', 'bzip-1.0.3',  'hmmer', 'lbm', 'nbody', 'blackscholes', 'fluid', 'hull']
  # benches = ['h264ref-9.3' , 'hmmer', 'lbm', 'perl-5.8.7', 'bzip-1.0.3', 'sjeng']
  benches = ['h264ref-9.3']
  rounds = ['1', '2', '3']
  overheads = ['3', '5', '10']
  heavy_hitters = {'h264ref-9.3' : ['FastLine16Y_11','FastPelY_14','PutPel_14', 'SATD', 'UMVLine16Y_11', 'UMVPelY_14'],
                   'hmmer' : ['FCHoose', 'Gaussrandom', 'sre_malloc', 'sre_random', 'SymbolIndex', 'toupper'],
                   'lbm' : ['LBM_initializeGrid','LBM_initializeSpecialCell','LBM_loadObstacleFile', 'LBM_showGridStatistics', 'LBM_performStreamCollide', 'LBM_swapGrids'],
                   'nbody' : ['forceTo','_vect3d<double>::operator*(double)','_vect3d<double>::operator+(_vect3d<double>, dot', '_point3d<double>::operator-(_point3d<double>)', '_vect3d<double>::_vect3d(double, double, double)', 'dot'],
                   'perl-5.8.7' : ['Perl_sv_grow','Perl_sv_clear','Perl_sv_upgrade', 'S_regtry', 'Perl_sv_free', 'S_regmatch'],
                   'sjeng' : ['remove_one','make','unmake', 'add_move', 'push_king', 'Pawn', 'push_slidE'],
                   'bzip' : ['mainGtU','bsW','mainSimpleSort', 'add_pair_to_block', 'mmed3'],
                   'fluid' : ['Vec3::operator-=(Vec3 const&)','Vec3::operator+=(Vec3 const&)','Vec3::operator*(float)', 'const GetLengthSq', 'Vec3::operator-(Vec3 const&)', 'Vec3::Vec3(float, float, float)'],
                   'blackscholes' : ['main','bs_thread','BlkSchlsEqEuroNoDiv', 'CNDF'],
                   'CNDFhull' : ['cross','triArea','_vect2d', '_point2d<double>::operator-(_point2d<double>)', 'isSpace']}

  RESULTS = "/u/budkahaw/Builds/ubiprof/groundtruth"
  # analysis = "Benchmark,Function,"
  analysis = ""
  # for round in rounds:
  #   analysis += ",Min%s" % round
  # analysis += ",MinMin\n"

  with cd(RESULTS):
    for bench in benches:
      for heavy_hitter in heavy_hitters.get(bench):
        analysis += "%s,%s" % (bench, heavy_hitter) 
        min_times = []
        for round in rounds:
          sample_file = "prof-wolverine.soic.indiana.edu-" + bench + "-" + round + "-" + heavy_hitter + ".out"
          print "Processing %s..\n" % sample_file 
          min_times.append(get_min_time(sample_file, heavy_hitter)) 
          analysis += ",%s" % min_times[int(round) - 1]
        analysis += ",%s\n" % min(min_times)	  

  with open('ground.txt', 'w') as ground:
    ground.write(analysis)
    
  print analysis

  analysis = ""

  for bench in benches:
    for overhead in overheads: 
      analysis = ""
      for heavy_hitter in heavy_hitters.get(bench):
        analysis += "%s,%s" % (bench, heavy_hitter) 
        min_times = []
        for round in rounds:
          sample_file = "adaptive-prof-wolverine.soic.indiana.edu-" + bench + "-" + round + "-" + overhead+ ".out"
          print "Processing %s..\n" % sample_file 
          min_times.append(get_min_time(sample_file, heavy_hitter)) 
          analysis += ",%s" % min_times[int(round) - 1]
        analysis += ",%s\n" % min(min_times)	  
      with open('adaptive-%s.txt' % str(overhead), 'w') as ground:
        ground.write(analysis)
      print analysis

  analysis = ""
  for bench in benches:
    for heavy_hitter in heavy_hitters.get(bench):
      analysis += "%s,%s" % (bench, heavy_hitter) 
      min_times = []
      for round in rounds:
        sample_file = "sampling-prof-wolverine.soic.indiana.edu-" + bench + "-" + round + ".out"
        print "Processing %s..\n" % sample_file 
        min_times.append(get_min_time(sample_file, heavy_hitter)) 
        analysis += ",%s" % min_times[int(round) - 1]
      analysis += ",%s\n" % min(min_times)	  

  with open('sampling.txt', 'w') as ground:
    ground.write(analysis)
    
  print analysis

  analysis = ""
  for bench in benches:
    for heavy_hitter in heavy_hitters.get(bench):
      analysis += "%s,%s" % (bench, heavy_hitter) 
      min_times = []
      for round in rounds:
        sample_file = "backoff-prof-wolverine.soic.indiana.edu-" + bench + "-" + round + ".out"
        print "Processing %s..\n" % sample_file 
        min_times.append(get_min_time(sample_file, heavy_hitter)) 
        analysis += ",%s" % min_times[int(round) - 1]
      analysis += ",%s\n" % min(min_times)	  

  with open('backoff.txt', 'w') as ground:
    ground.write(analysis)
    
  print analysis
  




if __name__ == "__main__":
      main()

