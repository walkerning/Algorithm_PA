# -*- coding: utf-8 -*-
from __future__ import print_function
import os
import sys
import cv2
import numpy as np

def seam_carving(image, d_func):
    """
    Parameters
    --------
    image: np.ndarray
        Input image, size is m x n.

    d_func: callable
        A function that receive image, the coordinate i, j as arguments,
        return the "destruction degree" d[i, j].
    Returns
    --------
    carved_image: np.ndarray
        Output image, size is m x n-1.
    """
    m, n = image.shape[:2]
    cost_mat = np.zeros((m,n))
    way_mat = np.zeros((m-1,n), dtype=np.int8)
    result_mat = np.zeros((m, n-1) + image.shape[2:])
    for x in range(n):
        cost_mat[0, x] = d_func(image, 0, x)
    for y in range(1, m):
        for x in range(n):
            if x == 0:
                before = cost_mat[y-1, 0:2]
                index = np.argmax(before)
            elif x == n-1:
                before = cost_mat[y-1, n-2:n]
                index = np.argmax(before) - 1
            else:
                before = cost_mat[y-1, x-1:x+2]
                index = np.argmax(before) - 1
            cost_mat[y, x] = before[index] + d_func(image, y, x)
            way_mat[y - 1, x] = index
    the_way = [np.argmin(cost_mat[m-1, :])]
    for y in xrange(m-1, 0, -1):
        the_way.append(the_way[-1] + way_mat[y - 1, the_way[-1]])
    the_way.reverse()
    #print(the_way)
    for y in range(0, m):
        #print(the_way[y])
        result_mat[y, :] = np.concatenate((image[y, :the_way[y]],
                                           image[y, the_way[y]+1:]), axis=0)
    return result_mat

def seam_carving_half(image, d_func):
    """
    Parameters
    --------
    image: np.ndarray
        Input image, size is m x n.

    d_func: callable
        A function that receive image, the coordinate i, j as arguments,
        return the "destruction degree" d[i, j].
    Returns
    --------
    carved_image: np.ndarray
        Output image, size is m/2 x n/2.
    """
    m, n = image.shape[:2]
    result_m, result_n = m/2, n/2
    for x in range(n, result_n, -1):
        image = seam_carving(image, d_func)
    image = image.transpose((1, 0, 2)) if len(image.shape) == 3 else image.T
    for x in range(m, result_m, -1):
        image = seam_carving(image, d_func)
    image = image.transpose((1, 0, 2)) if len(image.shape) == 3 else image.T
    return image

def mean_square(image, y, x):
    m, n = image.shape[:2]
    assert 0 <= y <= m - 1
    assert 0 <= x <= n - 1
    s = 0
    num = 0
    if x < n - 1:
        s +=  np.square(image[y, x, :] - image[y, x+1, :]).sum()
        num += 1
    if x > 0:
        s += np.square(image[y, x, :] - image[y, x-1, :]).sum()
        num += 1
    return s/num if num else 0

def main():
    assert len(sys.argv) == 2, "This program take one and only one argument: the file name of image file."
    im = cv2.imread(sys.argv[1])
    assert im is not None, "Cannot read image from {}.".format(sys.argv[1])
    result_fname = "out_" + os.path.basename(sys.argv[1])
    print("The result image will be writen to ", result_fname)

    result_im = seam_carving_half(im, mean_square)
    # for i in range(60):
    #     im = seam_carving(im, mean_square)
    # result_im = im
    cv2.imwrite(result_fname, result_im)

if __name__ == "__main__":
    main()
