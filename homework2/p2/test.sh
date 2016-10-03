#!/bin/bash

FIBO_INC=${FIBO_INC:=10000}
FIBO_START=${FIBO_START:=0}
FIBO_END=${FIBO_END:=100000}

python fibonacci.py -r 3 -t $(for i in `seq -f "%.0f" ${FIBO_START} ${FIBO_INC} ${FIBO_END}`; do echo -n '-n '$i' ';done) | awk '/elapsed/ {print $1, $NF;}' > bottom_up.res

python fibonacci.py -r 3 -s -t $(for i in `seq -f "%.0f" ${FIBO_START} ${FIBO_INC} ${FIBO_END}`; do echo -n '-n '$i' ';done) | awk '/elapsed/ {print $1, $NF;}' > recur_square.res
