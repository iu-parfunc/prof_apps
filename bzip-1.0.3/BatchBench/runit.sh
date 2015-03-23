

RUNID=$1 

set x 
set e

if [ -f data_out.$RUNID ] ; then 
    rm data_out.$RUNID
fi 

echo "filesize, real, user, sys" > data_out.$RUNID

for i in 1 10 20 30 40 50 60 70 80 90 100 ; do 
   /usr/bin/time -f "$i, %e, %U, %S" ../instrumented/bzip2 large.random $i 2>>data_out.$RUNID

   
done 

