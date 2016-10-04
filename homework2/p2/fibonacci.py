# -*- coding: utf-8 -*-
from __future__ import print_function
import argparse
import time

class Timeit(object):
    def __init__(self, n):
        self.timeit_dict = {}
        assert n > 0
        assert isinstance(n, int)
        self.n = n

    def __call__(self, key):
        def deco(func):
            def _func(*args, **kwargs):
                elapsed = 0
                start = time.time()
                for _ in range(self.n):
                    result = func(*args, **kwargs)
                    elapsed += time.time() - start
                self.timeit_dict.setdefault(key, []) \
                                .append((args, kwargs, elapsed/self.n, result))
                return result
            return _func
        return deco

    def print_summary(self):
        for key, data in self.timeit_dict.iteritems():
            print(key + ":")
            for record in data:
                print(record[0], record[1], "\t", record[3], "\telapsed: ", record[2])
            print("----")


def fibo_recursive_square(num):
    if num == 0:
        return 0
    if num == 1:
        return 1
    return fibo_square(num - 1)[0]

def mul1(sq):
    return [sq[0] + sq[2], sq[1] + sq[3],
            sq[0], sq[1]]

def square(sq):
    bc = sq[1]*sq[2]
    b_c = sq[1] + sq[2]
    a_d =  sq[0] + sq[3]
    ans = [sq[0]*sq[0]+bc, sq[0]*sq[1] + sq[1]*sq[3], 0, sq[3]*sq[3]+bc]
    ans[2] = a_d * b_c - ans[1]
    return ans

def fibo_square(num):
    if num == 1:
        return [1, 1, 1, 0]
    if num % 2 == 0:
        return square(fibo_square(num / 2))
    else:
        return mul1(square(fibo_square(num / 2)))

# def fibo_bottom_up(num):
#     fibo = [0, 1]
#     for i in range(2, num + 1):
#         fibo.append(fibo[-1] + fibo[-2])
#     return fibo[num]

def fibo_bottom_up(num):
    if num == 0:
        return 0
    num1 = 0
    num2 = 1
    for i in range(2, num + 1):
        num2, num1 = num1 + num2, num2
    return num2

def main():
    def noneg_int(value):
        ivalue = int(value)
        if ivalue < 0:
            raise argparse.ArgumentParser("%s is an invalid positive integer value" % value)
        return ivalue
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )
    parser.add_argument("-s", "--recur-square",
                        help="Calculate using recursive squaring.",
                        action="store_true",
                        default=False)
    parser.add_argument("-t", "--timing",
                       help="Print the time that each calculation use",
                       action="store_true",
                       default=False)
    parser.add_argument("-r", "--repeat-num",
                        type=noneg_int,
                        help="Repeating number when benchmark a function",
                        default=1)
    parser.add_argument("-n", "--num", required=True,
                        type=noneg_int, action="append",
                        help="The numbers to calculate.")
    args = parser.parse_args()

    if args.timing:
        global fibo_recursive_square, fibo_bottom_up
        timer = Timeit(args.repeat_num)
        fibo_recursive_square = timer("recursive_square")(fibo_recursive_square)
        fibo_bottom_up = timer("bottom_up")(fibo_bottom_up)
    for num in args.num:
        if args.recur_square:
            fibo_recursive_square(num)
        else:
            fibo_bottom_up(num)
    if args.timing:
        timer.print_summary()

if __name__ == "__main__":
    main()
