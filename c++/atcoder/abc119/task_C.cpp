#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

class MyDfs {
public:
  MyDfs(const size_t max_depth,
        const int a, const int b, const int c,
        const std::vector<unsigned int> l_array)
    : max_depth_(max_depth),
      a_(a), b_(b), c_(c),
      l_array_(l_array) {
    assert(l_array_.size() == max_depth);
  };

  int search(const size_t depth, const int a, const int b, const int c) const {
    if (depth == max_depth_) {
      const int mp = std::abs(a - a_) + std::abs(b - b_) + std::abs(c - c_) - 10 * 3;
      if (a == 0 || b == 0 || c == 0) {
        return 1e+9;
      } else {
        return mp;
      }
    }
    const int ret_0 = search(depth + 1, a, b, c);
    const int ret_1 = search(depth + 1, a + l_array_.at(depth), b, c) + 10;
    const int ret_2 = search(depth + 1, a, b + l_array_.at(depth), c) + 10;
    const int ret_3 = search(depth + 1, a, b, c + l_array_.at(depth)) + 10;
    return std::min({ret_0, ret_1, ret_2, ret_3});
  }

private:
  const size_t max_depth_;
  const int a_;
  const int b_;
  const int c_;
  const std::vector<unsigned int> l_array_;
};

int main() {
  unsigned int n, a, b, c;
  std::cin >> n >> a >> b >> c;

  std::vector<unsigned int> l_array(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> l_array.at(i);
  }

  MyDfs dfs(n, a, b, c, l_array);
  std::cout << dfs.search(0, 0, 0, 0) << std::endl;

  return 0;
}
