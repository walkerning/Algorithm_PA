#include "algo.h"

int ReadFile(std::istream& is, std::vector<Point>& vec) {
  double p_x;
  double p_y;
  int next_char;
  int num = 0;
  is >> std::ws;
  while ((next_char = is.peek()) != EOF) {
    is >> p_x;
    is >> p_y;
    vec.push_back(Point(p_x, p_y));
    num ++;
    is >> std::ws;
  }
  return num;
}

int WriteFile(std::ostream& os, const std::vector<Point>& vec) {
  for (std::vector<const Point>::iterator it = vec.begin();
       it != vec.end(); it++) {
    os << *it << std::endl;
  }
  return vec.size();
}

bool GenerateRandomPoints(int num_points, double minimum, double maximum, std::vector<Point>& vec) {
  if (minimum > maximum) return false;
  for (int i = 0; i < num_points; i++) {
    double new_x = (double)rand() / RAND_MAX;
    new_x = minimum + new_x * (maximum - minimum);
    double new_y = (double)rand() / RAND_MAX;
    new_y = minimum + new_y * (maximum - minimum);
    vec.push_back(Point(new_x, new_y));
  }
  return true;
}

ClosestPairSolver::ClosestPairSolver() : num_points_(0),
                                         current_index1_(-1),
                                         current_index2_(-1),
                                         current_sqr_mindist_(-1) {}

void ClosestPairSolver::AddPoint(Point new_point) {
  ipoints_ori_.push_back(IndexedPoint(num_points_, new_point));
  num_points_ ++;
}

void ClosestPairSolver::AddPoints(const std::vector<Point>& new_points) {
  for (std::vector<const Point>::iterator it = new_points.begin(); it < new_points.end(); it++) {
    AddPoint(*it);
  }
}

void ClosestPairSolver::SetPoints(const std::vector<Point>& new_points) {
  Clear();
  AddPoints(new_points);
}

bool _sort_by_second(const std::tuple<int, double> &t1, const std::tuple<int, double> &t2) {
  return std::get<1>(t1) < std::get<1>(t2);
}

/* FindClosestPairNSquare is the naive O(n^2) algorithm to find the minimal distance */
bool ClosestPairSolver::FindClosestPairNSquare(int* pindex1, int* pindex2, double* pdist) {
  if (num_points_ <= 1) {
    return false;
  }
  double mindist = -1;
  int index1 = 0;
  int index2 = 0;
  for (int i = 0; i < num_points_; i++) {
    for (int j = i + 1; j < num_points_; j++) {
      double dist = _dist(ipoints_ori_.at(i), ipoints_ori_.at(j));
      if (dist < mindist || mindist < 0) {
        mindist = dist;
        index1 = i;
        index2 = j;
      }
    }
  }
  *pindex1 = index1;
  *pindex2 = index2;
  *pdist = sqrt(mindist);
  return true;
}

bool ClosestPairSolver::FindClosestPair(int* pindex1, int* pindex2, double* pdist) {
  // copy `ipoints_ori_` to `ipoints_`
  // sort the `ipoints_` vector by x
  ipoints_.resize(num_points_);
  std::copy(ipoints_ori_.begin(), ipoints_ori_.end(), ipoints_.begin());
  std::sort(ipoints_.begin(), ipoints_.end(), sort_ipoints_by_x);

  // sort the `ipoints_` by y to get `ipoints_indexes_by_y_`
  std::vector<std::tuple<int, double> > ipoints_tmp_y;
  for (int i = 0; i < num_points_; i++) {
    ipoints_tmp_y.push_back(std::make_tuple(i, ipoints_.at(i).point.y));
  }
  std::sort(ipoints_tmp_y.begin(), ipoints_tmp_y.end(), _sort_by_second);
  for (std::vector<std::tuple<int, double> >::iterator it = ipoints_tmp_y.begin();
       it != ipoints_tmp_y.end(); it ++) {
    ipoints_indexes_by_y_.push_back(std::get<0>(*it));
  }

  // Recursive divide and conquer
  bool success = _FindClosestPair(ipoints_.begin(), ipoints_.end(), ipoints_indexes_by_y_, &current_index1_, &current_index2_, &current_sqr_mindist_);
  *pindex1 = current_index1_;
  *pindex2 = current_index2_;
  *pdist = sqrt(current_sqr_mindist_);
  return success;
}

bool ClosestPairSolver::_FindClosestPair(std::vector<IndexedPoint>::iterator beg, std::vector<IndexedPoint>::iterator end, const std::vector<int>& indexes_by_y, int* pindex1, int*pindex2, double* pdist) {
  using std::vector;
  int sz = end - beg;
  // Base case: O(1)
  if (sz == 0 || sz == 1) {
    *pindex1 = -1;
    *pindex2 = -1;
    *pdist = -1;
    return false;
  } else if (sz == 2) {
    *pindex1 = (*beg).index;
    *pindex2 = (*(beg + 1)).index;
    *pdist = _dist(*beg, *(beg + 1));
    return true;
  }

  // Divide: O(n)
  vector<IndexedPoint>::iterator middle_it = beg + sz/2;
  double middle_x = (*middle_it).point.x;
  vector<int> indexes_by_y_l;
  vector<int> indexes_by_y_r;
  for (vector<const int>::iterator it = indexes_by_y.begin(); it != indexes_by_y.end(); it++) {
    if ((ipoints_.at(*it)).point.x <= middle_x) {
      indexes_by_y_l.push_back(*it);
    } else {
      indexes_by_y_r.push_back(*it);
    }
  }

  // Conquer: 2 * T(n/2)
  int index1_l, index1_r;
  int index2_l, index2_r;
  double mindist_l, mindist_r;
  double mindist;
  bool success_l = _FindClosestPair(beg, middle_it, indexes_by_y_l, &index1_l, &index2_l, &mindist_l);
  bool success_r = _FindClosestPair(middle_it, end, indexes_by_y_r, &index1_r, &index2_r, &mindist_r);
  if (success_r && success_l) {
    if (mindist_l < mindist_r) {
      mindist = mindist_l;
      *pindex1 = index1_l;
      *pindex2 = index2_l;
    } else {
      mindist = mindist_r;
      *pindex1 = index1_r;
      *pindex2 = index2_r;
    }
  } else if (success_r) {
    mindist = mindist_r;
    *pindex1 = index1_r;
    *pindex2 = index2_r;
  } else if (success_l) {
    mindist = mindist_l;
    *pindex1 = index1_l;
    *pindex2 = index2_l;
  } else {
    // something goes wrong
    // because this can not happen
    return false;
  }

  // Merge: O(n)
  vector<int> indexes_by_y_cross;
  for (vector<const int>::iterator it = indexes_by_y.begin(); it != indexes_by_y.end(); it++) {
    double ipoint_x = ipoints_.at(*it).point.x;
    if (ipoint_x > middle_x - mindist && ipoint_x < middle_x + mindist) {
      indexes_by_y_cross.push_back(*it);
    }
  }

  int cross_size = indexes_by_y_cross.size();
  for (int i = 0; i < cross_size; i++) {
    IndexedPoint ipoint = ipoints_.at(indexes_by_y_cross.at(i));
    for (int j = 0; j < 8 && i + j + 1 < cross_size; j++) {
      IndexedPoint ipoint_compare = ipoints_.at(indexes_by_y_cross.at(i + j + 1));
      double new_dist = _dist(ipoint, ipoint_compare);
      if (new_dist < mindist) {
        mindist = new_dist;
        *pindex1 = ipoint.index;
        *pindex2 = ipoint_compare.index;
      }
    }
  }
  *pdist = mindist;
  return true;
}
