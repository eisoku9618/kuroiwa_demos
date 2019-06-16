#include <iostream>
#include <vector>

int main() {
  int n, x;
  std::cin >> n >> x;

  std::vector<int> l_array;
  for (size_t i = 0; i < n; ++i) {
    int li;
    std::cin >> li;
    l_array.push_back(li);
  }

  std::vector<int> d_array;
  d_array.push_back(0);
  for (auto l_i : l_array) {
    const int di_1 = d_array.back();
    d_array.push_back(di_1 + l_i);
  }

  size_t count = 0;
  for (auto d_i : d_array) {
    if (d_i <= x) {
      count++;
    } else {
      break;
    }
  }

  std::cout << count << std::endl;
  return 0;
}
