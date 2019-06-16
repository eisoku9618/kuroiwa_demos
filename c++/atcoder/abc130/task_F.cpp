#include <algorithm>
#include <utility>
#include <vector>
#include <iostream>
#include <string>

struct PolyLine {
  PolyLine(const long increase, const long decrease, const long constant)
    : increase_(increase), decrease_(decrease), constant_(constant) {
    if (std::abs(increase_) < 1e8 && std::abs(decrease_) < 1e8) {
      const double intersection = (decrease_ - increase_) / 2.0;
      if (intersection >= 0) {
        intersection_array.push_back(intersection);
      }
    }
    if (std::abs(decrease_) < 1e8 && std::abs(constant_) < 1e8) {
      const double intersection = decrease_ - constant_;
      if (intersection >= 0) {
        intersection_array.push_back(intersection);
      }
    }
    if (std::abs(constant_) < 1e8 && std::abs(increase_) < 1e8) {
      const double intersection = constant_ - increase_;
      if (intersection >= 0) {
        intersection_array.push_back(intersection);
      }
    }
  }

  double CalcVal(double time, bool is_max) const {
    std::vector<double> candidate;
    if (increase_ < 1e8) {
      candidate.push_back(increase_ + time);
    }
    if (decrease_ < 1e8) {
      candidate.push_back(decrease_ - time);
    }
    if (constant_ < 1e8) {
      candidate.push_back(constant_);
    }
    if (is_max) {
      return *std::max_element(candidate.begin(), candidate.end());
    } else {
      return *std::min_element(candidate.begin(), candidate.end());
    }
  }

  const long increase_;
  const long decrease_;
  const long constant_;
  std::vector<double> intersection_array;
};

int main() {
  unsigned int n;
  std::cin >> n;

  std::vector<std::pair<long, long>> up_array, down_array, right_array, left_array;

  for (unsigned int i = 0; i < n; ++i) {
    long x, y;
    char d;
    std::cin >> x >> y >> d;
    const std::pair<long, long> xy = std::make_pair(x, y);
    switch (d) {
    case 'U':
      up_array.push_back(xy);
      break;
    case 'D':
      down_array.push_back(xy);
      break;
    case 'R':
      right_array.push_back(xy);
      break;
    case 'L':
      left_array.push_back(xy);
      break;
    }
  }

  long x_min_inc = 1e9, x_min_dec = 1e9, x_min_const = 1e9;
  long x_max_inc = 1e9, x_max_dec = 1e9, x_max_const = 1e9;
  long y_min_inc = 1e9, y_min_dec = 1e9, y_min_const = 1e9;
  long y_max_inc = 1e9, y_max_dec = 1e9, y_max_const = 1e9;
  {
    std::vector<long> updown_x_array;
    for (auto x : up_array) {
      updown_x_array.push_back(x.first);
    }
    for (auto x : down_array) {
      updown_x_array.push_back(x.first);
    }
    if (updown_x_array.size() != 0) {
      x_max_const = *std::max_element(updown_x_array.begin(), updown_x_array.end());
      x_min_const = *std::min_element(updown_x_array.begin(), updown_x_array.end());
    }

    if (right_array.size() != 0) {
      x_max_inc = std::max_element(right_array.begin(), right_array.end(), [](std::pair<long, long> a, std::pair<long, long> b) {return a.first > b.first;})->first;
      x_min_inc = std::min_element(right_array.begin(), right_array.end(), [](std::pair<long, long> a, std::pair<long, long> b) {return a.first > b.first;})->first;
    }

    if (left_array.size() != 0) {
      x_max_dec = std::max_element(left_array.begin(), left_array.end(), [](std::pair<long, long> a, std::pair<long, long> b) {return a.first > b.first;})->first;
      x_min_dec = std::min_element(left_array.begin(), left_array.end(), [](std::pair<long, long> a, std::pair<long, long> b) {return a.first > b.first;})->first;
    }
  }
  {
    std::vector<long> horizontal_y_array;
    for (auto y : right_array) {
      horizontal_y_array.push_back(y.second);
    }
    for (auto y : left_array) {
      horizontal_y_array.push_back(y.second);
    }
    if (horizontal_y_array.size() != 0) {
      y_max_const = *std::max_element(horizontal_y_array.begin(), horizontal_y_array.end());
      y_min_const = *std::min_element(horizontal_y_array.begin(), horizontal_y_array.end());
    }

    if (up_array.size() != 0) {
      y_max_inc = std::max_element(up_array.begin(), up_array.end(), [](std::pair<long, long> a, std::pair<long, long> b) {return a.second < b.second;})->second;
      y_min_inc = std::min_element(up_array.begin(), up_array.end(), [](std::pair<long, long> a, std::pair<long, long> b) {return a.second < b.second;})->second;
    }

    if (down_array.size() != 0) {
      y_max_dec = std::max_element(down_array.begin(), down_array.end(), [](std::pair<long, long> a, std::pair<long, long> b) {return a.second < b.second;})->second;
      y_min_dec = std::min_element(down_array.begin(), down_array.end(), [](std::pair<long, long> a, std::pair<long, long> b) {return a.second < b.second;})->second;
    }
  }

  const PolyLine x_max_poly(x_max_inc, x_max_dec, x_max_const);
  const PolyLine x_min_poly(x_min_inc, x_min_dec, x_min_const);
  const PolyLine y_max_poly(y_max_inc, y_max_dec, y_max_const);
  const PolyLine y_min_poly(y_min_inc, y_min_dec, y_min_const);

  std::vector<double> candidate_intersection_time;
  std::copy(x_max_poly.intersection_array.begin(), x_max_poly.intersection_array.end(),
            std::back_inserter(candidate_intersection_time));
  std::copy(x_min_poly.intersection_array.begin(), x_min_poly.intersection_array.end(),
            std::back_inserter(candidate_intersection_time));
  std::copy(y_max_poly.intersection_array.begin(), y_max_poly.intersection_array.end(),
            std::back_inserter(candidate_intersection_time));
  std::copy(y_min_poly.intersection_array.begin(), y_min_poly.intersection_array.end(),
            std::back_inserter(candidate_intersection_time));

  if (candidate_intersection_time.size() == 0) {
    candidate_intersection_time.push_back(0.0);
  }

  double area = -1;
  for (auto time : candidate_intersection_time) {
    const double x_max = x_max_poly.CalcVal(time, true);
    const double x_min = x_min_poly.CalcVal(time, false);
    const double y_max = y_max_poly.CalcVal(time, true);
    const double y_min = y_min_poly.CalcVal(time, false);
    const double this_area = (x_max - x_min) * (y_max - y_min);
    if (area < 0) {
      area = this_area;
    } else {
      if (this_area < area) {
        area = this_area;
      }
    }
  }

  std::cout << area << std::endl;

  return 0;
}
