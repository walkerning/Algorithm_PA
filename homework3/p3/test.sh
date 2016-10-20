#!/bin/bash

for num in $(echo "10 100 1000 10000 100000 1000000 10000000 100000000 200000000 1000000000" | tr " " "\n"); do
    echo "$num" >> result.txt
    echo "$num"
    ./main $num | grep -v numbers | tee tmp_result.txt
    cat tmp_result.txt >> result.txt
done

rm tmp_result.txt
