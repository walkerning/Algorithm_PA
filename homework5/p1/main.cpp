#include <iostream>
#include <fstream>
#include <ctime>
#include "longest_monotonic_sequence.h"

int print_usage() {
  std::cerr << "./main <input file, space seperated number>" << std::endl;
  return 1;
}

int main(int argc, const char** argv) {
  if (argc != 2) {
    return print_usage();
  }
  std::ifstream infile(argv[1]);
  if (!infile.is_open()) {
    std::cerr << "打开文件 " << argv[1] << " 失败" << std::endl;
    return 1;
  }
  std::vector<double> nums;
  double num;
  int next_char;
  while ((next_char = infile.peek()) != EOF) {
    infile >> num;
    nums.push_back(num);
    infile >> std::ws;
  }
  std::cout << "输入序列, 大小: " << nums.size() << std::endl;
  for (auto& num: nums) {
    std::cout << num << " ";
  }
  std::clock_t start = std::clock();
  std::vector<double> ans = longest_monotonic_sequence(nums);
  std::cout << std::endl << "Time: " << (std::clock() - start) / (double)CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
  std::cout << "最长递增子序列, 大小: " << ans.size() << std::endl;
  for (auto& num: ans) {
    std::cout << num << " ";
  }
  return 0;
}
