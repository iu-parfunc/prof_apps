#!/bin/bash 

# currently outputs incorrect result when the gprof output 
# does not have a value noted for each field. 
# find a work around. 

set -e

old_IFS=$IFS
IFS=$'\n'

input=$1
output=$2

#lines=($(cat sample.out)) 
lines=($(cat $input)) 

header="timesecondssecondscallss/calls/callname"
header2="timesecondssecondscallsms/callms/callname"    

data_done="Indexbyfunctionname"
data_done2="%thepercentageofthetotalrunningtimeofthe"

l=$(echo ${lines[0]}  | tr -d ' '); 
counter=0 
while [ "$l" != "$header" -a "$l" != "$header2" ] 
do 
  counter=$((counter + 1));
  l=$(echo ${lines[$counter]}  | tr -d ' '); 
  #echo $l;
  printf ".";
done 
printf "\n";

echo "Found headers on line" 
echo $counter 


for data in "${lines[@]:$counter}";
do 
    curr_ns=$(echo $data | tr -d ' ');
    if [ "$curr_ns" = "$data_done2" ]; 
    then 
	printf "\n";
	echo "found end of gprof data" ;
	break;
    fi
    

    # squeeze whitespaces 
    trimmed=$(echo $data | sed -e 's/^ *//' -e 's/ *$//');
    squeezed=$(echo $trimmed | tr -s ' ');
    
    # switch to commas
    tmp=$(echo $squeezed | tr ' ' ','); 
    
    # numcommas
    nc=$(echo $tmp | tr -cd , | wc -c)
    
    
    # parse the data 
    # 7 fields separated by comma. 
    if [ $nc -eq 6 ] ;
    then
	echo $(echo $tmp | cut -d',' -f1,2,3,4,5,6,7) >> $output;
    elif [ $nc -eq 3 ]; 
    then 
        fields=$(echo $tmp | cut -d',' -f1,2,3)
	name=$(echo $tmp | cut -d',' -f4)
	echo $fields,,,$name >> $output;
    fi 
    printf "*" 
  
   

   


done

printf "\n";
echo "DONE!";


IFS=$old_IFS
