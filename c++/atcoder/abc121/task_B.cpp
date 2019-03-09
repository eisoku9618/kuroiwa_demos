#include <iostream>
#include <vector>

int main() {
  int n, m, c;
  std::cin >> n >> m >> c;

  std::vector<int> b_array(m);
  for (size_t i = 0; i < m; ++i) {
    std::cin >> b_array.at(i);
  }

  unsigned int ans = 0;
  for (size_t i = 0; i < n; ++i) {
    std::vector<int> a_array(m);
    for (size_t j = 0; j < m; ++j) {
      std::cin >> a_array.at(j);
    }
    int sum = c;
    for (size_t j = 0; j < m; ++j) {
      sum += a_array.at(j) * b_array.at(j);
    }
    if (sum > 0) {
      ans += 1;
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
