#!/bin/bash

FIBO_REPEATS=${FIBO_REPEATS:=3}
FIBO_STEP=${FIBO_STEP:=10000}
FIBO_START=${FIBO_START:=0}
FIBO_END=${FIBO_END:=100000}

python fibonacci.py -r ${FIBO_REPEATS} -t $(for i in `seq -f "%.0f" ${FIBO_START} ${FIBO_STEP} ${FIBO_END}`; do echo -n '-n '$i' ';done) | awk '/elapsed/ {print $1, $NF;}' > bottom_up.res

python fibonacci.py -r ${FIBO_REPEATS} -s -t $(for i in `seq -f "%.0f" ${FIBO_START} ${FIBO_STEP} ${FIBO_END}`; do echo -n '-n '$i' ';done) | awk '/elapsed/ {print $1, $NF;}' > recur_square.res
