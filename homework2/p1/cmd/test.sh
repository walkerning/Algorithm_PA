#!/bin/bash

# http://www.cyberciti.biz/tips/bash-shell-parameter-substitution-2.html
# a subtle error that i do not know before
CLOSEST_STEP=${1:-100000}
CLOSEST_END=${2:-1000000}

# temp files for test
tmpfile=$(mktemp /tmp/closest_point_pair.tmp.XXXXXXXX)
infile=$(mktemp /tmp/closest_point_pair.XXXXXXXX)

#echo -e "\tdivide and conqueue\tnaive O(N^2)"
x=${CLOSEST_STEP}
while [[ $x -le CLOSEST_END ]]; do
    #echo -ne "${x} 个点:\t"
    ./build/points_gen ${CLOSEST_STEP} ${tmpfile} 1>/dev/null
    cat ${tmpfile} >> ${infile}
    #./build/main_cmd ${infile} | awk '/Time: .* s/ {printf "%f\t", $2;}'
    ./build/main_cmd ${infile} | awk '/Time: .* s/ {printf "%f\n", $2;}'
    #./build/main_cmd_nsquare ${infile} | awk '/Time: .* s/ {printf "%f\n", $2;}'
    x=$((x + CLOSEST_STEP))
done
rm ${tmpfile}
rm ${infile}
