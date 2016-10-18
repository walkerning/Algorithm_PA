#include <iostream>
#include <cstdlib>
#include <ctime>
#include "gen_randint.h"
#include "sorts.h"

#define MAX_BITS 32

int print_usage() {
  std::cerr << "Usage: ./main <number of integers>";
  return 1;
}

void print_arr(unsigned int* arr, int n) {
  std::cout << "numbers: ";
  for (int i = 0; i < n; i ++) {
    std::cout << arr[i] << ", ";
  }
  std::cout << std::endl;
}

int main(int argc, const char** argv) {
  if (argc != 2) {
    return print_usage();
  }
  // FIXME: no error handling
  int num = atoi(argv[1]);
  std::cout << "sorting " << num << " numbers." << std::endl;

  srand(time(NULL));
  unsigned int* numbers = gen_randints(MAX_BITS, num);
  std::cout << "generating random numbers: " << std::endl;
  print_arr(numbers, num);

  unsigned int* input = new unsigned int[num];

  std::clock_t start;

  if (num <= 100000) {
    // too slow
    memcpy(input, numbers, sizeof(unsigned int) * num);
    start = std::clock();
    insert_sort(input, num);
    std::cout << "insertion sort: " << std::endl;
    std::cout << "Time: " << (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    print_arr(input, num);
    std::cout << std::endl;
  }

  memcpy(input, numbers, sizeof(unsigned int) * num);
  start = std::clock();
  quick_sort(input, num);
  std::cout << "quick sort: " << std::endl;
  std::cout << "Time: " << (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
  print_arr(input, num);
  std::cout << std::endl;

  memcpy(input, numbers, sizeof(unsigned int) * num);
  start = std::clock();
  merge_sort(input, num);
  std::cout << "merge sort: " << std::endl;
  std::cout << "Time: " << (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
  print_arr(input, num);
  std::cout << std::endl;

  memcpy(input, numbers, sizeof(unsigned int) * num);
  start = std::clock();
  shell_sort(input, num);
  std::cout << "shell sort: " << std::endl;
  std::cout << "Time: " << (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
  print_arr(input, num);
  std::cout << std::endl;

  memcpy(input, numbers, sizeof(unsigned int) * num);
  start = std::clock();
  radix_sort(input, num);
  std::cout << "radix sort: " << std::endl;
  std::cout << "Time: " << (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
  print_arr(input, num);
  std::cout << std::endl;

  delete(numbers);
  delete(input);
  return 0;
}
