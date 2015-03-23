


gen-data: 
	head -c 100M < /dev/urandom > large.random



run: 
	(cd ../ubiprof; make build)  
	(cd ../instrumented; readelf -s bzip2 |grep FUNC | awk -F '[[:space:]]+' '{print $$3 "," $$9}' > functions.txt)
	./runit.sh ubiprof
	(cd ../unprofiled; make build) 
	./runit.sh unprofiled 
