#!/bin/bash

for num in $(echo "10 100 1000 10000 100000 1000000 10000000 100000000 200000000" | tr " " "\n"); do
    echo "$num"
    ./main $num | grep -v numbers | tee result.txt
done
