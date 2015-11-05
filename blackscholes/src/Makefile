

all: 
	m4 ./c.m4.pthreads blackscholes.c > blackscholes.m4.cpp
	g++ -pthread -DENABLE_THREADS -DNCO=4 $(CFLAGS) blackscholes.m4.cpp -o blackscholes $(LDFLAGS) 


gen-data: 
	gcc inputgen.c -o inputgen 
	./inputgen 1000000 data.out 




clean:
	if [ -d blackscholes ]; then rm blackscholes; fi
