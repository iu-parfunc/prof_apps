
A Log of experiments and hacking, in chronological order
========================================================

[2014.08.07] {Debugging raxml assertion failures}
-------------------------------------------------

These, oddly are only happening when dynaprof is enabled. -RRN

They don't happen with DYN_STRATEGY=EMPTY...



Experiments left to perform
===========================

Methodology: grab one of the below, and write about it above as you
work on it.

Experiments

 * [ ] Aggregate number of probes vs. Overhead
  - scatterplot should show a roughly linear relationship
  - are different apps distinguishable?

  - [ ] plot Overhead vs epochs (Overhead time series)
  - [ ] plot Num threads vs overhead 


 * [ ] Probe overhead breakdown / analysis
  - [x] Measure probe overhead distribution, make histograms
  - Run these variants, to try to tease apart issues:
   - PROBE_TRUE_EMPTY_ON : nothing at all: literally consecutive getticks calls
   - (name?) : empty/call - perform no actual profiling work, but
     still a call to epilogFunction/prologFunction
 
   - (name?) : prolog only - the normal profiling work: statistics
     gathering plus possible call site patching on the first call
   - (name?) : epilog only - same for epilogue,

   - (name?) : probe [de]activation overhead, not counted in the above

   - OTHER: Daemon thread overhead


  - [ ] the above variants can be run for different apps
  - [ ] the above variants can also be run for the probe overhead
        microbench.  This does NOTHING but launch probes.  It's best
        case.
  - [ ] optional: a new WORST CASE microbench could test the scenario
        where the entire cache is blown away between probe calls, so
        that maximum memory penalty is incurred.
      
  - Any further expermients to understand outliers?

