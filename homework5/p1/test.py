#!/usr/bin/env python2.7
import math
import random
import subprocess
import re

RATIO = 0.4
tmp_test_fname = "tmp_test_fname.txt"

def cal(max_num):
    input = [str(random.randint(0, RATIO*max_num)) for _ in range(max_num)]
    with open(tmp_test_fname, "w") as f:
        f.write(" ".join(input))
    output = subprocess.check_output("./main {}".format(tmp_test_fname), shell=True)
    match = re.search("Time: ([0-9.]+) ms", output)
    assert match is not None
    print max_num, match.group(1), float(match.group(1))/max_num/math.log(max_num)

print "N\tTime(ms)"
for i in xrange(1, 7):
    cal(10**i/2)
    cal(10**i)
