#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  unsigned int N;
  std::cin >> N;

  std::vector<unsigned int> p_array(N);
  for (unsigned int i = 0; i < N; ++i) {
    std::cin >> p_array.at(i);
  }

  std::vector<unsigned int> p_array_sorted = p_array;
  std::sort(p_array_sorted.begin(), p_array_sorted.end(), std::less<unsigned int>());

  unsigned int diff_num = 0;
  for (unsigned int i = 0; i < N; ++i) {
    if (p_array.at(i) != p_array_sorted.at(i)) {
      diff_num += 1;
    }
  }

  if (diff_num == 0 || diff_num == 2) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }

  return 0;
}
