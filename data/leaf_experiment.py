import subprocess
import os
import random
import sys
import shutil

FNULL = open(os.devnull, 'w')
os.environ["DYN_STRATEGY"] = "SAMPLING"
os.environ["DYN_OUTPUT_TYPE"] = "STRIPPED"

# Warmup run
def run_warmup():
  print "Doing warm up runs.."
  for i in range(3):
    try:
      subprocess.check_call(["h264ref","-d", "test/input/foreman_test_encoder_baseline.cfg"], 
        stdout=FNULL, stderr=subprocess.STDOUT ) # Run with leaf nodes instrumented
    except subprocess.CalledProcessError as e:
      print ">> Error during warmup run.. Continuing.."
    print "--> Done with warmup run %d" % i

  # Remove warm up run data
  os.remove("prof.out")

# Call with unfiltered functions
def run_unfiltered(): 
  os.environ["DYN_FILTER_FILE"] = ""
  os.environ["DYN_FILTER_PROBES"] = ""
  for num in range(5):
    print "\n+++++++++++++++++ UNFILTERED ROUND %d ++++++++++++++++++" % num
    try:
      subprocess.check_call(["h264ref","-d", "test/input/foreman_test_encoder_baseline.cfg"], 
        stdout=FNULL, stderr=subprocess.STDOUT ) # Run with leaf nodes instrumented
    except subprocess.CalledProcessError as e:
      print ">>> Failed run with return code ", e.returncode, ". Retrying..."
      for i in range(3):
        try:
          subprocess.check_call(["h264ref","-d", "test/input/foreman_test_encoder_baseline.cfg"], 
             stdout=FNULL, stderr=subprocess.STDOUT ) # Run with leaf nodes instrumented
          break
        except subprocess.CalledProcessError:
          if i < 3:
            print ">>> Failed run with return code ", e.returncode, ". Retrying..."
            continue
          else: 
            print ">>> Failed after 3 retries.. Abandoning this run.."
  shutil.copyfile("prof.out", "unfiltered.out")
  os.remove("prof.out")

# Call with filtered leaf and non leaf functions
def run_filtered():
  non_leaf_funcs = [line.rstrip() for line in open("non_leaf.txt")]
  leaf_funcs = [line.rstrip() for line in open("leaf.txt")]


  for num in range(5):
    print "\n+++++++++++++++++ FILTERED ROUND %d ++++++++++++++++++" % num
    filters = ""
    idx_list = []
    idx = 0
     
    '''
    print "\nRunning with leaf nodes enabled.."
    os.environ["DYN_FILTER_FILE"] = "leaf.txt"
    try:
      subprocess.check_call(["h264ref","-d", "test/input/foreman_test_encoder_baseline.cfg"], 
          stdout=FNULL, stderr=subprocess.STDOUT ) # Run with leaf nodes instrumented
    except subprocess.CalledProcessError as e:
      print ">>> Failed run with return code ", e.returncode, ". Retrying..."
      for i in range(3):
        try:
          subprocess.check_call(["h264ref","-d", "test/input/foreman_test_encoder_baseline.cfg"], 
             stdout=FNULL, stderr=subprocess.STDOUT ) # Run with leaf nodes instrumented
          break
        except subprocess.CalledProcessError:
          if i < 3:
            print ">>> Failed run with return code ", e.returncode, ". Retrying..."
            continue
          else: 
            print ">>> Failed after 3 retries.. Abandoning this run.."
    print "Done.."
    '''

    print "\nRunning with each non leaf node enabled.."
    os.environ["DYN_FILTER_FILE"] = ""
    filters = ""
    idx_list = []
    idx = 0
    for i in range(20):
      print "--->Running with enabled non leaf function : %s" % non_leaf_funcs[i]
      os.environ["DYN_FILTER_PROBES"] = non_leaf_funcs[i] 
      try:
        subprocess.check_call(["h264ref","-d", "test/input/foreman_test_encoder_baseline.cfg"], 
          stdout=FNULL, stderr=subprocess.STDOUT ) # Run with leaf nodes instrumented
      except subprocess.CalledProcessError as e:
        print ">>> Failed run with return code ", e.returncode, ". Retrying..."
        for i in range(3):
          try:
            subprocess.check_call(["h264ref","-d", "test/input/foreman_test_encoder_baseline.cfg"], 
               stdout=FNULL, stderr=subprocess.STDOUT ) # Run with leaf nodes instrumented
            break
          except subprocess.CalledProcessError:
            if i < 3:
              print ">>> Failed run with return code ", e.returncode, ". Retrying..."
              continue
            else: 
              print ">>> Failed after 3 retries.. Abandoning this run.."

  shutil.copyfile("prof.out", "filtered.out")
  os.remove("prof.out")

def main(argv):
  run_warmup();
  print "\n===================== FILTERED RUNS ========================="
  run_filtered();
  print "\n=====================     DONE      =========================\n"
  print "==================== UNFILTERED RUNS ========================"
  run_unfiltered();
  print "\n=====================     DONE      =========================\n"

if __name__ == "__main__":
  main(sys.argv[1:])


