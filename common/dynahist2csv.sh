#!/bin/bash 


# Extract Rate and Time histograms from 
# Dynaprof profiler output 


set -e

old_IFS=$IFS
IFS=$'\n'

input=$1
output=$2

#remove output if exists
if [ -f $output ] ; then
    rm $output
fi


#lines=($(cat sample.out)) 
lines=($(cat $input)) 
header="FunctionRate_HistTime_Hist"

output_header="Function,r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10"

#output header to result file 
echo $output_header >> $output


# Eat part of file that is of no interest
l=$(echo ${lines[0]}  | tr -d ' '); 
counter=0 
while [ "$l" != "$header" ] 
do 
  counter=$((counter + 1));
  l=$(echo ${lines[$counter]}  | tr -d ' '); 
  #echo $l;
  printf ".";
done 
printf "\n";

printf "Histograms found starting on line: " 
printf $counter; printf "\n"; 

# echo ${lines[$counter]};

 
# takes a segment of the array starting at a valid histagram 
# location as input 
function extractHist {

# takes an array 
arr=("${@}");

# accumulate data 

rate_hist=
time_hist= 

#parse out first line 
t=$(echo ${arr[1]} | sed -e 's/^ *//' -e 's/ *$//');
s=$(echo  $t| tr -s ' ');
#echo $s;
   
fun_name=$(echo $s | cut -d' ' -f1);
rt=$(echo $s | cut -d' ' -f2); 
rate_hist+=$(echo $rt | cut -d':' -f2);
tt=$(echo $s | cut -d' ' -f3);
time_hist+=$(echo $tt | cut -d':' -f2);

#parse the rest of the histograms 
for ix in `seq 2 11`;
do 
    t=$(echo ${arr[$ix]} | sed -e 's/^ *//' -e 's/ *$//');
    s=$(echo  $t| tr -s ' ');
    # echo $s;
    
    
    val_tmp=$(echo $s | cut -d' ' -f1);
    val=$(echo $val_tmp |  cut -d':' -f2); 
    rate_hist+=,$val;
    val_tmp=$(echo $s | cut -d' ' -f2);
    val=$(echo $val_tmp |  cut -d':' -f2); 
    time_hist+=,$val;

done 
all_hist=$fun_name,$rate_hist,$time_hist;
# append to output file 

# echo "Adding line" 
echo $all_hist >> $output


}

# total length of array
tot=("${#lines[@]}"); 


# extract all histograms
while [ $counter -le $tot ]
do 
    extractHist "${lines[@]:$counter}";
    counter=$((counter+11));  
    printf "*"; 
done; 
# for some reason outputs one line too many. 

#finito! 
printf "\n";
echo "DONE!";


IFS=$old_IFS
