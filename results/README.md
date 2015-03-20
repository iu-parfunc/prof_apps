Result types
Glossary for probe overhead results [03/15/15]

- full : Probe times for normal instrumentation control including first time arg patching 
                and followed by stat collection + probe deactivations subsequently.
- regular : Probe times for stat collection only control flow
- deactivation : Probe times for deactivation only control flow
- empty : Probe times for empty prolog and epilog. (Prolog still contains the initial cost of initializing thread local 
          statistics data structure) 
- empty_full : Probe times for fully empty prolog and epilog 
- empty_cpu_time : Probe times for fully empty prolog and epilog. But the time measured is CPU time instead of wall clock time.
