#ifndef _ALGORITHM2_P1_algo_H
#define _ALGORITHM2_P1_algo_H
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

typedef struct _point {
  double x;
  double y;
  _point(): x(0), y(0) {} // FIXME: meaningless default constructor, not a good practice...
  _point(double p_x, double p_y): x(p_x), y(p_y) {}
} Point;

inline std::ostream& operator<< (std::ostream& os, const _point& p) {
  os << p.x << "\t" << p.y;
  return os;
}

int ReadFile(std::istream& is, std::vector<Point>& vec);

int WriteFile(std::ostream& os, const std::vector<Point>& vec);

class ClosestPairSolver {
public:
  typedef struct _indexedPoint{
    int index;
    Point point;
    _indexedPoint(): index(-1) {}
    _indexedPoint(int new_ind, Point new_point): index(new_ind), point(new_point) {}
  } IndexedPoint;

  ClosestPairSolver();
  void AddPoint(Point new_point);
  void AddPoints(const std::vector<Point>& points);
  void SetPoints(const std::vector<Point>& points);
  void Clear() {
    ipoints_ori_.clear();
    ipoints_.clear();
    ipoints_indexes_by_y_.clear();
    num_points_ = 0;
    current_index1_ = -1;
    current_index2_ = -1;
    current_sqr_mindist_ = -1;
  }
  bool FindClosestPair(int* pindex1, int* pindex2,
                       double* pdist);
  bool _FindClosestPair(std::vector<IndexedPoint>::iterator beg, std::vector<IndexedPoint>::iterator end, const std::vector<int>& indexes_by_y, int* pindex1, int* pindex2, double* pdist);
  int num_points() { return num_points_; }

  // FIXME: do we need to implement a sorting that support key function instead of a compare function?
  static bool sort_ipoints_by_x(const IndexedPoint& ip1, const IndexedPoint& ip2) {
    return ip1.point.x < ip2.point.x;
  }

  double _dist(IndexedPoint ipoint1, IndexedPoint ipoint2) {
    double dist_x = ipoint1.point.x - ipoint2.point.x;
    double dist_y = ipoint1.point.y - ipoint2.point.y;
    return dist_x * dist_x + dist_y * dist_y;
  }
private:
  int num_points_;
  std::vector<IndexedPoint> ipoints_;
  std::vector<int> ipoints_indexes_by_y_;
  std::vector<IndexedPoint> ipoints_ori_;
  int current_index1_;
  int current_index2_;
  double current_sqr_mindist_;
};

#endif
