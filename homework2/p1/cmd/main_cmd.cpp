/*
 * Command line interface for test
 */
#include <fstream>
#include "algo/algo.h"

int print_usage() {
  std::cerr << "Usage: ./test <filename>" << std::endl;
  return 1;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    return print_usage();
  }

  std::ifstream fs(argv[1]);
  if (!fs.is_open()) {
    std::cerr << "打开文件 " << argv[1] << " 失败" << std::endl;
  }
  std::vector<Point> points;
  int num = ReadFile(fs, points);
  std::cout << "从文件 " << argv[1] << " 中读取 " << num << " 个点" << std::endl;

  ClosestPairSolver solver;
  solver.SetPoints(points);
  int index1;
  int index2;
  double mindist;
  bool success = solver.FindClosestPair(&index1, &index2, &mindist);
  if (!success) {
    std::cerr << "点数不够, 没有距离的最小值" << std::endl;
    return 1;
  }
  std::cout << "点: " << std::endl << points.at(index1) << std::endl
            << points.at(index2) << std::endl;
  std::cout << "最小距离: " << mindist << std::endl;
  return 0;
}
