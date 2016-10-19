#ifndef _ALGORITHM3_P3_SORTS_H
#define _ALGORITHM3_P3_SORTS_H
#include <cmath>
#include <cstring>

template <class T>
void insert_sort(T* arr, int n);

template <class T>
void quick_sort(T* arr, int n);

template <class T>
void merge_sort(T* arr, int n);

template <class T>
void shell_sort(T* arr, int n);

void radix_sort(unsigned int* arr, int n);

void radix_sort32(unsigned int* arr, int n);

#endif
