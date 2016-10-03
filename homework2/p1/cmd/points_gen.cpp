/*
 * Generate random points
 */
#include <fstream>
#include <cstdlib>
#include "algo/algo.h"

int print_usage() {
  std::cerr << "Usage: ./points_gen <num of points> <filename> [minimum=-500 maximum=500]\nnote: num of points must be less than INT_MAX" << std::endl;
  return 1;
}

int main(int argc, char** argv) {
  const char* filename = NULL;
  int num_points = 0;
  int minimum = -500;
  int maximum = 500;
  if (argc < 3 || argc > 5) {
    return print_usage();
  }
  if (argc >= 3) {
    num_points = atoi(argv[1]);
    filename = argv[2];
  }
  if (argc >= 4) {
    int converted_minimum = atof(argv[3]);
    minimum = converted_minimum == 0? minimum: converted_minimum;
  }
  if (argc >= 5) {
    int converted_maximum = atof(argv[4]);
    maximum = converted_maximum == 0? maximum: converted_maximum;
  }
  std::vector<Point> vec;
  bool success = GenerateRandomPoints(num_points, minimum,
                                 maximum, vec);
  if (!success) {
    std::cerr << "生成随机点失败" << std::endl;
    return 1;
  }
  std::ofstream fs(filename);
  if (fs.is_open()) {
    int num = WriteFile(fs, vec);
    std::cout << num << "个点被写入文件 " << filename << std::endl;
  } else {
    std::cerr << "打开文件 " << filename << " 失败" << std::endl;
  }
  return 0;
}
