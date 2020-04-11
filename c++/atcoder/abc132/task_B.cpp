#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int n;
  std::cin >> n;

  std::vector<int> p_vec;
  for (size_t i = 0; i < n; ++i) {
    int p;
    std::cin >> p;
    p_vec.push_back(p);
  }

  int counter = 0;
  for (size_t i = 1; i < n - 1; ++i) {
    const int max = std::max({p_vec.at(i - 1), p_vec.at(i), p_vec.at(i + 1)});
    const int min = std::min({p_vec.at(i - 1), p_vec.at(i), p_vec.at(i + 1)});
    if (p_vec.at(i) != max && p_vec.at(i) != min) {
      counter++;
    }
  }

  std::cout << counter << std::endl;

  return 0;
}
