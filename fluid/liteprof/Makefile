
rule0: build-par-apps-liteprof

include ../Makefile_common

build: build-par-apps-liteprof

run: 
	if [ -z $(PERF) ]; then \
		make run-par-liteprof; \
	else \
		make run-par-perf-liteprof; \
	fi	
	
clean:
