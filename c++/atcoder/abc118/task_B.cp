#include <iostream>
#include <vector>

int main() {
  unsigned int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<unsigned int>> a_mat(n, std::vector<unsigned>(m, 0));
  for (size_t i = 0; i < n; ++i) {
    unsigned int k;
    std::cin >> k;
    for (size_t k_i = 0; k_i < k; k_i++) {
      unsigned int idx = 0;
      std::cin >> idx;
      a_mat.at(i).at(idx - 1) = 1;
    }
  }

  unsigned int counter = 0;
  for (size_t j = 0; j < m; ++j) {
    bool is_ok = true;
    for (size_t i = 0; i < n; ++i) {
      if (a_mat.at(i).at(j) == 0) {
        is_ok = false;
        break;
      }
    }
    if (is_ok) {
      ++counter;
    }
  }
  std::cout << counter << std::endl;

  return 0;
}
