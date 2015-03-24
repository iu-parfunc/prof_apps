


gen-data: 
	(cd ../Data; make) 
	../Data/uniform -d 3 1000000  input.data


run: 
	(cd ../ubiprof; make build) 
	(cd ../BarnesHut; readelf -s nbody |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	./runit.sh ubiprof
	(cd ../unprofiled; make build)
	./runit.sh unprofiled
