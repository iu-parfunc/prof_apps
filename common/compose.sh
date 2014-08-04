#!/bin/bash 

# How to use! 
# ./compose.sh dyna.out gprof.csv 
#
# The dyna.out is already csv. 
# gprof.out needs to be converted to csv with ./gprof2csv.sh
# output is printed on stdout so just direct it to a file. 




#takes two input files. dyna.out gprof.out 
#produces one output file 


# no! do not just drop out when grep fails
# set -e 
old_IFS=$IFS
IFS=$'\n'

inputDyna=$1;
inputGprof=$2;

echo $inputDyna
echo $inputGprof

linesDyna=($(cat $inputDyna))

printf "%-40s%-15s%-15s%s\n" "Function," "dynaprof," "gprof," "gprof-dyna";

for l in "${linesDyna[@]}"; 
do 

    trimmed=$(echo $l | sed -e 's/^ *//' -e 's/ *$//');
    squeezed=$(echo $trimmed | tr -s ' ');
    
    
    fn_name=$(echo $squeezed | cut -d',' -f1)
    fn_count=$(echo $squeezed | cut -d',' -f2)
   
    
    #echo greping for $fn_name in $inputGprof 
    # peform a lookup in the gprof data 
    IFS=$old_IFS
    gp_line=$(grep -m 1 $fn_name $inputGprof)
    IFS=$'\n'
   
    gp_trimmed=$(echo $gp_line | sed -e 's/^ *//' -e 's/ *$//');
    gp_squeezed=$(echo $gp_trimmed | tr -s ' ');
    
    
    gp_fn_count=$(echo $gp_squeezed | cut -d',' -f4)
    
    printf "%-40s%-15s%-15s%d\n" "$fn_name," "$fn_count," "$gp_fn_count," $(($gp_fn_count - $fn_count));


done 




#
# Interesting Columns DYNA:   1, 2 
# Interesting Columns Gprof:  4, 7  



IFS=$old_IFS
