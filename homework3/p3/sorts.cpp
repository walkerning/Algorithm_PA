#include "sorts.h"
// template <class T>
// void choose_sort(T* arr, int n) {
//   int min;
//   int ind;
//   for (int i = 0; i < n - 1; i ++) {
//     min = arr[i];
//     ind = i;
//     for (int j = i + 1; j < n; j ++) {
//       int ele = arr[j];
//       if (ele < min) {
//         min = ele;
//         ind = j;
//       }
//     }
//     if (ind != i) {
//       arr[ind] = arr[i];
//       arr[i] = min;
//     }
//   }
// }

template <class T>
void insert_sort(T* arr, int n) {
  for (int i = 0; i < n; i ++) {
    T num = arr[i];
    int j = i - 1;
    for (; j >=0 && arr[j] > num; j --) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = num;
  }
}

template <class T>
void swap(T* arr, int ind1, int ind2) {
  T tmp = arr[ind1];
  arr[ind1] = arr[ind2];
  arr[ind2] = tmp;
}

template <class T>
void _quick_sort(T* arr, int left, int right) {
  if (right - left <= 1) {
    return;
  }
  T pivot = arr[right - 1];
  // divide
  int seperate_ind = left;
  for (int i = left; i < right - 1; i++) {
    if (arr[i] <= pivot) {
      swap(arr, i, seperate_ind);
      seperate_ind ++;
    }
  }
  swap(arr, right - 1, seperate_ind);
  // conquer
  _quick_sort(arr, left, seperate_ind);
  _quick_sort(arr, seperate_ind + 1, right);
}

template <class T>
void quick_sort(T* arr, int n) {
  _quick_sort(arr, 0, n);
}

// void _print_arr(unsigned int* arr, int n) {
//   std::cout << "numbers: ";
//   for (int i = 0; i < n; i ++) {
//     std::cout << arr[i] << ", ";
//   }
//   std::cout << std::endl;
// }

template <class T>
void merge_sort(T* arr, int n) {
  if (n == 1) {
    return;
  }
  // divide
  int seperate_ind = n >> 1;
  T* subarr_start = arr + seperate_ind;
  // conquer
  merge_sort(arr, seperate_ind);
  merge_sort(subarr_start, n - seperate_ind);
  // merge
  T* ex_arr = new T[n];
  int i = 0;
  int j = 0;
  int index = 0;
  while (i < seperate_ind && j < n - seperate_ind) {
    if (arr[i] <= subarr_start[j]) {
      ex_arr[index++] = arr[i++];
    } else {
      ex_arr[index++] = subarr_start[j++];
    }
  }
  if (i < seperate_ind) {
    memcpy(&ex_arr[index], &arr[i], sizeof(T)*(seperate_ind-i));
  } else if (j < n - seperate_ind) {
    memcpy(&ex_arr[index], &subarr_start[j], sizeof(T)*(n-seperate_ind-j));
  }
  memcpy(arr, ex_arr, sizeof(T)*n);
  delete(ex_arr);
}

template <class T>
void shell_sort(T* arr, int n) {
  for (int step = n >> 1; step > 0; step >>= 1) {
    for (int i = step; i < n; i++) {
      T num = arr[i];
      int j = i - step;
      for (; j >= 0 && arr[j] > num; j -= step) {
        arr[j + step] = arr[j];
      }
      arr[j + step] = num;
    }
  }
}

void counting_sort(unsigned int* arr, int n, int min_bit, int bits) {
  unsigned int count_k = 1 << bits;
  int* C = new int[count_k];
  unsigned int* A = new unsigned int[n];
  unsigned int* B = new unsigned int[n];
  memcpy(B, arr, sizeof(unsigned int) * n);
  for (int j = 0; j < count_k; j++) {
    C[j] = 0;
  }
  for (int i = 0; i < n; i++) {
    A[i] = (arr[i] >> min_bit) & ((1 << bits) - 1);
  }
  for (int i = 0; i < n; i++) {
    C[A[i]] += 1;
  }
  for (int j = 1; j < count_k; j++) {
    C[j] += C[j-1];
  }
  for (int i = n - 1; i >= 0; i--) {
    B[C[A[i]] - 1] = arr[i];
    C[A[i]] -= 1;
  }
  memcpy(arr, B, sizeof(unsigned int) * n);
  delete(C);
  delete(B);
  delete(A);
}

// only sort non-negative integers
void radix_sort(unsigned int* arr, int n) {
  using namespace std;
  int bits = static_cast<int>(log2(n));
  // find max one
  unsigned int max = arr[0];
  for (int i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  int total_bits = static_cast<int>(log2(max)) + 1;
  int num_loops = (total_bits - 1) / bits + 1;
  for (int i = 0; i < num_loops; i++) {
    counting_sort(arr, n, i*bits, bits);
  }
}

template void insert_sort<unsigned int>(unsigned int*, int);
template void quick_sort<unsigned int>(unsigned int*, int);
template void merge_sort<unsigned int>(unsigned int*, int);
template void shell_sort<unsigned int>(unsigned int*, int);
