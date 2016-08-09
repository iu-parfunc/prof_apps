
build: build-seq-apps-liteprof

include ../Makefile_common

run: build 
	if [ -z $(PERF) ]; then \
		make run-seq-liteprof; \
	else \
		make run-seq-perf-liteprof; \
	fi	
	
clean:
