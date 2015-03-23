


gen-data: 
	head -c 100M < /dev/urandom > large.random



run: 
	(cd ../ubiprof; make build)  
	./runit.sh ubiprof
	(cd ../unprofiled; make build) 
	./runit.sh unprofiled 
