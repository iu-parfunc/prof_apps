
include ../Makefile_common

build: build-par-apps-plain

run: 
	if [ -z $(PERF) ]; then \
		make run-par-plain; \
	else \
		make run-par-perf-plain; \
	fi	
	
clean:
