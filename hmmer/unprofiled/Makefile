
build: build-seq-apps-plain

include ../Makefile_common

run: build 
	if [ -z $(PERF) ]; then \
		make run-seq-plain; \
	else \
		make run-seq-perf-plain; \
	fi	
	
clean:
