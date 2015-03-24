

run: 
	(cd ../ubiprof; make build) 
	(cd ../src; readelf -s fluidanimate |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	./runit.sh ubiprof
	(cd ../unprofiled; make build)
	./runit.sh unprofiled
