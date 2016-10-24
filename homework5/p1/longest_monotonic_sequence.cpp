#include "longest_monotonic_sequence.h"
// #include <iostream>
// using namespace std; // for test

template <class T>
int binary_search(std::vector<T> array, T num) {
  int left = 0;
  int right = array.size();
  int index = (left + right)/2;
  if (right == 0 || num <= array[0]) {
    return -1;
  }
  while (left < right) {
    if (index == right - 1) {
      if (array[index] < num) {
        return index;
      } else {
        right = index;
      }
    } else if (array[index + 1] >= num && array[index] < num) {
      return index;
    } else if (array[index + 1] < num) {
      left = index + 1;
    } else {
      right = index;
    }
    index = (left + right)/2;
  }
  return index;
}

template <class T>
std::vector<T> longest_monotonic_sequence(std::vector<T> input) {
  int len = input.size();
  T* way = new T[len];
  std::vector<T> end;
  std::vector<int> end_index;
  end.push_back(input[0]);
  end_index.push_back(0);
  way[0] = -1;
  for (int i = 1; i < len; i++) {
    int index = binary_search(end, input[i]);
    if (index == end.size() - 1) {
      end.push_back(input[i]);
      way[i] = end_index[end_index.size() - 1];
      end_index.push_back(i);
    } else {
      end[index + 1] = input[i];
      way[i] = index >= 0? end_index[index]: -1;
      end_index[index + 1] = i;
    }
  }
  std::vector<T> ans;
  int index = end_index[end_index.size() - 1];
  while (index != -1) {
    ans.push_back(input[index]);
    index = way[index];
  }
  std::reverse(ans.begin(), ans.end());
  delete(way);
  return ans;
}

template std::vector<double> longest_monotonic_sequence<double>(std::vector<double> input);
