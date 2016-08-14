
build: build-par-apps-plain

include ../Makefile_common

run: 
	if [ -z $(PERF) ]; then \
		make run-par-plain; \
	else \
		make run-par-perf-plain; \
	fi	
	
clean:
