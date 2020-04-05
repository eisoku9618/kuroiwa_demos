#include <iostream>
#include <map>

#include <algorithm>
#include <utility>
#include <vector>
#include <string>

int main() {
  unsigned int N;
  std::cin >> N;

  std::multimap<unsigned int, unsigned int, std::less<unsigned long>> xy_map;
  std::multimap<unsigned int, unsigned int, std::less<unsigned long>> yx_map;
  for (unsigned int i = 0; i < N; ++i) {
    unsigned int x, y;
    std::cin >> x >> y;
    xy_map.emplace(x, y);
    yx_map.emplace(y, x);
  }

  std::multimap<unsigned int, unsigned int, std::less<unsigned long>> corner_xy_map;
  std::multimap<unsigned int, unsigned int, std::less<unsigned long>> corner_yx_map;
  for (const auto& xy_pair : xy_map) {
    const unsigned int x_count = xy_map.count(xy_pair.first);
    const unsigned int y_count = yx_map.count(xy_pair.second);
    if (x_count > 1 && y_count > 1) {
      corner_xy_map.insert(xy_pair);
      corner_yx_map.emplace(xy_pair.second, xy_pair.first);
    }
  }

  std::multimap<unsigned int, unsigned int, std::less<unsigned long>> pure_map;
  for (const auto& xy_pair : xy_map) {
    if (corner_xy_map.count(xy_pair.first) != 0 || corner_yx_map.count(xy_pair.second) != 0) {
      pure_map.insert(xy_pair);
    }
  }

  std::vector<unsigned int> x_vec, y_vec;
  for (const auto& xy_pair : pure_map) {
    x_vec.push_back(xy_pair.first);
    y_vec.push_back(xy_pair.second);
  }
  std::sort(x_vec.begin(), x_vec.end());
  x_vec.erase(std::unique(x_vec.begin(), x_vec.end()), x_vec.end());
  std::sort(y_vec.begin(), y_vec.end());
  y_vec.erase(std::unique(y_vec.begin(), y_vec.end()), y_vec.end());

  const unsigned int grid_num = x_vec.size() * y_vec.size();

  std::cout << grid_num - pure_map.size() << std::endl;

  return 0;
}
